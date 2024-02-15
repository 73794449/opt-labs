#include "token.h"
#include "error.h"
#include <stddef.h>
#include <stdlib.h>

Token *_tokens = NULL;
unsigned long int tokenCount = 0;

void add_to_tokens(Token token) {
  tokenCount++;
  _tokens = (Token *)realloc(_tokens, (tokenCount) * sizeof(Token));
  if (_tokens == NULL) {
    add_to_errors(create_error_with_linecolumn(errorCount + 1, 0,
                                               "Cannot reallocate *_tokens",
                                               true, token.row, token.col));
  } else {
    _tokens[tokenCount - 1] = token;
  }
}

Token create_token(unsigned int row, unsigned int col, unsigned long int code,
                   char _data[], unsigned int dataSize) {
  char *__data = malloc((dataSize + 1) * sizeof(char));
  for (unsigned int i = 0; i < dataSize; i++)
    __data[i] = _data[i];
  __data[dataSize] = '\0';
  Token token = {row - 1, col - 1, code, __data, dataSize};
  return token;
}