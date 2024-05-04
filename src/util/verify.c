#include "verify.h"
#include "symbol_type.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char c, d;
size_t o_row = 0, o_col = 0;
size_t v_row = 0, v_col = 0;

#define step_macro(x, row, col)                                                \
  if (x == '\n') {                                                             \
    row++;                                                                     \
    col = 0;                                                                   \
  } else if (x == '\t') {                                                      \
    col += 4;                                                                  \
  } else {                                                                     \
    col++;                                                                     \
  }

void step(bool is_c) {
  if (is_c) {
    step_macro(c, o_row, o_col);
  } else {
    step_macro(d, v_row, v_col);
  }
}

void skip_ws(FILE *_out, FILE *_ver, bool is_c) {
  if (is_c) {
    if (symbol_type(c) == SYMBOL_WS) {
      c = (char)getc(_out);
      skip_ws(_out, _ver, true);
    }
  } else {
    if (symbol_type(d) == SYMBOL_WS) {
      d = (char)getc(_ver);
      skip_ws(_out, _ver, false);
    }
  }
}

void verify(char *_output, char *_verify) {
  FILE *_out = fopen(_output, "r");
  if (_out == NULL) {
    printf("Failed to open output file on verify stage\n");
    exit(EXIT_FAILURE);
  }
  FILE *_ver = fopen(_verify, "r");
  if (_ver == NULL) {
    printf("Failed to open verify file on verify stage\n");
    exit(EXIT_FAILURE);
  }

  do {
    c = (char)getc(_out);
    d = (char)getc(_ver);
    skip_ws(_out, _ver, true);
    skip_ws(_out, _ver, false);
    if (c != d) {
      printf("Output(%llu:%llu:%c) != Verify(%llu:%llu:%c)\n", o_row + 1, o_col,
             c, v_row + 1, v_col, d);
    }
  } while (!(c == EOF || d == EOF));

  fclose(_out);
  fclose(_ver);
}