#include "lexer.h"
#include "stdlib.h"
#include "symbol_type.h"
Lexer lexer = {NULL, 0, 1, 1, '\0', SYMBOL_START, false};

void proc_lexer(char *_input_file) {
  FILE *__input_file;
  __input_file = fopen(_input_file, "r");
  if (__input_file == NULL)
    add_to_errors(create_error_without_linecolumn(
        FILE_ACCESS, "Cannot open input file.", true));
  else {
    inp(__input_file);
    do {
      switch (lexer.symbolType) {
      case SYMBOL_WS:
        ws(__input_file);
        break;
      case SYMBOL_DIG:
        dig(__input_file);
        break;
      case SYMBOL_LET:
        let(__input_file);
        break;
      case SYMBOL_DM1:
        dm1(__input_file);
        break;
      case SYMBOL_DM2:
        dm2(__input_file);
        break;
      case SYMBOL_COM_BEGIN:
        com_begin(__input_file);
        break;
      case SYMBOL_ERROR:
        s_error(__input_file);
        break;
      case SYMBOL_EOF:
        break;
      default:
        add_to_errors(create_error_without_linecolumn(
            LEXER_STATE, "Impossible if rrly, unknown category", true));
        lexer.symbolType = SYMBOL_EOF;
        break;
      };
    } while (lexer.symbolType != SYMBOL_EOF);
  }
  fclose(__input_file);
}
