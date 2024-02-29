#include "token_structure.h"
#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "error.h"
typedef struct token Identifier;
extern Identifier *_identifiers;
extern size_t identifierCount;
void add_to_identifiers(Identifier identifier);
#endif