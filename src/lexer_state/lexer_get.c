#include "lexer_get.h"
#include "symbol_type.h"

void inp(FILE *__input_file) {
  lexer.symbol = (char)fgetc(__input_file);
  if (lexer.symbol == '\n') {
    lexer.row++;
    lexer.col = 1;
  } else {
    if (lexer.symbol == '\t')
      lexer.col += 4;
    else
      lexer.col++;
  }
  lexer.symbolType = symbol_type(lexer.symbol);
}

void ws(FILE *__input_file) {
  do
    inp(__input_file);
  while (lexer.symbolType == SYMBOL_WS);
}
void dig(FILE *__input_file) {
  size_t row = lexer.row;
  size_t col = lexer.col;
  do {
    add_buffer_symbol();
    inp(__input_file);
  } while (lexer.symbolType == SYMBOL_DIG);

  add_to_tokens(
      create_token(row, col, lexer._buffer, lexer.bufferSize, SYMBOL_DIG));
  clean_buffer();
}
void let(FILE *__input_file) {
  size_t row = lexer.row;
  size_t col = lexer.col;
  do {
    add_buffer_symbol();
    inp(__input_file);
  } while (lexer.symbolType == SYMBOL_DIG || lexer.symbolType == SYMBOL_LET);

  add_to_tokens(
      create_token(row, col, lexer._buffer, lexer.bufferSize, SYMBOL_LET));
  clean_buffer();
}
void dm1(FILE *__input_file) {
  size_t row = lexer.row;
  size_t col = lexer.col;
  add_buffer_symbol();

  add_to_tokens(
      create_token(row, col, lexer._buffer, lexer.bufferSize, SYMBOL_DM1));
  clean_buffer();
  inp(__input_file);
}

void dm2(FILE *__input_file) {
  size_t row = lexer.row;
  size_t col = lexer.col;
  add_buffer_symbol();
  inp(__input_file);
  if (lexer.symbolType == SYMBOL_DM1) {
    add_buffer_symbol();
    inp(__input_file);
  }
  add_to_tokens(
      create_token(row, col, lexer._buffer, lexer.bufferSize, SYMBOL_DM2));
  clean_buffer();
}

void com_begin(FILE *__input_file) {
  size_t row = lexer.row;
  size_t col = lexer.col;
  inp(__input_file);
  if (lexer.symbol == '*') {
    lexer.inComment = true;
    com_confirm(__input_file, row, col);
  } else {
    add_to_errors(create_error_with_linecolumn(LEXER_STATE, "No * after (",
                                               true, row, col));
    inp(__input_file);
  }
}

void com_confirm(FILE *__input_file, size_t row, size_t col) {
  inp(__input_file);
  if (lexer.symbol == '*') {
    com_ending(__input_file, row, col);
  } else {
    if (lexer.symbolType == 7) {
      add_to_errors(create_error_with_linecolumn(
          LEXER_STATE, "Not closed comment", true, row, col));
      inp(__input_file);
    } else
      com_confirm(__input_file, row, col);
  }
}

void com_ending(FILE *__input_file, size_t row, size_t col) {
  inp(__input_file);
  if (lexer.symbol == ')') {
    inp(__input_file);
    lexer.inComment = false;
  } else {
    if (lexer.symbol == '*')
      com_ending(__input_file, row, col);
    else {
      if (lexer.symbolType == 7) {
        add_to_errors(create_error_with_linecolumn(
            LEXER_STATE, "Not closed comment", true, row, col));
        inp(__input_file);
      } else
        com_confirm(__input_file, row, col);
    }
  }
}

void s_error(FILE *__input_file) {
  if (lexer.symbolType == SYMBOL_COM_CONFIRM ||
      lexer.symbolType == SYMBOL_COM_ENDING)
    add_to_errors(create_error_with_linecolumn(
        LEXER_STATE, "Comment is not openned or already closed", false,
        lexer.row, lexer.col));
  else
    add_to_errors(create_error_with_linecolumn(LEXER_STATE, "Got error symbol",
                                               true, lexer.row, lexer.col));
  inp(__input_file);
}