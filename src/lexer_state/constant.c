#include <stdbool.h>

#include "constant.h"
#include "error.h"
#include "token_structure.h"

Constant *_constants = NULL;
size_t constantCount = 0;

void add_to_constants(Constant constant) {
  constantCount++;
  _constants = (Token *)realloc(_constants, constantCount * sizeof(Token));
  if (_constants == NULL)
    add_to_errors(create_error_with_linecolumn(
        MEMORY_ACCESS, "Cannot reallocate *_constants", true, constant.row,
        constant.col));
  else
    _constants[constantCount - 1] = constant;
}

bool is_constant(size_t tokenCode) {
  for (size_t i = 0; i < constantCount; i++)
    if (tokenCode == _constants[i].code)
      return true;

  return false;
}