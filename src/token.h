#ifndef TOKEN_H
#define TOKEN_H
#include "token_structure.h"
#include "error.h"

extern Token *_tokens;
extern size_t tokenCount;

void add_to_tokens(Token token);
#endif