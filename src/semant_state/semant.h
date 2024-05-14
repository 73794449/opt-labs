#include <stdlib.h>
#ifndef SEMANT_H
#define SEMANT_H

struct var{
    char* name;
    char* value;
};
typedef struct var Var;

struct cnst{
    char* name;
    char* value;
};
typedef struct cnst Const;

void proc_semant();

extern char **semant_final;
extern size_t semant_final_count;

#endif