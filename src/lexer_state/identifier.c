#include <stdbool.h>

#include "identifier.h"
#include "token_structure.h"

Identifier *_identifiers = NULL;
size_t identifierCount = 0;

void add_to_identifiers(Identifier identifier) {
  identifierCount++;
  _identifiers =
      (Token *)realloc(_identifiers, identifierCount * sizeof(Identifier));
  if (_identifiers == NULL)
    add_to_errors(create_error_with_linecolumn(
        MEMORY_ACCESS, "Cannot reallocate *_identifiers", true, identifier.row,
        identifier.col));
  else
    _identifiers[identifierCount - 1] = identifier;
}

bool is_identifier(size_t tokenCode) {
  for (size_t i = 0; i < identifierCount; i++)
    if (tokenCode == _identifiers[i].code)
      return true;

  return false;
}