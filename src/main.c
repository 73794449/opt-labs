#include "out.h"
#include "lexer.h"
int main(int argc, char *argv[]) {
  proc_cli(argc, argv);
  if (gotError) {
    print_errors();
    return -1;
  } else {
    proc_lexer(params._input_file);
  }
  if (params.verbose) {
    out_file_lexer();
    print_file_out();
  } else {
    out_file_lexer();
  }
  return 0;
}