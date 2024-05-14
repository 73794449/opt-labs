#include "knut_tables.h"
#include "tree.h"

#ifndef SYNTAX_H
#define SYNTAX_H

extern Tree *_tree;
void proc_syntax();

struct probably {
  Tree *result;
  bool status;
};
typedef struct probably ProbablyResults;

ProbablyResults probe(Table table, size_t i);

Line ruler(Table table, size_t k);
#define rules(i) ruler(table, i)

#endif