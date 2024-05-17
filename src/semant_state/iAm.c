#include "semant.h"
#include <string.h>


bool iAmInConst(char *v) {
  for (size_t i = 0; i < constCount; i++) {
    if (strcmp(consts[i].name, v) == 0)
      return true;
  }
  return false;
}

bool iAmProgram(char *v)
{
  if(strcmp(program_name,v) == 0)
    return true;
  return false;
}

bool iAmInVars(char *v) {
  for (size_t i = 0; i < varsCount; i++) {
    if (strcmp(vars[i].name, v) == 0)
      return true;
  }
  return false;
}