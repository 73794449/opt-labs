#ifndef ERROR_H
#define ERROR_H
#include <stdbool.h>

struct error {
  // -1 -> Means that error does not exist
  long int number;
  // 0 -> Lexer, -1 -> File access, -2 -> Memory access
  short int state;
  char *_error_message;
  // true -> Error, false -> Warning
  bool critical;
  bool hasLineColumn;
  unsigned int row;
  unsigned int col;
};
typedef struct error Error;

extern Error *_errors;
extern unsigned int errorCount;
extern bool gotError;
extern bool gotWarning;

Error create_error_without_linecolumn(long int number, short int state,
                                      char *_error_message, bool critical);
Error create_error_with_linecolumn(long int number, short int state,
                                   char *_error_message, bool critical,
                                   unsigned int row, unsigned int col);
Error create_error_def();
void add_to_errors(Error error);
bool has_critical();

#endif