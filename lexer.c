#include "lexer.h"
#include "error.h"
#include "token.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lexer lexer = {0, NULL, 0, 1, 1, '\0', 6, false};

unsigned int lastConst = 0;
unsigned long int lastIdentifier = 0;
char **identifiers;

void add_buffer_symbol() {
  if (lexer.state != 52) {
    lexer._buffer =
        (char *)realloc(lexer._buffer, lexer.bufferSize * sizeof(char));
    if (lexer._buffer == NULL) {
      add_to_errors(create_error_with_linecolumn(errorCount + 1, 0,
                                                 "Cannot resize *buff", true,
                                                 lexer.row, lexer.col));
    }
    lexer._buffer[lexer.bufferSize] = lexer.symbol;
    lexer.bufferSize++;
  }
}

void clean_buffer() {
  lexer._buffer = NULL;
  lexer.bufferSize = 0;
}

/*
0 - ws: whitespace(and etc.)| ASCII 8->13, 32
1 - dig: numbers| ASCII 48->57
11 - add: + or -
2 - let: identifiers and keywords| ASCII 65->90, 97->122
3 - dm1: delimeters first type
4 - dm2: delimeters second type(for 2 symbols in token)
51 - com_beg: comment begin '('
52 - com_confirm: comment confirm '*'
53 - com_end: comment end ')'
6 - err: error symbols| ASCII 0->7, 127 or any not listed here
7 - eof: end-of-file symbol| not ASCII symbol
*/
unsigned short int symbol_type(char symbol) {
  unsigned short int category = 6;
  if ((symbol > 7 && symbol < 14) || symbol == 32)
    category = 0;
  else if (symbol > 47 && symbol < 58)
    category = 1;
  else if (symbol > 64 && symbol < 91)
    category = 2;
  else if (symbol == '.' || symbol == ';' || symbol == '[' || symbol == ']' ||
           symbol == '=' || symbol == '+' || symbol == '-')
    category = 3;
  else if (symbol == '=')
    category = 31;
  else if (symbol == ':' || symbol == '<' || symbol == '>')
    category = 4;
  else if (symbol == '(')
    category = 5;
  else if (symbol == EOF)
    category = 7;
  else
    category = 6;

  return category;
}

unsigned short int is_keyword() {
  char *_verify[10] = {"PROGRAM", "VAR", "BEGIN",   "END",     "CONST",
                       "CASE",    "OF",  "ENDCASE", "INTEGER", "FLOAT"};
  for (unsigned short int i = 0; i < 10; i++) {
    if (!strcmp(lexer._buffer, _verify[i]))
      return i + 1;
  }
  return 0;
}

unsigned short int get_code_dm1() {
  char _verify[10] = {'+', '-', ':', '<', '>', '=', '.', ';', '[', ']'};
  for (unsigned short i = 0; i < 10; i++) {
    if (lexer._buffer[0] == _verify[i])
      return (unsigned short int)lexer._buffer[0];
  }
  return 0;
}
unsigned short int get_code_dm2() {
  char _verify[3] = {'<', '>', ':'};
  if (lexer._buffer[1] == '=') {
    for (unsigned short i = 0; i < 3; i++) {
      if (lexer._buffer[0] == _verify[i])
        return i + 1;
    }
  }
  return get_code_dm1();
}

unsigned long int get_code() {
  unsigned long int base = 0;
  switch (lexer.state) {
  case 1:
    base = 500;
    base += lastConst + 1;
    break;
  case 2:
    if (is_keyword()) {
      base = 400;
      base += is_keyword();
    } else {
      base = 1000;
      if (identifiers != NULL) {
        for (unsigned long int i = 0; i < lastIdentifier; i++) {
          if (!strcmp(lexer._buffer, identifiers[i])) {
            return base + i + 1;
          }
        }
      }
      identifiers =
          (char **)realloc(identifiers, (lastIdentifier + 1) * sizeof(char *));
      if (identifiers == NULL) {
        add_to_errors(create_error_with_linecolumn(
            errorCount + 1, 0, "Cannot resize **identifiers", true, lexer.row,
            lexer.col));
      }
      identifiers[lastIdentifier] = lexer._buffer;
      lastIdentifier++;
      return base + lastIdentifier;
    }
    break;
  case 3:
  case 11:
    base = 0 + get_code_dm1();
    break;
  case 4:
    base = get_code_dm2();
    if (lexer._buffer[1] == '=')
      base += 300;
    break;

  default:
    add_to_errors(create_error_without_linecolumn(
        errorCount + 1, 0, "Impossible for get_code()", true));
    return 0;
  };
  return base;
}

void inp(FILE *__input_file) {
  lexer.symbol = (char)fgetc(__input_file);
  if (lexer.symbol == '\n') {
    lexer.row++;
    lexer.col = 1;
  } else {
    if (lexer.symbol == '\t')
      lexer.col += 4;
    else {
      if (lexer.symbol == EOF) {
        lexer.state = 7;
      }
      lexer.col++;
    }
  }
  lexer.symbolType = symbol_type(lexer.symbol);
}

