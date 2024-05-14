#include "verify.h"
#include "symbol_type.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char c, d;
size_t o_row = 0, o_col = 0;
size_t v_row = 0, v_col = 0;

#define step_macro(x, row, col)                                                \
  do {                                                                         \
    if (x == '\n') {                                                           \
      row++;                                                                   \
      col = 0;                                                                 \
    } else if (x == '\t') {                                                    \
      col += 4;                                                                \
    } else {                                                                   \
      col++;                                                                   \
    }                                                                          \
  } while (0)

#define step_c() step_macro(c, o_row, o_col)
#define step_d() step_macro(d, v_row, v_col)
#define if_step(x)                                                             \
  do {                                                                         \
    if (x)                                                                     \
      step_c();                                                                \
    else                                                                       \
      step_d();                                                                \
  } while (0)
#define skip_ws_char(x, flag)                                                  \
  do {                                                                         \
    if (symbol_type(x) == SYMBOL_WS) {                                         \
      x = (char)getc(_out);                                                    \
      if_step(flag);                                                           \
      skip_ws(_out, _ver, flag);                                               \
    }                                                                          \
  } while (0)
#define open_read_file(pname, filename)                                        \
  FILE *pname = fopen(filename, "r");                                          \
  if (_out == NULL) {                                                          \
    printf("Failed to open output file on verify stage\n");                    \
    exit(EXIT_FAILURE);                                                        \
  }

void skip_ws(FILE *_out, FILE *_ver, bool is_c) {
  if (is_c)
    skip_ws_char(c, true);
  else
    skip_ws_char(d, false);
}

void verify(char *_output, char *_verify) {
  open_read_file(_out, _output);
  open_read_file(_ver, _verify);

  do {
    c = (char)getc(_out);
    d = (char)getc(_ver);
    step_c();
    step_d();
    skip_ws(_out, _ver, true);
    skip_ws(_out, _ver, false);
    if (c != d)
      printf("Output(%llu:%llu:%c) != Verify(%llu:%llu:%c)\n", o_row + 1, o_col,
             c, v_row + 1, v_col, d);
  } while (!(c == EOF || d == EOF));

  fclose(_out);
  fclose(_ver);
}