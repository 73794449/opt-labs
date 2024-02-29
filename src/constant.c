#include "constant.h"
#include <stdbool.h>
#include "token_structure.h"
#include "error.h"
Constant *_constants = NULL;
size_t constantCount = 0;
void add_to_constants(Constant constant)
{
  constantCount++;
  _constants = (Token *)realloc(_constants, constantCount * sizeof(Token));
  if (_constants == NULL) {
    add_to_errors(create_error_with_linecolumn(errorCount + 1, MEMORY_ACCESS,
                                               "Cannot reallocate *_constants",
                                               true, constant.row, constant.col));
  } else {
    _constants[constantCount - 1] = constant;
  }
}