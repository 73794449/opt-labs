#include "token_structure.h"
#ifndef OUT_H
#define OUT_H
#include "cli.h"
#include "error.h"
void print_params();
void print_error(Error error);
void print_errors();
void print_lexer();
void print_token(Token token);
void print_tokens();
void out_file_lexer();
void print_file_out();
void out_file_errors();
#endif