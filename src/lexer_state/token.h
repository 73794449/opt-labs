#include "error.h"
#include "token_structure.h"

#ifndef TOKEN_H
#define TOKEN_H

extern Token *_tokens;
extern size_t tokenCount;

void add_to_tokens(Token token);

#endif