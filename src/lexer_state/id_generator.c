#include <stdbool.h>
#include <string.h>

#include "constant.h"
#include "id_generator.h"
#include "identifier.h"
#include "lexer_structure.h"
#include "strings.h"
#include "symbol_type.h"

size_t get_keyword_id() {
  char *_verify[10] = {"PROGRAM", "VAR", "BEGIN",   "END",     "CONST",
                       "CASE",    "OF",  "ENDCASE", "INTEGER", "FLOAT"};
  for (size_t i = 0; i < 10; i++)
    if (!strcmp(lexer._buffer, _verify[i]))
      return i + 1;
  return 0;
}

size_t get_dm1_id() {
  char _verify[12] = {'+', '-', ':', '<', '>',  '=',
                      '.', ';', '[', ']', '\\', '/'};
  for (unsigned short i = 0; i < 12; i++)
    if (lexer._buffer[0] == _verify[i])
      return (size_t)lexer._buffer[0];
  return 0;
}
size_t get_dm2_id() {
  char _verify[3] = {'<', '>', ':'};
  if (strlen(lexer._buffer) > 1)
    if (lexer._buffer[1] == '=')
      for (size_t i = 0; i < 3; i++)
        if (lexer._buffer[0] == _verify[i])
          return i + 301;

  return get_dm1_id();
}

size_t get_id(size_t row, size_t col, unsigned short int type) {
  size_t base = 0;
  switch (type) {
  case SYMBOL_DIG:
    base = 501;
    for (size_t i = 0; i < constantCount; i++)
      if (!strcmp(lexer._buffer, _constants[i]._data))
        return _constants[i].code;

    base += constantCount;
    add_to_constants(create_token_with_code(row, col, lexer._buffer,
                                            lexer.bufferSize, base));
    break;
  case SYMBOL_LET:
    if (get_keyword_id()) {
      base = 400;
      base += get_keyword_id();
    } else {
      if (lexer._buffer[0] > 64 && lexer._buffer[0] < 91) {
        base = 1001;
        for (size_t i = 0; i < identifierCount; i++)
          if (!strcmp(lexer._buffer, _identifiers[i]._data))
            return _identifiers[i].code;

        base += identifierCount;
        add_to_identifiers(create_token_with_code(row, col, lexer._buffer,
                                                  lexer.bufferSize, base));
      } else {
        base = 750;
        for (size_t i = 0; i < stringsCount; i++)
          if (!strcmp(lexer._buffer, _strings[i]._data))
            return _strings[i].code;

        base += stringsCount;
        add_to_strings(create_token_with_code(row, col, lexer._buffer,
                                              lexer.bufferSize, base));
      }
    }
    break;
  case SYMBOL_DM1:
    base = get_dm1_id();
    break;
  case SYMBOL_DM2:
    base = get_dm2_id();
    break;

  default:
    add_to_errors(create_error_without_linecolumn(
        LEXER_STATE, "Impossible for get_code()", true));
    return 0;
  };
  return base;
}