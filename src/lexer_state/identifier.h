#include "error.h"
#include "token_structure.h"
#ifndef IDENTIFIER_H
#define IDENTIFIER_H

typedef struct token Identifier;
extern Identifier *_identifiers;
extern size_t identifierCount;

void add_to_identifiers(Identifier identifier);
bool is_identifier(size_t tokenCode);

#endif