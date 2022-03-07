#ifndef SHOW_IO_H
#define SHOW_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "show.h"
#include "show_table.h"
#include "error.h"

#define DEFAULT_SIZE 10
#define EXP_COEFF 2
#define FILE_END 1

int input(FILE *f, struct show_table *table);

void print(struct show_table *table);

int input_elem(FILE *f, struct show *n);

void print_table_with_key_sort(struct show_table *table, struct show_table_h_sort *handl);

void print_table_with_key_filter(struct show_table *table, struct show_table_h_filter *handl);

int add(struct show_table *table);

#endif
