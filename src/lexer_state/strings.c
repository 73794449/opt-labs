#include <stdbool.h>

#include "error.h"
#include "strings.h"
#include "token_structure.h"

Stringy *_strings = NULL;
size_t stringsCount = 0;

void add_to_strings(Stringy str) {
  stringsCount++;
  _strings = (Token *)realloc(_strings, stringsCount * sizeof(Stringy));
  if (_strings == NULL)
    add_to_errors(create_error_with_linecolumn(
        MEMORY_ACCESS, "Cannot reallocate *_strings", true, str.row, str.col));

  else
    _strings[stringsCount - 1] = str;
}

bool is_stringy(size_t tokenCode) {
  for (size_t i = 0; i < stringsCount; i++)
    if (tokenCode == _strings[i].code)
      return true;

  return false;
}