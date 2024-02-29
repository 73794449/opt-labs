#include "lexer_structure.h"
#include "error.h"
#include <stdlib.h>
void add_buffer_symbol() {
    lexer._buffer =
        (char *)realloc(lexer._buffer, (lexer.bufferSize+1) * sizeof(char));
    if (lexer._buffer == NULL) {
      add_to_errors(create_error_with_linecolumn(errorCount + 1, 0,
                                                 "Cannot resize *buff", true,
                                                 lexer.row, lexer.col));
    }
    lexer._buffer[lexer.bufferSize] = lexer.symbol;
    lexer._buffer[lexer.bufferSize+1] = '\0';
    lexer.bufferSize++;
}

void clean_buffer() {
  lexer._buffer = NULL;
  lexer.bufferSize = 0;
}