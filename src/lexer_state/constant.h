#include <stdbool.h>
#include <stddef.h>

#include "token_structure.h"
#ifndef CONSTANT_H
#define CONSTANT_H

typedef struct token Constant;

extern Constant *_constants;
extern size_t constantCount;

void add_to_constants(Constant constant);
bool is_constant(size_t tokenCode);

#endif