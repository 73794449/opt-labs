#include "symbol_type.h"
#include <stdio.h>

unsigned short int symbol_type(char symbol) {
  unsigned short int category = 6;
  if ((symbol > 7 && symbol < 14) || symbol == 32)
    category = SYMBOL_WS;
  else if (symbol > 47 && symbol < 58)
    category = SYMBOL_DIG;
  else if (symbol > 64 && symbol < 91)
    category = SYMBOL_LET;
  else if (symbol == '.' || symbol == ';' || symbol == '[' || symbol == ']' ||
           symbol == '=' || symbol == '+' || symbol == '-')
    category = SYMBOL_DM1;
  else if (symbol == ':' || symbol == '<' || symbol == '>' || symbol == '/' ||
           symbol == '\\')
    category = SYMBOL_DM2;
  else if (symbol == '(')
    category = SYMBOL_COM_BEGIN;
  else if (symbol == EOF)
    category = SYMBOL_EOF;
  else
    category = SYMBOL_ERROR;

  return category;
}