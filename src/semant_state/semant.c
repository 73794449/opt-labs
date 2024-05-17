#include "semant.h"
#include "error.h"
#include <stdio.h>
#include <string.h>

char **semant_final = NULL;
size_t semant_final_count = 0;

char *program_name = NULL;
Const *consts = NULL;
size_t constCount = 0;

Var *vars = NULL;
size_t varsCount = 0;

char **statementsCode = NULL;
size_t codeCount = 0;

size_t skip = 0;
size_t labelCounter = 0;
size_t dived = 1;

#define macro_bbb(val, x, y, z) val->_branches[x]->_branches[y]->_branches[z]
#define macro_bbbb(val, x, y, z, k)                                            \
  val->_branches[x]->_branches[y]->_branches[z]->_branches[k]

void process_summands_list(Tree *list, char *reg) {
  char v[100];
  char err[200];
  if (strcmp(list->_branches[0]->_value, "<empty>") == 0) {

  } else {
    if (strcmp(list->_branches[0]->_value, "+") == 0) {
      if (strcmp(macro_bbb(list, 1, 0, 0)->_value, "<identifier>") == 0) {
        snprintf(v, 100, "\taddq\t%s, %%%s",
                 macro_bbbb(list, 1, 0, 0, 0)->_value, reg);
        if (!iAmInVars(macro_bbbb(list, 1, 0, 0, 0)->_value)) {
          snprintf(err, 200, "Variable %s used before declaration",
                   macro_bbbb(list, 1, 0, 0, 0)->_value);
          add_to_errors(
              create_error_without_linecolumn(SEMANT_STATE, err, true));
        }
      } else
        snprintf(v, 100, "\taddq\t%s, %%%s", macro_bbb(list, 1, 0, 0)->_value,
                 reg);
    } else {
      if (strcmp(macro_bbb(list, 1, 0, 0)->_value, "<identifier>") == 0) {
        snprintf(v, 100, "\tsubq\t%s, %%%s",
                 macro_bbbb(list, 1, 0, 0, 0)->_value, reg);
        if (!iAmInVars(macro_bbbb(list, 1, 0, 0, 0)->_value)) {
          snprintf(err, 200, "Variable %s used before declaration",
                   macro_bbbb(list, 1, 0, 0, 0)->_value);
          add_to_errors(
              create_error_without_linecolumn(SEMANT_STATE, err, true));
        }
      } else
        snprintf(v, 100, "\tsubq\t%s, %%%s", macro_bbb(list, 1, 0, 0)->_value,
                 reg);
    }
    add_to_statements(v);
    if (list->branchesCount == 3) {
      process_summands_list(list->_branches[2], reg);
    }
  }
}

void process_expression(Tree *expression, char *reg) {
  char v[100];
  char err[200];
  if (strcmp(expression->_branches[0]->_value, "<summand>") == 0) {
    if (strcmp(macro_bbb(expression, 0, 0, 0)->_value, "<identifier>") == 0) {
      snprintf(v, 100, "\tmovq\t%s, %%%s",
               macro_bbbb(expression, 0, 0, 0, 0)->_value, reg);
      if (!iAmInVars(macro_bbbb(expression, 0, 0, 0, 0)->_value)) {
        snprintf(err, 200, "Variable %s used before declaration",
                 macro_bbbb(expression, 0, 0, 0, 0)->_value);
        add_to_errors(create_error_without_linecolumn(SEMANT_STATE, err, true));
      }
    } else
      snprintf(v, 100, "\tmovq\t%s, %%%s",
               macro_bbb(expression, 0, 0, 0)->_value, reg);
    add_to_statements(v);
    process_summands_list(expression->_branches[1], reg);
  } else {
    snprintf(v, 100, "\tmovq\t$0, %%%s", reg);
    add_to_statements(v);
    if (strcmp(macro_bbb(expression, 0, 1, 0)->_value, "<identifier>") == 0) {
      snprintf(v, 100, "\tmovq\t%s, %%%s",
               macro_bbbb(expression, 0, 1, 0, 0)->_value, reg);
      if (!iAmInVars(macro_bbbb(expression, 0, 1, 0, 0)->_value)) {
        snprintf(err, 200, "Variable %s used before declaration",
                 macro_bbbb(expression, 0, 1, 0, 0)->_value);
        add_to_errors(create_error_without_linecolumn(SEMANT_STATE, err, true));
      }
    } else
      snprintf(v, 100, "\tmovq\t%s, %%%s",
               macro_bbb(expression, 0, 1, 0)->_value, reg);
    process_summands_list(expression->_branches[2], reg);
  }
}

void process_statement(Tree *stats) {
  Var v;
  v.name = macro_bbb(stats, 0, 0, 0)->_value;
  v.value = "8";
  process_expression(stats->_branches[2], "rax");
  add_to_vars(v);
  char val[100];
  snprintf(val, 100, "\tmovq\t%%rax, %s", v.name);
  add_to_statements(val);
}
size_t labelCounterBackup = 0;
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
        snprintf(v, 100, "\tjmp\t?L%llu", labelCounterBackup);
        add_to_statements(v);
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

void proc_name() {
  Tree *name = find_in_tree(_tree, "<procedure-identifier>");
  program_name = name->_branches[0]->_branches[0]->_value;
}

void proc_const(Tree *cur_tree) {
  Tree *constDeclars = find_in_tree(cur_tree, "<constant-declarations-list>");
  if (constDeclars != NULL) {
    Const c;
    c.name = macro_bbbb(constDeclars, 0, 0, 0, 0)->_value;
    c.value = macro_bbbb(constDeclars, 0, 2, 0, 0)->_value;
    add_to_const(c);
    proc_const(constDeclars->_branches[1]);
  }
}

void proc_statements(Tree *cur_tree) {
  Tree *statementDeclars = find_in_tree(cur_tree, "<statements-list>");
  if (statementDeclars != NULL) {

    if (strcmp(statementDeclars->_branches[0]->_branches[0]->_value, "CASE") ==
        0) {
      char v[100];
      process_expression(statementDeclars->_branches[0]->_branches[1], "rax");
      dive_alternatives(statementDeclars->_branches[0], NULL, "<alternative>");
      labelCounterBackup = labelCounter;
      snprintf(v, 100, "\tjmp\t?L%llu", labelCounter++);
      add_to_statements(v);
      labelCounter = 0;
      dive_alternatives(statementDeclars->_branches[0], NULL, "<statement>");
      labelCounter = labelCounterBackup;
      snprintf(v, 100, "?L%llu: NOP", labelCounter++);
      add_to_statements(v);

    } else if (strcmp(statementDeclars->_branches[0]->_branches[0]->_value,
                      "<variable-identifier>") == 0) {
      process_statement(statementDeclars->_branches[0]);
    } else {
      add_to_errors(create_error_without_linecolumn(
          SEMANT_STATE, "Impossible statement", true));
    }
    proc_statements(statementDeclars->_branches[1]);
  }
}

void proc_semant() {
  proc_name();
  proc_const(_tree);
  proc_statements(_tree);
  generate_final_output();
}