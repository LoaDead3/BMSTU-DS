#ifndef DTS_GRAPH_H
#define DTS_GRAPH_H

#include <stdlib.h>
#include <stdio.h>

#include "err.h"
#include "graph_io.h"

#define NO_ADJ 71

typedef struct graph graph;
typedef struct edge edge;

struct edge
{
    int start;
    int end;
    edge *next;
};

struct graph
{
    int v_num;
    edge *edge_list;
};

//Создание ребра
edge *edge_init_node(int start, int end);

//Добавление ребра в граф
void graph_add_edge(graph *gr, edge *node);

//Освобождение памяти
void graph_free(graph *gr);

//Проверка наличия ребра в графе
int graph_is_edge_exist(graph *gr, int d1, int d2);

//Проверка является ли граф деревом
int graph_is_tree(graph *gr, int *res);

//Проверка наличия дерева в графе при удалении вершины
int show_tree_in_graph(graph *gr);

#endif 
