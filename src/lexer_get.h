#include <stdio.h>
#include <bits/types.h>
#ifndef LEXER_GET_H
#define LEXER_GET_H
#include "lexer_structure.h"
#include "token.h"
#include "error.h"

__uint8_t symbol_type(char symbol);
void inp(FILE *__input_file);
void ws(FILE *__input_file);
void dig(FILE *__input_file);
void let(FILE *__input_file);
void dm1(FILE *__input_file);
void dm2(FILE *__input_file);
void com_begin(FILE *__input_file);
void com_confirm(FILE *__input_file,size_t row, size_t col);
void com_ending(FILE *__input_file,size_t row, size_t col);
void s_error(FILE *__input_file);
#endif