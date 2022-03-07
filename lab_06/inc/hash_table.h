#ifndef DTS_HASH_TABLE_H
#define DTS_HASH_TABLE_H

#include "sl_list.h"
#include "err.h"

#define SMP_NUM 0

typedef unsigned long long ull;

typedef struct hash_table hash_table;

struct hash_table
{
    sl_list **table;
    int size;
    int cmp_sum;
    int oper_num;
};

//Освобождение памяти
void hash_table_free(hash_table *table);

//Инициализация таблицы
int hash_table_init(hash_table *table, int size);

//Вставка элемента по строке
int hash_table_insert_char(hash_table *table, char *data, int *n);

//Поиск элемента по строке
sl_list *hash_table_search_char(hash_table *table, char *data, int *n);

//Удаление элемента по строке
sl_list *hash_table_remove_char(hash_table *table, char *data);

//Реструктуризация
int restruct(hash_table *dst, hash_table *src);

int is_empty(hash_table *table);

#endif 
