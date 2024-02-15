#ifndef LEXER_H
#define LEXER_H
#include "cli.h"
#include <stddef.h>
struct lexer {
  unsigned int state;
  /*
  0: whitespace - Reading next tokek(whitespace)
  1: number - Reading next token(number)
  11: add - Reading + and -
  2: identifier - Reading next token(identifier)
  3: delimiter1 - Reading next token(delimeter1)
  4: delimiter2 - Reading next token(delimeter2)
  51: comment begin - Reading ('('), BCOM
  52: comment confirm - Reading token('*'), COMCON
  53: comment end - Reading token(')'), ECOM
  6: ERR - error
  7: EXIT - exit state
  8: START - start state
  */

  // Buff work
  char *_buffer;
  unsigned int bufferSize;
  unsigned short int row;
  unsigned short int col;
  char symbol;
  unsigned short int symbolType;
  bool com;
};
typedef struct lexer Lexer;

extern Lexer lexer;

void proc_lexer(char *_input_file);

#endif