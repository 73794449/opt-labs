#include "token.h"
#include "id_generator.h"

Token *_tokens = NULL;
size_t tokenCount = 0;

void add_to_tokens(Token token) {
  tokenCount++;
  _tokens = (Token *)realloc(_tokens, tokenCount * sizeof(Token));
  if (_tokens == NULL)
    add_to_errors(create_error_with_linecolumn(MEMORY_ACCESS,
                                               "Cannot reallocate *_tokens",
                                               true, token.row, token.col));
  else

    _tokens[tokenCount - 1] = token;
}
