#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cli.h"
#include "error.h"

#define WIN

Params params = {NULL, "output", false, true, true, true, NULL};

void check_file_access(char *_file, bool inputFile) {
  if (access(_file, F_OK) == -1) {
    if (inputFile)
      add_to_errors(create_error_without_linecolumn(
          FILE_ACCESS, "Missing access to input/verify file", true));
    else
      add_to_errors(create_error_without_linecolumn(
          FILE_ACCESS, "File for output does not exist, creating...", false));
  }
}

void check_file_missing(char *_file) {
  FILE *_fp;
  if (_file != NULL) {
#ifdef WIN
    _fp = fopen(_file, "w+");
#endif
#ifndef WIN
    _fp = fopen(_file, "w");
#endif

    if (_fp == NULL)
      add_to_errors(create_error_without_linecolumn(
          FILE_ACCESS, "Cannot create/open output file", true));

    fclose(_fp);
  } else
    add_to_errors(create_error_without_linecolumn(
        FILE_ACCESS, "Cannot create/open output file", true));
}

void proc_cli(int argc, char *argv[]) {
  if (argc == 2)
    params._input_file = argv[1];
  else {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
        params._input_file = argv[++i];
      else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
        params._output_file = argv[++i];
      else if (strcmp(argv[i], "-q") == 0)
        params.verbose = 0;
      else if (strcmp(argv[i], "-offsyntax") == 0)
        params.out_syntax = false;
      else if (strcmp(argv[i], "-offlexer") == 0)
        params.out_lexer = false;
      else if (strcmp(argv[i], "-offcodegen") == 0)
        params.out_codegen = false;
      else if (strcmp(argv[i], "-v") == 0 && i + 1 < argc)
        params._verify_file = argv[++i];
    }
  }

  if (params._input_file == NULL) {
    char v[200];
    snprintf(v,200,"Input filename %s is inaccessible.",params._input_file);
    add_to_errors(create_error_without_linecolumn(
        FILE_ACCESS, v, true));
  } else {
    check_file_access(params._input_file, true);
    check_file_access(params._output_file, false);
    if (params._verify_file != NULL)
      check_file_access(params._verify_file, true);
    check_file_missing(params._output_file);
  }
}
