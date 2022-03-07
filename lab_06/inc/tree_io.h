#ifndef DTS_TREE_IO_H
#define DTS_TREE_IO_H

#include <stdio.h>
#include <stdlib.h>

#include "err.h"
#include "tree.h"

void bs_tree_node_print(bs_tree *node);

int bs_tree_export_to_dot(char *fl, char *tree_name, bs_tree *tree);

int bs_tree_input(bs_tree **tree, char *filename);

//AVL

void avl_tree_node_print(avl_tree *node);

int avl_tree_export_to_dot(char *fl, char *tree_name, avl_tree *tree);

int avl_tree_input(avl_tree **tree, char *filename);


#endif 
