#ifndef CLI_H
#define CLI_H
#include "error.h"
struct params {
  char *_input_file;
  char *_output_file;
  bool verbose;
};
typedef struct params Params;

extern Params params;

void proc_cli(int argc, char *argv[]);

#endif