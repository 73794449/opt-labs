#include "out.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
  proc_cli(argc, argv);
  if (gotError) {
    print_errors();
    return -1;
  } else {
    proc_lexer(params._input_file);
  }
  if (params.verbose) {
    print_errors();
    out_file_lexer();
  } else {
    out_file_lexer();
    print_file_out();
  }
  return 0;
}