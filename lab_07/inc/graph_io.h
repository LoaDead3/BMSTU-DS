#ifndef DTS_GRAPH_IO_H
#define DTS_GRAPH_IO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "err.h"
#include "graph.h"

#define STR_LEN 128
#define EMPTY_STR 999

typedef struct graph graph;
typedef struct edge edge;

int graph_input(graph *gr, char *filename);

int graph_print(graph *gr, char *filename);

#endif 
