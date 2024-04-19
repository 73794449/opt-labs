#include "tree.h"
#include "token.h"
#include "symbolType.h"
t_tree *create_node(char* value, size_t id)
{
    t_tree *t;
    t = (t_tree *)malloc(sizeof(t_tree));
    t->_branches = NULL;
    t->branchesCount = 0;
    t->value = value;
    t->id = id;
    return t;
}

void add_branch(t_tree* origin, t_tree* tree)
{
    origin->branchesCount++;
    origin->_branches = (t_tree**) realloc(origin->_branches,origin->branchesCount*sizeof(t_tree*));
    if(origin->_branches == NULL)
    {
        add_to_errors(create_error_without_linecolumn(MEMORY_ACCESS,"Cannot reallocate *_branches",true));
    }
    else
    {
        tree->_parent = origin;
        origin->_branches[origin->branchesCount-1] = tree;
    }
}


void free_tree(t_tree *tree)
{
    if(tree != 0)
    {
        for(size_t i = 0; i < tree->branchesCount; i++)
            free(tree->_branches[i]);
        if(tree->branchesCount != 0)
            free(tree->_branches);
        free(tree);
    }
}
