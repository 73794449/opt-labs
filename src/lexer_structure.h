#ifndef LEXER_STRUCTURE_H
#define LEXER_STRUCTURE_H
#include <stdbool.h>
#include <stddef.h>
#include <bits/types.h>
struct lexer {
  char *_buffer;
  size_t bufferSize;
  size_t row;
  size_t col;
  char symbol;
  __uint8_t symbolType;
  bool inComment;
};
typedef struct lexer Lexer;
extern Lexer lexer;
/*
@symbolType
*/
#define SYMBOL_START            0
#define SYMBOL_WS               1
#define SYMBOL_DIG              2
#define SYMBOL_LET              3
#define SYMBOL_DM1              4
#define SYMBOL_DM2              5
#define SYMBOL_COM_BEGIN        6
#define SYMBOL_COM_CONFIRM      7     
#define SYMBOL_COM_ENDING       8     
#define SYMBOL_ERROR            10    //0xA Unknown symbol
#define SYMBOL_EOF              11    //0xB End of file symbol


void add_buffer_symbol();
void clean_buffer();
#endif