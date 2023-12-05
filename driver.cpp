//===----------------------------------------------------------------------===//
// Main driver code.
//===----------------------------------------------------------------------===//

#include <cstdio>
#include <cstdlib>

#include "ast.h"
#include "lexer.h"
#include "parser.h"

int main() {
  // Install standard binary operators.
  // 1 is lowest precedence.
  BinopPrecedence['<'] = 10;
  BinopPrecedence['+'] = 20;
  BinopPrecedence['-'] = 20;
  BinopPrecedence['*'] = 40; // highest.

  // Prime the first token.
  fprintf(stderr, "ready> ");
  getNextToken();

  // Run the main "interpreter loop" now.
  MainLoop();

  return 0;
}