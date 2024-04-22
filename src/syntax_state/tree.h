#include <stdlib.h>

#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

struct tree {
  char* _value;
  struct tree** _branches;
  size_t branchesCount;
  size_t id;
};
typedef struct tree Tree;

Tree* create_node(char* _value, size_t id);
void add_branch(Tree* _origin, Tree* _tree);
void free_tree(Tree* _tree);

#endif