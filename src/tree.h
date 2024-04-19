#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H
#include <stdlib.h>
typedef struct tree{
    char* value;
    struct tree **_branches;
    size_t branchesCount;
    struct tree *_parent;
    size_t id;
}   t_tree;


t_tree *create_node(char* value, size_t id);
void add_branch(t_tree* origin, t_tree* tree);
void free_tree(t_tree *tree);
#endif