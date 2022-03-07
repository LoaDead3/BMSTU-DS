#include "../inc/hash_table.h"

int smp[] = {53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127};

int cur_smp = 0;

void hash_table_free(hash_table *table)
{
    for (int i = 0; i < table->size; i++)
        sl_list_free_list(table->table[i]);
    free(table->table);
}

ull hash(const char *str, int p)
{
    if(str == NULL)
        return 0;
    ull n = (ull) *str++;
    while(*str)
    {
        n += *str++ * p;
        p *= p;
    }
    return n;
}

int hash_table_init(hash_table *table, int size)
{
    table->table = calloc(size, sizeof(sl_list*));
    if(!table->table)
        return MEM_ERROR;
    table->size = size;
    return NO_ERRORS;
}

void hash_table_insert(hash_table *table, sl_list *node, int *n)
{
    *n = 0;
    int index = (int) (hash(node->data, smp[cur_smp]) % (ull) table->size);
    table->table[index] = sl_list_push_back(table->table[index], node, n);
    table->oper_num++;
    table->cmp_sum += *n;
}

int hash_table_insert_char(hash_table *table, char *data, int *n)
{
    sl_list *node = sl_list_init_node(data);
    if(!node)
        return MEM_ERROR;
    hash_table_insert(table, node, n);
    return NO_ERRORS;
}

sl_list *hash_table_search_char(hash_table *table, char *data, int *n)
{
    *n = 0;
    int index = (int) (hash(data, smp[cur_smp]) % (ull) table->size);
    sl_list *res = sl_list_search(table->table[index], data, n);
    if(res != NULL)
    {
        table->oper_num++;
        table->cmp_sum += *n;
    }
    return res;
}

sl_list *hash_table_remove_char(hash_table *table, char *data)
{
    int index = (int) (hash(data, smp[cur_smp]) % (ull) table->size);
    sl_list *res = NULL;
    table->table[index] = sl_list_remove(table->table[index], data, &res);
    return res;
}

int restruct(hash_table *dst, hash_table *src)
{
    dst->table = NULL;
    dst->size = 0;
    dst->cmp_sum = 0;
    dst->oper_num = 0;
    int size = 0, rc = 0;
    if(cur_smp >= SMP_NUM)
        size = src->size * 2;
    else
    {
        size = src->size;
        cur_smp++;
    }
    rc = hash_table_init(dst, size);
    if(rc)
        return rc;
    for (int i = 0; i < src->size; i++)
    {
        if(src->table[i] != NULL)
        {
            sl_list *list = src->table[i];
            for (; list; list = list->next)
            {
                int cmp_n = 0;
                rc = hash_table_insert_char(dst, list->data, &cmp_n);
                if(rc)
                {
                    hash_table_free(dst);
                    return rc;
                }
            }
        }
    }
    return rc;
}

int is_empty(hash_table *table)
{
    int res = 1;
    for (int i = 0; i < table->size; i++)
    {
        if(table->table[i] != NULL)
        {
            res = 0;
            break;
        }
    }
    return res;
}