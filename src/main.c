#include "lexer.h"
#include "out.h"
#include "syntax.h"
#include "verify.h"

int main(int argc, char *argv[]) {
  proc_cli(argc, argv);

  if (gotError) {
    print_errors();
    return -1;
  } else
    proc_lexer(params._input_file);

  if (params.out_lexer) {
    if (params.verbose) {
      out_file_lexer();
      print_file_out();
    } else
      out_file_lexer();
  }

  if (gotError) {
    print_errors();
    return -1;
  } else {
    just_clean();
    proc_syntax();
  }

  if (params.out_syntax) {
    if (params.verbose) {
      out_file_syntax();
      print_file_out();
    } else
      out_file_syntax();
  }

  free_trees();
  free_errors();
  free_tables();
  free_tokens();

  if (params._verify_file != NULL) {
    verify(params._output_file, params._verify_file);
  }
  return 0;
}