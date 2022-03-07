#ifndef SORTS_H
#define SORTS_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "error.h"
#include "show.h"
#include "show_table.h"
#include "show_table_io.h"

int bin_insertion_sort_key(struct show_table *table);

int buble_sort_key(struct show_table *table);

int bin_insertion_sort_table(struct show_table *table);

int buble_sort_table(struct show_table *table);




int sorting_key_strap(struct show_table *table, int (*sort)(void *, size_t, size_t, int (*compare)(void *, void *)));

int sorting_strap(struct show_table *table, int (*sort)(void *, size_t, size_t, int (*compare)(void *, void *)));

int bin_insertion_sort(void *base, size_t num, size_t size, int (*compare)(void *, void *));

int buble_sort(void *base, size_t num, size_t size, int (*compare)(void *, void *));


#endif
