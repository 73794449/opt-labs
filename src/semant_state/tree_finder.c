#include "semant.h"
#include <string.h>

Tree *find_in_tree(Tree *cur_tree, char *value) {
  if (strcmp(cur_tree->_value, value) == 0 && skip == 0) {
    return cur_tree;
  } else {
    if (strcmp(cur_tree->_value, value) == 0)
      skip--;
    if (cur_tree->branchesCount != 0) {
      for (size_t i = 0; i < cur_tree->branchesCount; i++) {
        Tree *temp = find_in_tree(cur_tree->_branches[i], value);
        if (temp != NULL) {
          return temp;
        }
      }
      return NULL;
    } else
      return NULL;
  }
}