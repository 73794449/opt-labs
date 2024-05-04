#include <stddef.h>
#include <stdlib.h>
#ifndef TOKEN_STRUCTURE_H
#define TOKEN_STRUCTURE_H

struct token {
  size_t row;
  size_t col;
  size_t code;
  char *_data;
  size_t dataSize;
};
typedef struct token Token;

Token create_token(size_t row, size_t col, char *_data, size_t dataSize,
                   unsigned short int type);

Token create_token_with_code(size_t row, size_t col, char *_data,
                             size_t dataSize, size_t code);
#endif