#include <stdlib.h>

#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

struct tree {
  char *_value;
  struct tree **_branches;
  size_t branchesCount;
  size_t id;
};
typedef struct tree Tree;

Tree *create_node(char *_value, size_t id);
void add_branch(Tree *_origin, Tree *_tree);
void free_tree(Tree *_tree);

/* add_branch defines*/
#define add_branch_with_token(token)                                           \
  do {                                                                         \
    add_branch(newTree, token);                                                \
    state = true;                                                              \
  } while (0)
#define add_branch_def_token()                                                 \
  add_branch_with_token(create_node(_tokens[tokenIterator]._data, i))
#define add_branch_empty() add_branch_with_token(create_node("<empty>", i))

#endif