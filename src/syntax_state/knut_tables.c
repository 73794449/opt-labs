#include "knut_tables.h"
#include "error.h"
#include "terms.h"

Code new_code(size_t addrTo, char *_term) {
  Code myCode = {addrTo, _term, false};
  if (_term != NULL)
    myCode.isTerm = true;
  return myCode;
}

Line new_line(size_t addr, Code myCode, bool at, size_t afAddr) {
  Line myLine = {addr, myCode, at, afAddr};
  return myLine;
}

void insert(Table *_table, Line myLine) {
  _table->linesCount++;
  _table->lines =
      (Line *)realloc(_table->lines, _table->linesCount * sizeof(Line));
  if (_table->lines == NULL)
    add_to_errors(create_error_without_linecolumn(
        MEMORY_ACCESS, "Cannot reallocate *knut_lines", true));
  else
    _table->lines[_table->linesCount - 1] = myLine;
}

char *name_by_id(size_t addr) {
  switch (addr) {
  case SIGNAL_PROGRAM:
    return "<signal-program>";
  case PROGRAM:
    return "<program>";
  case BLOCK:
    return "<block>";
  case DECLARATIONS:
    return "<declarations>";
  case CONSTANT_DECLARATIONS:
    return "<constant-declarations>";
  case CONSTANT_DECLARATIONS_LIST:
    return "<constant-declarations-list>";
  case CONSTANT_DECLARATION:
    return "<constant-declaration>";
  case STATEMENT:
    return "<statement>";
  case STATEMENTS_LIST:
    return "<statements-list>";
  case ALTERNATIVES_LIST:
    return "<alternatives-list>";
  case ALTERNATIVE:
    return "<alternative>";
  case EXPRESSION:
    return "<expression>";
  case SUMMANDS_LIST:
    return "<summands-list>";
  case ADD_INSTRUCTION:
    return "<add-instruction>";
  case SUMMAND:
    return "<summand>";
  case CONSTANT:
    return "<constant>";
  case VARIABLE_IDENTIFIER:
    return "<variable-identifier>";
  case CONSTANT_IDENTIFIER:
    return "<constant-identifier>";
  case PROCEDURE_IDENTIFIER:
    return "<procedure-identifier>";
  case UNSIGNED_INTEGER:
    return "<unsigned-integer>";
  case IDENTIFIER:
    return "<identifier>";
  case STRING:
    return "<string>";
  case EMPTY:
    return "<empty>";
  default:
    return "<error>";
  };
}

/*
rule(addr,addr_to,term,at_addr,af_addr)
Creates new rule in knut table
*/

#define rule(addr, addr_to, term, at_addr, af_addr)                            \
  insert(&myTable, new_line(addr, new_code(addr_to, term), at_addr, af_addr))

