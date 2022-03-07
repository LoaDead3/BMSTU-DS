#include "../inc/hash_table_io.h"


int hash_table_input(hash_table *table, char *filename)
{
    FILE *f = fopen(filename, "r");
    if(!f)
        return FILE_ERROR;
    char cur[128];
    int n = 0;
    while (fscanf(f, "%s", cur) != EOF)
    {
        n++;
        int cmp_n = 0;
        int rc = hash_table_insert_char(table, cur, &cmp_n);
        if (rc)
        {
            hash_table_free(table);
            return rc;
        }
    }
    fclose(f);
    if(n == 0)
        return EMPTY_FILE;
    return NO_ERRORS;
}

void hash_table_print(hash_table *table)
{
    if(!table->table)
    {
        printf("Empty table\n");
        return;
    }
    for (int i = 0; i < table->size; i++)
    {
        printf("%d: ", i);
        list_print(table->table[i]);
    }
}
