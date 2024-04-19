#ifndef KNUT_TABLES_H
#define KNUT_TABLES_H
#include <stdlib.h>
#include <stdbool.h>


typedef struct knut_code
{
    size_t addr_to;
    char* term;
    bool is_term;
} KC;

typedef struct knut_line 
{
    size_t addr;
    KC code;
    bool AT;
    size_t AF_ADDR;
} KL;

typedef struct knut_table
{
    size_t lines_count;
    KL* lines;
} KNUT;

KNUT create_knut_table();
char* name_by_id(size_t addr);
bool created_rule(size_t number);

#endif