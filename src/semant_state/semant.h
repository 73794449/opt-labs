#include <stdlib.h>
#include "syntax.h"
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


extern Const *consts;
extern size_t constCount;

extern Var *vars;
extern size_t varsCount;

extern char **statementsCode;
extern size_t codeCount;

extern char* program_name;

void proc_semant();

void generate_final_output();
bool iAmInConst(char *v);
bool iAmProgram(char *v);
bool iAmInVars(char *v);

void add_to_const(Const c);
void add_to_vars(Var v);
void add_to_statements(char *value);
char **add_to_semant_final_program(char *value);


extern size_t skip;
Tree *find_in_tree(Tree *cur_tree, char *value);


extern char **semant_final;
extern size_t semant_final_count;

#endif