Table create_knut_table() {
  Table myTable = {.linesCount = 0, .lines = NULL};
  /*
  AT - ACTION TRUE
  AF - ACTION FALSE
  */
  /*   ADDR ADDR_TO TERM AT AF_ADDR*/
  /*<signal-program> --> <program> */
  rule(0, SIGNAL_PROGRAM, NULL, false, ERROR);
  rule(1, PROGRAM, NULL, false, ERROR);
  rule(2, SIGNAL_PROGRAM_FINISH, NULL, true, ERROR);
  /*<program> --> PROGRAM <procedure-identifier> ; <block> .*/
  rule(3, 0, "PROGRAM", false, ERROR);
  rule(4, PROCEDURE_IDENTIFIER, NULL, false, ERROR);
  rule(5, 0, ";", false, ERROR);
  rule(6, BLOCK, NULL, false, ERROR);
  rule(7, 0, ".", true, ERROR);
  /*<block> --> <declarations> BEGIN <statements-list> END*/
  rule(8, DECLARATIONS, NULL, false, ERROR);
  rule(9, 0, "BEGIN", false, ERROR);
  rule(10, STATEMENTS_LIST, NULL, false, ERROR);
  rule(11, 0, "END", true, ERROR);
  /*<declarations> --> <constant-declarations>*/
  rule(12, CONSTANT_DECLARATIONS, NULL, true, ERROR);
  /*<constant-declarations> --> CONST <constant-declarations-list> | <empty>*/
  rule(13, 0, "CONST", false, ERROR);
  rule(14, CONSTANT_DECLARATIONS_LIST, NULL, true, 15);
  rule(15, EMPTY, NULL, true, ERROR);
  /*<constant-declarations-list> --> <constantdeclaration>
   * <constant-declarations-list> | <empty>*/
  rule(16, CONSTANT_DECLARATION, NULL, false, ERROR);
  rule(17, CONSTANT_DECLARATIONS_LIST, NULL, true, 18);
  rule(18, EMPTY, NULL, true, ERROR);
  /*<constant-declaration> --> <constant-identifier> = <constant>;*/
  rule(19, CONSTANT_IDENTIFIER, NULL, false, ERROR);
  rule(20, 0, "=", false, ERROR);
  rule(21, CONSTANT, NULL, false, ERROR);
  rule(22, 0, ";", true, ERROR);
  /*<statements-list> --> <statement> <statement-list> | <empty>*/
  rule(23, STATEMENT, NULL, false, ERROR);
  rule(24, STATEMENTS_LIST, NULL, true, 25);
  rule(25, EMPTY, NULL, true, ERROR);
  /*<statement> --> CASE <expression> OF <alternativeslist> ENDCASE ;|
  <variable-identifier> := <expression> ;*/
  rule(26, 0, "CASE", false, 32);
  rule(27, EXPRESSION, NULL, false, ERROR);
  rule(28, 0, "OF", false, ERROR);
  rule(29, ALTERNATIVES_LIST, NULL, false, ERROR);
  rule(30, 0, "ENDCASE", false, ERROR);
  rule(31, 0, ";", true, ERROR);
  rule(32, VARIABLE_IDENTIFIER, NULL, false, ERROR);
  rule(33, 0, ":=", false, ERROR);
  rule(34, EXPRESSION, NULL, false, ERROR);
  rule(35, 0, ";", true, ERROR);
  /*<alternatives-list> --> <alternative> <alternativeslist> | <empty>*/
  rule(36, ALTERNATIVE, NULL, false, ERROR);
  rule(37, ALTERNATIVES_LIST, NULL, true, 38);
  rule(38, EMPTY, NULL, true, ERROR);
  /*<alternative> --> <expression> : /<statements-list>\*/
  rule(39, EXPRESSION, NULL, false, ERROR);
  rule(40, 0, ":", false, ERROR);
  rule(41, 0, "/", false, ERROR);
  rule(42, STATEMENTS_LIST, NULL, false, ERROR);
  rule(43, 0, "\\", true, ERROR);
  /*<expression> --> <summand> <summands-list> | - <summand> <summands-list>*/
  rule(44, SUMMAND, NULL, false, 46);
  rule(45, SUMMANDS_LIST, NULL, true, ERROR);
  rule(46, 0, "-", false, ERROR);
  rule(47, SUMMAND, NULL, false, ERROR);
  rule(48, SUMMANDS_LIST, NULL, true, ERROR);
  /*<summands-list> --> <add-instruction> <summand> | <summands-list> |
   * <empty>*/
  rule(49, ADD_INSTRUCTION, NULL, false, ERROR);
  rule(50, SUMMAND, NULL, true, 51);
  rule(51, SUMMANDS_LIST, NULL, true, 52);
  rule(52, EMPTY, NULL, true, ERROR);
  /*<add-instruction> --> + | -*/
  rule(53, 0, "+", true, 54);
  rule(54, 0, "-", true, ERROR);
  /*<summand> --> <variable-identifier> | <unsigned-integer>*/
  rule(55, VARIABLE_IDENTIFIER, NULL, true, 56);
  rule(56, UNSIGNED_INTEGER, NULL, true, ERROR);
  /*<constant> --> <unsigned-integer>*/
  rule(57, UNSIGNED_INTEGER, NULL, true, ERROR);
  /*<variable-identifier> --> <identifier>*/
  rule(58, IDENTIFIER, NULL, true, ERROR);
  /*<constant-identifier> --> <identifier>*/
  rule(59, IDENTIFIER, NULL, true, ERROR);
  /*<procedure-identifier> --> <identifier>*/
  rule(60, IDENTIFIER, NULL, true, ERROR);

  rule(UNSIGNED_INTEGER, 0, "", true, ERROR);
  rule(IDENTIFIER, 0, "", true, ERROR);
  rule(STRING, 0, "", true, ERROR);
  rule(EMPTY, 0, "", true, ERROR);
  return myTable;
}
