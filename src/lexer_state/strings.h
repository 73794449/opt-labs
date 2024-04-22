#include <stdbool.h>
#include <stddef.h>

#include "token_structure.h"

#ifndef STRINGS_H
#define STRINGS_H

typedef struct token Stringy;
extern Stringy *_strings;
extern size_t stringsCount;

void add_to_strings(Stringy str);
bool is_stringy(size_t tokenCode);

#endif