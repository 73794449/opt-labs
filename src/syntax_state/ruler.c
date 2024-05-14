#include "syntax.h"

Line ruler(Table table, size_t k) {
  for (size_t i = 0; i < table.linesCount; i++)
    if (table.lines[i].addr == k)
      return table.lines[i];

  exit(EXIT_FAILURE);
}