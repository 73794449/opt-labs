#ifndef TERMS_H
#define TERMS_H

#define SIGNAL_PROGRAM 0
#define SIGNAL_PROGRAM_FINISH 2
#define PROGRAM 3
#define PROGRAM_ENDING 7
#define BLOCK 8
#define DECLARATIONS 12
#define CONSTANT_DECLARATIONS 13
#define CONSTANT_DECLARATIONS_LIST 16
#define CONSTANT_DECLARATION 19
#define STATEMENTS_LIST 23
#define STATEMENT 26
#define ALTERNATIVES_LIST 36
#define ALTERNATIVE 39
#define EXPRESSION 44
#define SUMMANDS_LIST 49
#define ADD_INSTRUCTION 55
#define SUMMAND 57
#define CONSTANT 59
#define VARIABLE_IDENTIFIER 60
#define CONSTANT_IDENTIFIER 61
#define PROCEDURE_IDENTIFIER 62
#define ERROR 666
#define OK 777

/*
<identifier> --> <letter><string>                                  id>1000
<string> --> <letter><string> | <digit><string> | <empty>          id>750
<unsigned-integer> --> <digit><digits-string>                      id>500
<digits-string> --> <digit><digits-string> | <empty>
<digit> --> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
<letter> --> A | B | C | D | ... | Z
*/
#define IDENTIFIER 100
#define UNSIGNED_INTEGER 101
#define STRING 102
#define EMPTY 200

#endif