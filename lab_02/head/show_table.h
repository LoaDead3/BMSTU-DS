#ifndef SHOW_TABLE_H
#define SHOW_TABLE_H

#include <stdlib.h>
#include <stdio.h>

#include "show.h"
#include "error.h"
#include "show_table_io.h"


struct show_table
{
    struct show *list;
    int size;
};

struct show_table_h_filter
{
    struct show_h_filter *list;
    int size;
};

struct show_table_h_sort
{
    struct show_h_sort *list;
    int size;
};


int print_filtred_shows(struct show_table *src);

int del(struct show_table *table);

#endif
