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

Tree* _tree;

size_t tokenIterator = 0;
char* _expected;

Line ruler(Table table, size_t k) {
  for (size_t i = 0; i < table.linesCount; i++)
    if (table.lines[i].addr == k) return table.lines[i];

  exit(EXIT_FAILURE);
}
#define rules(i) ruler(table, i)

void proc_syntax() {
  Table table = create_knut_table();
  _tree = create_node(name_by_id(SIGNAL_PROGRAM), SIGNAL_PROGRAM);
  ProbablyResults run = probe(table, PROGRAM);
  if (run.status)
    add_branch(_tree, run.result);
  else
    add_to_errors(create_error_syntaxer(
        _tokens[tokenIterator].row, _tokens[tokenIterator].col,
        run.result->_value, _tokens[run.result->id]._data));
}

ProbablyResults probe(Table table, size_t i) {
  ProbablyResults ret = {false, NULL};
  bool state = false;
  Tree* newTree = create_node(name_by_id(i), i);
  size_t savedTokenPos = tokenIterator;
  bool atNotFinished = true;
  do {
    if (!rules(i).code.isTerm) {
      ProbablyResults inner_probe = probe(table, rules(i).code.addrTo);
      if (inner_probe.status == true) {
        if (rules(i).atAddr != true)
          i++;
        else
          atNotFinished = false;
        add_branch(newTree, inner_probe.result);
        state = true;
      } else {
        if (rules(i).afAddr != ERROR) {
          i = rules(i).afAddr;
          state = true;
        } else {
          state = false;
          ret.result = inner_probe.result;
          ret.status = state;
          return ret;
        }
      }
    } else {
      state = false;
      switch (rules(i).addr) {
        case UNSIGNED_INTEGER:
          if (is_constant(_tokens[tokenIterator].code)) {
            add_branch(newTree, create_node(_tokens[tokenIterator]._data, i));
            state = true;
          }
          break;
        case IDENTIFIER:
          if (is_identifier(_tokens[tokenIterator].code)) {
            add_branch(newTree, create_node(_tokens[tokenIterator]._data, i));
            state = true;
          }
          break;
        case STRING:
          if (is_stringy(_tokens[tokenIterator].code)) {
            add_branch(newTree, create_node(_tokens[tokenIterator]._data, i));
            state = true;
          }
          break;
        case EMPTY:
          add_branch(newTree, create_node(name_by_id(EMPTY), i));
          state = true;
          break;
        default:
          if (strcmp(rules(i).code._term, _tokens[tokenIterator]._data) == 0) {
            add_branch(newTree, create_node(_tokens[tokenIterator]._data, i));
            state = true;
          }
      };
      if (state == false) {
        if (rules(i).afAddr != ERROR) {
          i = rules(i).afAddr;
          state = true;
        } else {
          if(rules(i).addr < 100){
          ret.status = false;
          ret.result = create_node(rules(i).code._term, tokenIterator);
          tokenIterator=savedTokenPos;
          return ret;
          }
        }
      } else {
        if (rules(i).addr != EMPTY) tokenIterator++;
        if (rules(i).addr < 100 && rules(i).atAddr != true)
          i++;
        else
          atNotFinished = false;
      }
    }

  } while (atNotFinished && state && errorCount < 1);

  ret.result = newTree;
  ret.status = state;
  return ret;
}