#ifndef SYMBOL_TYPE_H
#define SYMBOL_TYPE_H

/*
@symbolType
*/
#define SYMBOL_START 0
#define SYMBOL_WS 1
#define SYMBOL_DIG 2
#define SYMBOL_LET 3
#define SYMBOL_DM1 4
#define SYMBOL_DM2 5
#define SYMBOL_COM_BEGIN 6
#define SYMBOL_COM_CONFIRM 7
#define SYMBOL_COM_ENDING 8
#define SYMBOL_ERROR 10 // 0xA Unknown symbol
#define SYMBOL_EOF 11   // 0xB End of file symbol

unsigned short int symbol_type(char symbol);

#endif