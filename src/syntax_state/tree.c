#include "tree.h"
#include "error.h"
#include "symbol_type.h"
#include "token.h"

Tree *create_node(char *_value, size_t id) {
  Tree *t;
  t = (Tree *)malloc(sizeof(Tree));
  t->_branches = NULL;
  t->branchesCount = 0;
  t->_value = _value;
  t->id = id;
  return t;
}

void add_branch(Tree *_origin, Tree *_tree) {
  _origin->branchesCount++;
  _origin->_branches = (Tree **)realloc(
      _origin->_branches, _origin->branchesCount * sizeof(Tree *));
  if (_origin->_branches == NULL)
    add_to_errors(create_error_without_linecolumn(
        MEMORY_ACCESS, "Cannot reallocate *_branches", true));
  else
    _origin->_branches[_origin->branchesCount - 1] = _tree;
}

void free_tree(Tree *_tree) {
  if (_tree != 0) {
    for (size_t i = 0; i < _tree->branchesCount; i++)
      free(_tree->_branches[i]);
    if (_tree->branchesCount != 0)
      free(_tree->_branches);
    free(_tree);
  }
}
