#include "error.h"
#include "semant.h"
#include <stdio.h>
#include <string.h>

void add_to_const(Const c) {
  if (!iAmInConst(c.name) && !iAmProgram(c.name)) {
    constCount++;
    consts = (Const *)realloc(consts, sizeof(Const) * constCount);
    if (consts == NULL)
      add_to_errors(create_error_without_linecolumn(
          MEMORY_ACCESS, "Cannot realloc consts", true));
    else {
      consts[constCount - 1] = c;
    }
  } else {
    char val[100];
    snprintf(val, 100, "Cannot create const %s, name used by CONST or PROGRAM",
             c.name);
    add_to_errors(create_error_without_linecolumn(SEMANT_STATE, val, true));
  }
}

void add_to_vars(Var v) {
  if (!iAmInConst(v.name) && !iAmProgram(v.name)) {
    varsCount++;
    vars = (Var *)realloc(vars, sizeof(Var) * varsCount);
    if (vars == NULL)
      add_to_errors(create_error_without_linecolumn(
          MEMORY_ACCESS, "Cannot realloc vars", true));
    else
      vars[varsCount - 1] = v;
  } else {
    char val[100];
    snprintf(val, 100, "Cannot create var %s, name used by CONST or PROGRAM",
             v.name);
    add_to_errors(create_error_without_linecolumn(SEMANT_STATE, val, true));
  }
}

void add_to_statements(char *value) {
  codeCount++;
  statementsCode = (char **)realloc(statementsCode, sizeof(value) * codeCount);
  if (statementsCode == NULL)
    add_to_errors(create_error_without_linecolumn(
        MEMORY_ACCESS, "Cannot realloc statementsCode", true));
  else {
    statementsCode[codeCount - 1] = malloc(sizeof(char) * strlen(value));
    strcpy(statementsCode[codeCount - 1], value);
  }
}

char **add_to_semant_final_program(char *value) {
  semant_final_count++;
  semant_final =
      (char **)realloc(semant_final, sizeof(value) * semant_final_count);
  if (semant_final == NULL)
    add_to_errors(create_error_without_linecolumn(
        MEMORY_ACCESS, "Cannot realloc semant_final", true));
  else {
    semant_final[semant_final_count - 1] = malloc(sizeof(char) * strlen(value));
    strcpy(semant_final[semant_final_count - 1], value);
  }

  return semant_final;
}