#include <stdlib.h>

#include "error.h"
#include "lexer_structure.h"
void add_buffer_symbol() {
  lexer._buffer =
      (char *)realloc(lexer._buffer, (lexer.bufferSize + 2) * sizeof(char));
  if (lexer._buffer == NULL)
    add_to_errors(create_error_with_linecolumn(
        LEXER_STATE, "Cannot resize *buff", true, lexer.row, lexer.col));

  lexer._buffer[lexer.bufferSize] = lexer.symbol;
  lexer._buffer[lexer.bufferSize + 1] = '\0';
  lexer.bufferSize++;
}

void clean_buffer() {
  lexer._buffer = NULL;
  lexer.bufferSize = 0;
}