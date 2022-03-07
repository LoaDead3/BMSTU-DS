#ifndef DTS_TREE_H
#define DTS_TREE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct binary_search_tree bs_tree;

typedef struct balanced_binary_search_tree avl_tree;

#include "err.h"
#include "tree_io.h"


struct binary_search_tree
{
    char *data;
    bs_tree *left;
    bs_tree *right;
};

struct balanced_binary_search_tree
{
    char *data;
    int height;
    avl_tree *left;
    avl_tree *right;
};

//Освобождение памяти
void bs_tree_free(bs_tree *tree);

//Вставка элемента по строке
int bs_tree_insert_node_char(bs_tree **tree, char *data, int *n);

//Поиск элемента по строке
bs_tree *bs_tree_search_char(bs_tree *tree, char *data, int *n);

//Удаление элемента
bs_tree *bs_tree_remove(bs_tree *node, char *data);

//Прямой обход
void bs_tree_nlr_detour(bs_tree *tree);

//Центрированный обход
void bs_tree_lnr_detour(bs_tree *tree);

//Обратный обход
void bs_tree_lrn_detour(bs_tree *tree);

//AVL

//Освобождение памяти
void avl_tree_free(avl_tree *tree);

//Создание дерева
avl_tree *avl_tree_create(char **arr, int n);

//Вставка элемента по строке
int avl_tree_insert_node_char(avl_tree **tree, char *data, int *n);

//Поиск элемента по строке
avl_tree *avl_tree_search_char(avl_tree *tree, char *data, int *n);

//Удаление элемента
avl_tree *avl_tree_remove(avl_tree *node, char *data);

//Прямой обход
void avl_tree_nlr_detour(avl_tree *tree);

//Центрированный обход
void avl_tree_lnr_detour(avl_tree *tree);

//Обратный обход
void avl_tree_lrn_detour(avl_tree *tree);

#endif
