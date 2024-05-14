#include "semant.h"
#include "error.h"
#include "syntax.h"
#include <stdio.h>
#include <string.h>

char **semant_final;
size_t semant_final_count = 0;

size_t codeCount = 0;
char **statementsCode;
size_t varsCount = 0;
Var *vars = NULL;
size_t skip = 0;
size_t labelCounter = 0;
size_t dived = 1;

bool iAmInConst(char *v, Const *consts, size_t constCount) {
  for (size_t i = 0; i < constCount; i++) {
    if (strcmp(consts[i].name, v) == 0)
      return true;
  }
  return false;
}

Tree *find_in_tree(Tree *cur_tree, char *value) {
  if (strcmp(cur_tree->_value, value) == 0 && skip == 0) {
    return cur_tree;
  } else {
    if (strcmp(cur_tree->_value, value) == 0)
      skip--;
    if (cur_tree->branchesCount != 0) {
      for (size_t i = 0; i < cur_tree->branchesCount; i++) {
        Tree *temp = find_in_tree(cur_tree->_branches[i], value);
        if (temp != NULL) {
          return temp;
        }
      }
      return NULL;
    } else
      return NULL;
  }
}

bool existInVars(char *v) {
  for (size_t i = 0; i < varsCount; i++) {
    if (strcmp(vars[i].name, v) == 0)
      return true;
  }
  return false;
}

void add_to_vars(Var v) {
  vars = (Var *)realloc(vars, sizeof(Var) * varsCount);
  if (vars == NULL)
    add_to_errors(create_error_without_linecolumn(MEMORY_ACCESS,
                                                  "Cannot realloc vars", true));
  else
    vars[varsCount - 1] = v;
}

