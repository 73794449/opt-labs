#include "out.h"
#include <stdio.h>
#include "constant.h"
#include "identifier.h"
#include "lexer.h"
#include "syntax.h"
#include "strings.h"
void print_params()
{
  printf("Input file: %s\n", params._input_file);
  printf("Output file: %s\n", params._output_file);
  if (params.verbose)
    printf("Verbose mode enabled\n");
}
void print_error(Error error)
{
  char *critical = "Warning";
  short int state = error.state;
  if (error.critical)
    critical = "Error";
  if (state == LEXER_STATE)
    if (error.hasLineColumn)
      printf("#%ld|%s(Lexer)| Line->%ld, Column->%ld |: %s\n", error.number,
             critical, error.row, error.col, error._error_message);
    else
      printf("#%ld|%s(Lexer): %s\n", error.number, critical,
             error._error_message);
  else if (state == FILE_ACCESS)
    printf("#%ld|%s(File IO): %s\n", error.number, critical,
           error._error_message);
  else if (state == SYNTAX_STATE)
    printf("#%ld|%s(Syntax): %s\n",error.number,critical,error._error_message); 
  else if(state == MEMORY_ACCESS)
    printf("#%ld|%s(Memory): %s\n",error.number,critical,error._error_message);   
  else
    printf("#%ld|%s(Unknown): %s\n", error.number, critical,
           error._error_message);
}

void get_error(Error error, FILE *__output_file)
{
  char *critical = "Warning";
  short int state = error.state;
  if (error.critical)
    critical = "Error";
  if (state == LEXER_STATE)
    if (error.hasLineColumn)
      fprintf(__output_file,"#%ld|%s(Lexer)| Line->%ld, Column->%ld |: %s\n", error.number,
             critical, error.row, error.col, error._error_message);
    else
      fprintf(__output_file,"#%ld|%s(Lexer): %s\n", error.number, critical,
             error._error_message);
  else if (state == FILE_ACCESS)
    fprintf(__output_file,"#%ld|%s(File IO): %s\n", error.number, critical,
           error._error_message);
  else if (state == SYNTAX_STATE)
    fprintf(__output_file,"#%ld|%s(Syntax): %s\n",error.number,critical,error._error_message); 
  else if(state == MEMORY_ACCESS)
    fprintf(__output_file,"#%ld|%s(Memory): %s\n",error.number,critical,error._error_message);   
  else
    fprintf(__output_file,"#%ld|%s(Unknown): %s\n", error.number, critical,
           error._error_message);
}

void print_errors()
{
  for (size_t i = 0; i < errorCount; i++)
  {
    print_error(_errors[i]);
  }
}
void print_lexer()
{
  printf("Current buffer: %s\n", lexer._buffer);
  printf("Current row: %lu\n", lexer.row);
  printf("Current col: %lu\n", lexer.col);
  printf("Current symbol: %c\n", lexer.symbol);
  printf("Current symbol type: %d\n", lexer.symbolType);
}
void print_token(Token token)
{
  printf("[%lu][%lu] %lu: %s\n", token.row, token.col, token.code, token._data);
}
void print_tokens()
{
  for (unsigned long int i = 0; i < tokenCount; i++)
  {
    print_token(_tokens[i]);
  }
}

void out_file_lexer()
{
  FILE *__output_file;
  __output_file = fopen(params._output_file, "w");
  if (__output_file == NULL)
  {
    add_to_errors(create_error_without_linecolumn(FILE_ACCESS, "Cannot write to output file", true));
  }
  else
  {
    fprintf(__output_file,
            "|Line  |Column|Code  |Data  \n+------+------+------+------\n");
    for (size_t i = 0; i < tokenCount; i++)
    {
      fprintf(__output_file, "|%6ld|%6ld|%6ld|%s\n", _tokens[i].row,
              _tokens[i].col, _tokens[i].code, _tokens[i]._data);
    }
  }
  out_file_errors(__output_file);
  fclose(__output_file);
}

void print_file_out()
{
  FILE *__output_file;
  __output_file = fopen(params._output_file, "r");
  if (__output_file == NULL)
  {
    add_to_errors(create_error_without_linecolumn(FILE_ACCESS, "Cannot open output file for reading", true));
  }
  else
  {
    for (char c = (char)getc(__output_file); c != EOF;
         c = (char)getc(__output_file))
      printf("%c", c);
  }
}

void out_file_errors(FILE *__output_file)
{
  if(errorCount > 0){
  fprintf(__output_file, "ERRORS:\n");
  }
  for (size_t i = 0; i < errorCount; i++)
  {
    get_error(_errors[i], __output_file);
  }
  
}
void just_clean()
{
  clean_errors();
}


void out_node(t_tree* tree, FILE *__output_file, size_t level)
{
    for(size_t k = 0; k <  level; k++)
        fprintf(__output_file,"|");

    fprintf(__output_file,"%s\n", tree->value);

    for(size_t i = 0; i < tree->branchesCount; i++)
    {
      out_node(tree->_branches[i],__output_file,level+1);
    }
}

void out_file_syntax()
{
  FILE *__output_file;
  __output_file = fopen(params._output_file, "a");
  if (__output_file == NULL)
  {
    add_to_errors(create_error_without_linecolumn(FILE_ACCESS, "Cannot write to output file", true));
  }
  else
  {
    fprintf(__output_file, "SYNTAX:\n");
    out_node(_tree,__output_file,0);
  }
  fprintf(__output_file,"\n");
  out_file_errors(__output_file);
  fclose(__output_file);
}

void free_errors()
{
  free(_errors);
}

void free_tokens()
{
  free(_tokens);
}

void free_tables()
{
  free(_constants);
  free(_identifiers);
  free(_strings);
}

void free_trees()
{
  free_tree(_tree);
}