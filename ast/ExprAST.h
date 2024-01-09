#pragma once

#include "llvm/IR/BasicBlock.h"

class ExprAST {
public:
  virtual ~ExprAST() {}
  virtual llvm::Value *codegen() = 0;
};