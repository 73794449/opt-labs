#include "error.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Error *_errors = NULL;
size_t errorCount = 0;
bool gotError = false;
bool gotWarning = false;

bool has_critical() {
  for (size_t i = 0; i < errorCount; i++)
    if (_errors[i].critical)
      return true;

  return false;
}

Error create_error_syntaxer(size_t row, size_t col, char *_expected,
                            char *_here) {
  Error error = {.state = SYNTAX_STATE,
                 .row = row,
                 .col = col,
                 .number = errorCount + 1,
                 .critical = true,
                 ._expected = _expected,
                 ._here = _here,
                 .syntaxer = true};
  return error;
}

Error create_error_without_linecolumn(unsigned short int state,
                                      char *_error_message, bool critical) {
  Error error = {errorCount + 1, state, NULL, critical, false, 0, 0,
                 NULL,           NULL,  false};

  error._error_message=(char*)malloc(sizeof(char)*strlen(_error_message));
  error._error_message=strcpy(error._error_message, _error_message);
  return error;
}

Error create_error_with_linecolumn(unsigned short int state,
                                   char *_error_message, bool critical,
                                   size_t row, size_t col) {
  Error error = {
      errorCount + 1, state, _error_message, critical, true, row, col,
      NULL,           NULL,  false};
  return error;
}

Error create_error_def() {
  Error error = {0, NOT_ERROR, "", false, false, 0, 0, NULL, NULL, false};
  return error;
}

void add_to_errors(Error error) {
  errorCount++;
  _errors = (Error *)realloc(_errors, (errorCount) * sizeof(Error));
  if (_errors == NULL)
    exit(EXIT_FAILURE);
  else {
    _errors[errorCount - 1] = error;
    if (error.critical)
      gotError = true;
    else
      gotWarning = true;
  }
}

void clean_errors() {
  errorCount = 0;
  _errors = NULL;
}