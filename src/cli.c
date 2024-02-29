#include "cli.h"
#include "error.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

Params params = {NULL, NULL, false};

void check_file_access(char *_file, bool inputFile) {
  if (access(_file, F_OK) != 0) {
    if (inputFile) {
      add_to_errors(create_error_without_linecolumn(
          errorCount + 1, FILE_ACCESS, "Missing access to input file", true));
    } else {
      add_to_errors(create_error_without_linecolumn(
          errorCount + 1, FILE_ACCESS, "File for output does not exist, creating...",
          false));
    }
  }
}

void check_file_missing(char *_file) {
  FILE *_fp;
  if(_file != NULL){
  _fp = fopen(_file, "w");

  if (_fp == NULL) {
    add_to_errors(create_error_without_linecolumn(
        errorCount + 1, FILE_ACCESS, "Cannot create/open output file", true));
  }
  fclose(_fp);
  }
  else
  {
        add_to_errors(create_error_without_linecolumn(
        errorCount + 1, FILE_ACCESS, "Cannot create/open output file", true));
  }
}

void proc_cli(int argc, char *argv[]) {
  if (argc == 2) {
    params._input_file = argv[1];
  } else {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
        params._input_file = argv[i + 1];
        i++;
      } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
        params._output_file = argv[i + 1];
        i++;
      } else if (strcmp(argv[i], "-v") == 0) {
        params.verbose = 1;
      }
    }
  }

  if (params._input_file == NULL) {
    add_to_errors(create_error_without_linecolumn(
        errorCount + 1, FILE_ACCESS, "Input filename is empty.", true));
  } else {
    check_file_access(params._input_file, true);
    check_file_access(params._output_file, false);
    check_file_missing(params._output_file);
  }
}
