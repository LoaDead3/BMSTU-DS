#include "../head/show_table.h"

void shift_handl_table(struct show_table_h_filter *table, int start, int end)
{
    for (int i = start; i < end - 1; i++)
        table->list[i] = table->list[i + 1];
}

void shift_table(struct show_table *table, int start, int end)
{
    for (int i = start; i < end - 1; i++)
    {
        table->list[i] = table->list[i + 1];
        table->list[i].index--;
    }
}


int print_filtred_shows(struct show_table *src)
{
    struct show_table_h_filter handl;
    handl.list = calloc(src->size, sizeof(struct show_h_filter));
    if (!handl.list)
    {
        free(handl.list);
        return MEM_ERROR;
    }
    handl.size = 0;
    for (int i = 0; i < src->size; i++)
    {
        if (src->list[i].cur_type == MUSIC)
        {
            handl.list[handl.size].index = src->list[i].index;
            handl.list[handl.size].min_age = src->list[i].music.min_age;
            handl.list[handl.size].duration = src->list[i].music.duration;
            handl.size++;
        }
    }
    if (handl.size == 0)
    {
        printf("Not found\n");
        return 0;
    }
    handl.list = realloc(handl.list, sizeof(struct show_h_filter) * handl.size);
    if (!handl.list)
    {
        free(handl.list);
        return MEM_ERROR;
    }
    int rc, year, max_dur;
    printf("Input child's age:");
    rc = scanf("%d", &year);
    if (rc != 1 || year > 18)
    {
        free(handl.list);
        return WRONG_DATA;
    }
    printf("Input max duration:");
    rc = scanf("%d", &max_dur);
    if (rc != 1)
    {
        free(handl.list);
        return WRONG_DATA;
    }
    for (int i = 0; i < handl.size; i++)
    {
        if (year < handl.list[i].min_age || max_dur < handl.list[i].duration)
            shift_handl_table(&handl, i--, handl.size--);
    }
    if (handl.size < 1)
        printf("Not found\n");
    else
        print_table_with_key_filter(src, &handl);
    free(handl.list);
    return 0;
}

int del(struct show_table *table)
{
    int num;
    int rc;
    printf("Input index:");
    rc = scanf("%d", &num);
    if (table->size == 1 || num >= table->size)
    {
        printf("Deletion is not possible\n");
        return 0;
    }
    if (rc != 1)
        return WRONG_DATA;
    shift_table(table, num, table->size-- - 1);
    table->list = realloc(table->list, sizeof(struct show) * table->size);
    if (!table->list)
        return MEM_ERROR;
    return 0;
}
