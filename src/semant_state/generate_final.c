#include "semant.h"
#include <stdio.h>
void generate_final_output()
{
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
}