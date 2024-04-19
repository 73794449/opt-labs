#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "constant.h"
#include "error.h"
#include "identifier.h"
#include "knut_tables.h"
#include "strings.h"
#include "syntax.h"
#include "terms.h"
#include "token.h"

t_tree* _tree;

size_t token_i = 0;

struct probe_res {
  t_tree* result;
  bool status;
};
typedef struct probe_res PR;

PR probe(KNUT knut_table, size_t i);
KL ruler(KNUT table, size_t k) {
  for (size_t i = 0; i < table.lines_count; i++) {
    if (table.lines[i].addr == k) {
      return table.lines[i];
    }
  }
  exit(0);
}

#define rules(i) ruler(knut_table, i)
void proc_syntax() {
  KNUT knut_table = create_knut_table();
  size_t k = 3;
  _tree = create_node(name_by_id(SIGNAL_PROGRAM), 0);
  PR run = probe(knut_table, k);
  if (run.status) add_branch(_tree, run.result);
}

PR probe(KNUT knut_table, size_t i) {
  bool state = false;
  t_tree* new_one = create_node(name_by_id(i), i);
  bool AT_NOT_FINISHED = true;
  do {
    if (!rules(i).code.is_term) {
      PR inner_probe = probe(knut_table, rules(i).code.addr_to);
      if (inner_probe.status == true) {
        if (rules(i).AT != true)
          i++;
        else
          AT_NOT_FINISHED = false;
        add_branch(new_one, inner_probe.result);
        state = true;
      } else {
        if (rules(i).AF_ADDR != ERROR) {
          i = rules(i).AF_ADDR;
          state = true;
        } else {
          state = false;
        }
      }
    } else {
      state = false;
      switch (rules(i).addr) {
        case UNSIGNED_INTEGER:
          if (is_constant(_tokens[token_i].code)) {
            add_branch(new_one, create_node(_tokens[token_i]._data, i));
            state = true;
          }
          break;
        case IDENTIFIER:
          if (is_identifier(_tokens[token_i].code)) {
            add_branch(new_one, create_node(_tokens[token_i]._data, i));
            state = true;
          }
          break;
        case STRING:
          if (is_stringy(_tokens[token_i].code)) {
            add_branch(new_one, create_node(_tokens[token_i]._data, i));
            state = true;
          }
          break;
        case EMPTY:
          add_branch(new_one, create_node(name_by_id(EMPTY), i));
          state = true;
          break;
        default:
          if (strcmp(rules(i).code.term, _tokens[token_i]._data) == 0) {
            add_branch(new_one, create_node(_tokens[token_i]._data, i));
            state = true;
          }
      };
      if (state == false) {
        if (rules(i).AF_ADDR != ERROR) {
          i = rules(i).AF_ADDR;
          state = true;
        } else {
          if(rules(i).addr < 100){
            add_to_errors(create_error_syntaxer(
                _tokens[token_i].row, _tokens[token_i].col, rules(i).code.term,
                _tokens[token_i]._data));
            break;
          }
        }
      } else {
        if (rules(i).addr != EMPTY) token_i++;
        if (rules(i).addr < 100 && rules(i).AT != true)
          i++;
        else
          AT_NOT_FINISHED = false;
      }
    }

  } while (AT_NOT_FINISHED && state && errorCount < 1);
  PR ret = {new_one, state};
  return ret;
}