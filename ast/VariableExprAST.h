#pragma once

#include "ast/ExprAST.h"
#include "logger/logger.h"

// Expression class for referencing a variable, like "a"
class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {}
  // We assume that the variable has already been emitted somewhere
  llvm::Value *VariableExprAST::codegen() override {
    llvm::Value *V = NamedValues[Name];

    if (!V) {
        LogErrorV("Unknown variable name");
    }

    return V;
    }
};