char **add_to_statements(char *value) {
  codeCount++;
  statementsCode = (char **)realloc(statementsCode, sizeof(value) * codeCount);
  if (statementsCode == NULL)
    add_to_errors(create_error_without_linecolumn(
        MEMORY_ACCESS, "Cannot realloc statementsCode", true));
  else {
    statementsCode[codeCount - 1] = malloc(sizeof(char) * strlen(value));
    strcpy(statementsCode[codeCount - 1], value);
  }

  return statementsCode;
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

char **process_summands_list(Tree *list, char *reg) {
  if (strcmp(list->_branches[0]->_value, "<empty>") == 0) {
    return statementsCode;
  } else {
    char v[100];
    if (strcmp(list->_branches[0]->_branches[0]->_value, "+") == 0) {
      if (strcmp(list->_branches[1]->_branches[0]->_branches[0]->_value,
                 "<identifier>") == 0) {
        snprintf(v, 100, "\taddq\t%s, %%%s",
                 list->_branches[1]
                     ->_branches[0]
                     ->_branches[0]
                     ->_branches[0]
                     ->_value,
                 reg);
        snprintf(v, 100, "%s",
                 list->_branches[1]
                     ->_branches[0]
                     ->_branches[0]
                     ->_branches[0]
                     ->_value);
        if (!existInVars(v)) {
          char msg[200];
          snprintf(msg, 200, "Variable %s is not declared",
                   list->_branches[1]
                       ->_branches[0]
                       ->_branches[0]
                       ->_branches[0]
                       ->_value);
          add_to_errors(
              create_error_without_linecolumn(SEMANT_STATE, msg, true));
        }
      } else
        snprintf(v, 100, "\taddq\t$%s, %%%s",
                 list->_branches[1]->_branches[0]->_branches[0]->_value, reg);

      statementsCode = add_to_statements(v);
    } else {
      if (strcmp(list->_branches[1]->_branches[0]->_branches[0]->_value,
                 "<identifier>") == 0) {
        snprintf(v, 100, "\tsubq\t%s, %%%s",
                 list->_branches[1]
                     ->_branches[0]
                     ->_branches[0]
                     ->_branches[0]
                     ->_value,
                 reg);
        if (!existInVars(v)) {
          char msg[200];
          snprintf(msg, 200, "Variable %s is not declared",
                   list->_branches[1]
                       ->_branches[0]
                       ->_branches[0]
                       ->_branches[0]
                       ->_value);
          add_to_errors(
              create_error_without_linecolumn(SEMANT_STATE, msg, true));
        }
      } else
        snprintf(v, 100, "\tsubq\t$%s, %%%s",
                 list->_branches[1]->_branches[0]->_branches[0]->_value, reg);
      statementsCode = add_to_statements(v);
    }
    if (list->branchesCount == 3) {
      statementsCode = process_summands_list(list->_branches[2], reg);
    }

    return statementsCode;
  }
}

char **process_expression(Tree *expression, char *reg) {
  char v[100];
  size_t start_for_list = 0;
  if (strcmp(expression->_branches[0]->_value, "-") == 0) {
    snprintf(v, 100, "\tmovq\t$0, %%%s", reg);
    statementsCode = add_to_statements(v);
    snprintf(v, 100, "\tsubq\t$%s, %%%s",
             expression->_branches[1]->_branches[0]->_branches[0]->_value, reg);
    statementsCode = add_to_statements(v);
    start_for_list = 2;
  } else {
    if (strcmp(expression->_branches[0]->_branches[0]->_branches[0]->_value,
               "<identifier>") == 0) {
      snprintf(v, 100, "%s",
               expression->_branches[0]
                   ->_branches[0]
                   ->_branches[0]
                   ->_branches[0]
                   ->_value);
      if (!existInVars(v)) {
        char msg[200];
        snprintf(msg, 200, "Variable %s is not declared",
                 expression->_branches[0]
                     ->_branches[0]
                     ->_branches[0]
                     ->_branches[0]
                     ->_value);
        add_to_errors(create_error_without_linecolumn(SEMANT_STATE, msg, true));
        snprintf(v, 100, "\tmovq\t%s, %%%s",
                 expression->_branches[0]
                     ->_branches[0]
                     ->_branches[0]
                     ->_branches[0]
                     ->_value,
                 reg);
      }
    } else {
      snprintf(v, 100, "\tmovq\t$%s, %%%s",
               expression->_branches[0]->_branches[0]->_branches[0]->_value,
               reg);
    }
    statementsCode = add_to_statements(v);
    start_for_list = 1;
  }
  for (size_t i = start_for_list; i < expression->branchesCount; i++) {
    statementsCode = process_summands_list(expression->_branches[i], reg);
  }

  return statementsCode;
}

void process_statement(Tree *stats) {
  Var v;
  v.name = stats->_branches[0]->_branches[0]->_branches[0]->_value;
  v.value = "8";
  process_expression(stats->_branches[2], "rax");
  varsCount++;
  add_to_vars(v);
  char val[100];
  snprintf(val, 100, "\tmovq\t%%rax, %s", v.name);
  add_to_statements(val);
}

void dive_alternatives(Tree *my_tree, Tree *parent, char *val) {
  if (strcmp(my_tree->_value, "<expression>") == 0) {
    if (parent != NULL) {
      if (strcmp(parent->_value, val) == 0 &&
          strcmp("<alternative>", val) == 0) {
        process_expression(my_tree, "rbx");
        char v[100];
        snprintf(v, 100, "\tcmpq\t%%rax, %%rbx");
        add_to_statements(v);
        snprintf(v, 100, "\tje\t?L%llu", labelCounter++);
        add_to_statements(v);
      } else if (strcmp(parent->_value, val) == 0 &&
                 strcmp("<statement>", val) == 0 && dived == 0) {
        char v[100];
        snprintf(v, 100, "?L%llu: NOP", labelCounter++);
        add_to_statements(v);
        process_statement(parent);
      } else if (strcmp(parent->_value, val) == 0 &&
                 strcmp("<statement>", val) == 0) {
        dived--;
      }
    }
  } else {
    for (size_t i = 0; i < my_tree->branchesCount; i++) {
      dive_alternatives(my_tree->_branches[i], my_tree, val);
    }
  }
}

void proc_semant() {

  Tree *constDeclars = find_in_tree(_tree, "<constant-declarations>");
  size_t constCount = constDeclars->_branches[1]->branchesCount;
  Const *consts = (Const *)malloc(constCount * sizeof(Const));
  for (size_t i = 0; i < constCount; i++) {
    skip = i;
    Tree *constDeclar = find_in_tree(constDeclars, "<constant-declaration>");
    consts[i].name =
        constDeclar->_branches[0]->_branches[0]->_branches[0]->_value;
    consts[i].value =
        constDeclar->_branches[2]->_branches[0]->_branches[0]->_value;
  }

  Tree *statements = find_in_tree(_tree, "<statements-list>");
  size_t statementsCount = statements->branchesCount;
  Tree **stats = (Tree **)malloc(statementsCount * sizeof(Tree *));
  for (size_t i = 0; i < statementsCount; i++) {
    skip = i;
    stats[i] = find_in_tree(statements, "<statement>");
  }
  for (size_t i = 0; i < statementsCount; i++) {
    if (strcmp(stats[i]->_branches[0]->_value, "CASE") == 0) {
      char v[100];
      process_expression(stats[i]->_branches[1], "rax");
      size_t labelCounterBackup = labelCounter;
      dive_alternatives(stats[i], NULL, "<alternative>");
      snprintf(v, 100, "\tjmp\t?L%llu", labelCounter++);
      add_to_statements(v);
      labelCounter = labelCounterBackup;
      dive_alternatives(stats[i], NULL, "<statement>");
      snprintf(v, 100, "?L%llu: NOP", labelCounter++);
      add_to_statements(v);

    } else if (strcmp(stats[i]->_branches[0]->_value,
                      "<variable-identifier>") == 0) {
      process_statement(stats[i]);
    } else {
      add_to_errors(create_error_without_linecolumn(
          SEMANT_STATE, "Impossible statement", true));
    }
  }

  Tree *name = find_in_tree(_tree, "<procedure-identifier>");
  char *program_name = name->_branches[0]->_branches[0]->_value;

  char v[100];
  snprintf(v, 100, ".section .rodata");
  add_to_semant_final_program(v);
  for (size_t i = 0; i < constCount; i++) {
    snprintf(v, 100, "\t%s:\t.quad %s", consts[i].name, consts[i].value);
    add_to_semant_final_program(v);
  }

  snprintf(v, 100, "\n");
  add_to_semant_final_program(v);

  snprintf(v, 100, ".section .bbs");
  add_to_semant_final_program(v);
  for (size_t i = 0; i < varsCount; i++) {
    snprintf(v, 100, "\t%s:\t.space %s", vars[i].name, vars[i].value);
    add_to_semant_final_program(v);
  }

  snprintf(v, 100, "\n");
  add_to_semant_final_program(v);
  snprintf(v, 100, ".section .text");
  add_to_semant_final_program(v);
  snprintf(v, 100, ".globl main");
  add_to_semant_final_program(v);
  snprintf(v, 100, "main:");
  add_to_semant_final_program(v);
  snprintf(v, 100, "\tjmp %s", program_name);
  add_to_semant_final_program(v);
  snprintf(v, 100, "%s:", program_name);
  add_to_semant_final_program(v);

  for (size_t i = 0; i < codeCount; i++)
    add_to_semant_final_program(statementsCode[i]);

  snprintf(v, 100, "\tmovq\t$60, %%rax");
  add_to_semant_final_program(v);
  snprintf(v, 100, "\txor\t%%rdi, %%rdi");
  add_to_semant_final_program(v);
  snprintf(v, 100, "\tsyscall");
  add_to_semant_final_program(v);

  for(size_t i = 0; i < varsCount; i++)
  {
    if(iAmInConst(vars[i].name,consts,constCount))
    {
        char msg[200];
        snprintf(msg, 200, "Variable %s has bad name, CONST already use it",
                 vars[i].name);
        add_to_errors(create_error_without_linecolumn(SEMANT_STATE, msg, true));
    }
  }
}