void got_ws(FILE *__input_file) {
  do {
    inp(__input_file);
  } while (lexer.symbolType == 0);
  lexer.state = 0;
}
void got_dig(FILE *__input_file) {
  unsigned int row = lexer.row;
  unsigned int col = lexer.col;
  lexer.state = 1;
  do {
    add_buffer_symbol();
    inp(__input_file);
  } while (lexer.symbolType == 1);

  add_to_tokens(
      create_token(row, col, get_code(), lexer._buffer, lexer.bufferSize));
  clean_buffer();
}
void got_let(FILE *__input_file) {
  unsigned int row = lexer.row;
  unsigned int col = lexer.col;
  lexer.state = 2;
  do {
    add_buffer_symbol();
    inp(__input_file);
  } while (lexer.symbolType == 1 || lexer.symbolType == 2);

  add_to_tokens(
      create_token(row, col, get_code(), lexer._buffer, lexer.bufferSize));
  clean_buffer();
}
void got_dm1(FILE *__input_file) {
  unsigned int row = lexer.row;
  unsigned int col = lexer.col;
  lexer.state = 3;
  add_buffer_symbol();
  inp(__input_file);
  add_to_tokens(
      create_token(row, col, get_code(), lexer._buffer, lexer.bufferSize));
  clean_buffer();
}

void got_dm2(FILE *__input_file) {
  unsigned int row = lexer.row;
  unsigned int col = lexer.col;
  lexer.state = 4;
  add_buffer_symbol();
  inp(__input_file);
  if (lexer.symbolType == 3) {
    add_buffer_symbol();
    inp(__input_file);
  }
  add_to_tokens(
      create_token(row, col, get_code(), lexer._buffer, lexer.bufferSize));
  clean_buffer();
}

void got_com(FILE *__input_file, unsigned int row, unsigned int col);
void got_ecom(FILE *__input_file, unsigned int row, unsigned int col);

void got_com_beg(FILE *__input_file) {
  lexer.state = 51;
  unsigned int row = lexer.row;
  unsigned int col = lexer.col;
  inp(__input_file);
  if (lexer.symbol == '*') {
    lexer.com = true;
    got_com(__input_file, row, col);
  } else {
    add_to_errors(create_error_with_linecolumn((errorCount + 1), 0,
                                               "No * after (", true, row, col));
    inp(__input_file);
  }
}

void got_com(FILE *__input_file, unsigned int row, unsigned int col) {
  inp(__input_file);
  if (lexer.symbol == '*') {
    got_ecom(__input_file, row, col);
  } else {
    if (lexer.symbolType == 7) {
      add_to_errors(create_error_with_linecolumn(
          errorCount + 1, 0, "Not closed comment", true, row, col));
      inp(__input_file);
    } else {
      got_com(__input_file, row, col);
    }
  }
}

void got_ecom(FILE *__input_file, unsigned int row, unsigned int col) {
  inp(__input_file);
  if (lexer.symbol == ')') {
    inp(__input_file);
    lexer.state = 0;
    lexer.com = false;
  } else {
    if (lexer.symbol == '*')
      got_ecom(__input_file, row, col);
    else {
      if (lexer.symbolType == 7) {
        add_to_errors(create_error_with_linecolumn(
            errorCount + 1, 0, "Not closed comment", true, row, col));
        inp(__input_file);
      } else
        got_com(__input_file, row, col);
    }
  }
}

void proc_lexer(char *_input_file) {
  FILE *__input_file;
  __input_file = fopen(_input_file, "r");
  if (__input_file == NULL) {
    add_to_errors(create_error_without_linecolumn(
        (errorCount + 1), -1, "Cannot open input file.", true));
  } else {
    lexer.state = 8;
    inp(__input_file);
    do {
      switch (lexer.symbolType) {
      case 0:
        got_ws(__input_file);
        break;
      case 1:
        got_dig(__input_file);
        break;
      case 2:
        got_let(__input_file);
        break;
      case 3:
      case 31:
        got_dm1(__input_file);
        break;
      case 4:
        got_dm2(__input_file);
        break;
      case 5:
        got_com_beg(__input_file);
        break;
      case 6:
        if (lexer.symbol == '*' || lexer.symbol == ')')
          add_to_errors(create_error_with_linecolumn(
              errorCount + 1, 0, "Comment is not openned or already closed",
              false, lexer.row, lexer.col));
        else
          add_to_errors(create_error_with_linecolumn((errorCount + 1), 0,
                                                     "Got error symbol", true,
                                                     lexer.row, lexer.col));
        inp(__input_file);
        break;
      case 7:
        lexer.state = 7;
        break;
      default:
        add_to_errors(create_error_without_linecolumn(
            errorCount + 1, 0, "Impossible if rrly, unknown category", true));
        break;
      };
    } while (lexer.state != 7);
  }
}
