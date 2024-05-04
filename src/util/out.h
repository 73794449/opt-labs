#include "cli.h"
#include "error.h"
#include "token_structure.h"
#ifndef OUT_H
#define OUT_H

void print_params();
void print_error(Error error);
void print_errors();
void print_lexer();
void print_token(Token token);
void print_tokens();
void out_file_lexer();
void print_file_out();
void out_file_errors();
void out_file_syntax();
void just_clean();
void free_trees();
void free_errors();
void free_tokens();
void free_tables();

#endif