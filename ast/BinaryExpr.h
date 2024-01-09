#include "llvm/IR/IRBuilder.h"
#include "logger/logger.h"
#include "ast/ExprAST.h"
#include "kaleidoscope/kaleidoscope.h"

// Expression class for a binary operator
class BinaryExprAST : public ExprAST {
  char Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS) : Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
  // Generate LLVM code for binary expressions
  llvm::Value *BinaryExprAST::codegen() override {
    llvm::Value *L = LHS->codegen();
    llvm::Value *R = RHS->codegen();

    if (!L || !R) {
        return nullptr;
    }

    switch (Op) {
        case '+':
        return Builder.CreateFAdd(L, R, "addtmp");
        case '-':
        return Builder.CreateFSub(L, R, "subtmp");
        case '*':
        return Builder.CreateFMul(L, R, "multmp");
        case '<':
        L = Builder.CreateFCmpULT(L, R, "cmptmp");
        return Builder.CreateUIToFP(L, llvm::Type::getDoubleTy(TheContext), "booltmp");
        default:
        return LogErrorV("Invalid binary operator");
    }
    }
};