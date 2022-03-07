#ifndef DTS_HASH_TABLE_IO_H
#define DTS_HASH_TABLE_IO_H

#include <stdio.h>

#include "hash_table.h"
#include "sl_list_io.h"

int hash_table_input(hash_table *table, char *filename);

void hash_table_print(hash_table *table);

#endif 
