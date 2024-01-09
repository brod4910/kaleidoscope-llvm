#pragma once 

#include "ast/ExprAST.h"
#include "llvm/IR/IRBuilder.h"
#include "kaleidoscope/kaleidoscope.h"

// Represents the "prototype" for a function,
// which captures its name, and its argument names
class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;

public:
  PrototypeAST(const std::string &name, std::vector<std::string> Args) : Name(name), Args(std::move(Args)) {}

  // Generates LLVM code for externals calls
  llvm::Function *PrototypeAST::codegen() override {
    std::vector<llvm::Type *> Doubles(Args.size(), llvm::Type::getDoubleTy(TheContext));
    llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getDoubleTy(TheContext), Doubles, false);
    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, TheModule.get());

    unsigned Idx = 0;
    for (auto &Arg : F->args()) {
      Arg.setName(Args[Idx++]);
    }

    return F;
  }

  const std::string &getName() const { return Name; }
};