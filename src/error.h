#include <stdbool.h>
#include <bits/types.h>
#include <stddef.h>
#ifndef ERROR_H
#define ERROR_H

struct error {
  size_t number;
  __uint8_t state;
  char *_error_message;
  bool critical;
  bool hasLineColumn;
  size_t row;
  size_t col;
};
typedef struct error Error;

/*
@state
*/
#define NOT_ERROR 0
#define FILE_ACCESS 1
#define MEMORY_ACCESS 2
#define LEXER_STATE 3

extern Error *_errors;
extern size_t errorCount;
extern bool gotError;
extern bool gotWarning;

Error create_error_without_linecolumn(size_t number, __uint8_t state,
                                      char *_error_message, bool critical);
Error create_error_with_linecolumn(size_t number, __uint8_t state,
                                   char *_error_message, bool critical,
                                   size_t row, size_t col);
Error create_error_def();
void add_to_errors(Error error);
bool has_critical();

#endif