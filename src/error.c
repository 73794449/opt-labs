#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <bits/types.h>
#include <stddef.h>
Error *_errors = NULL;
size_t errorCount = 0;
bool gotError = false;
bool gotWarning = false;

bool has_critical() {
  for (size_t i = 0; i < errorCount; i++) {
    if (_errors[i].critical)
      return true;
  }
  return false;
}

Error create_error_without_linecolumn(size_t number, __uint8_t state,
                                      char *_error_message, bool critical) {
  Error error = {number, state, _error_message, critical, false, 0, 0};
  return error;
}

Error create_error_with_linecolumn(size_t number, __uint8_t state,
                                   char *_error_message, bool critical,
                                   size_t row, size_t col) {

  Error error = {number, state, _error_message, critical, true, row, col};
  return error;
}

Error create_error_def() {
  Error error = {0, NOT_ERROR, "", false, false, 0, 0};
  return error;
}

void add_to_errors(Error error) {
  errorCount++;
  _errors = (Error *)realloc(_errors, (errorCount) * sizeof(Error));
  if (_errors == NULL) {
    exit(EXIT_FAILURE);
  } else {
    _errors[errorCount - 1] = error;
    if (error.critical)
      gotError = true;
    else
      gotWarning = true;
  }
}