/// NumberExprAST - Expression class for numeric literals like "1.0".
#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Constant.h>

#include "ast/ExprAST.h"


class NumberExprAST : public ExprAST {
  double Val;

public:
    NumberExprAST(double Val) : Val(Val) {}
    llvm::Value *NumberExprAST::codegen() override {
      return llvm::ConstantFP::get(*TheContext, llvm::APFloat(Val));
    }
};