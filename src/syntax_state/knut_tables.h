#ifndef KNUT_TABLES_H
#define KNUT_TABLES_H
#include <stdbool.h>
#include <stdlib.h>

struct code {
  size_t addrTo;
  char *_term;
  bool isTerm;
};
typedef struct code Code;

struct line {
  size_t addr;
  Code code;
  bool atAddr;
  size_t afAddr;
};
typedef struct line Line;

struct table {
  size_t linesCount;
  Line *lines;
};
typedef struct table Table;

Table create_knut_table();
char *name_by_id(size_t addr);

#endif