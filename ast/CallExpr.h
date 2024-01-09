
#include "ast/ExprAST.h"
#include "llvm/IR/IRBuilder.h"
#include "logger/logger.h"
#include "kaleidoscope/kaleidoscope.h"

// Expression class for function calls
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const std::string &Callee, std::vector<std::unique_ptr<ExprAST>> Args) : Callee(Callee), Args(std::move(Args)) {}
  // Generate LLVM code for function calls
  llvm::Value *CallExprAST::codegen() override {
    llvm::Function *CalleeF = TheModule->getFunction(Callee);

    if (!CalleeF) {
        return LogErrorV("Unknown function referenced");
    }

    if (CalleeF->arg_size() != Args.size()) {
        return LogErrorV("Incorrect # arguments passed");
    }

    std::vector<llvm::Value *> ArgsV;
    for (unsigned i = 0, e = Args.size(); i != e; i++) {
        ArgsV.push_back(Args[i]->codegen());

        if (!ArgsV.back()) {
        return nullptr;
        }
    }

    return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
  }
};