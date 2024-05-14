#include <stdbool.h>
#include <stddef.h>

#ifndef LEXER_STRUCTURE_H
#define LEXER_STRUCTURE_H

struct lexer {
  char *_buffer;
  size_t bufferSize;
  size_t row;
  size_t col;
  char symbol;
  unsigned short int symbolType;
  bool inComment;
};
typedef struct lexer Lexer;
extern Lexer lexer;

void add_buffer_symbol();
void clean_buffer();
#endif