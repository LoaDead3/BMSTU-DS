#include "../head/sorts.h"

int cmp_show_name_key(void *a, void *b)
{
    struct show_h_sort *tmp1 = (struct show_h_sort *) a, *tmp2 = (struct show_h_sort *) b;
    return strcmp(tmp1->show, tmp2->show);
}

int cmp_show_name(void *a, void *b)
{
    struct show *tmp1 = (struct show *) a, *tmp2 = (struct show *) b;
    return strcmp(tmp1->show, tmp2->show);
}

void *inc(void *n, size_t size)
{
    return (char *) n + size / sizeof(char);
}

void *dec(void *n, size_t size)
{
    int a = size / sizeof(char);
    return (char *) n - a;
}

void *mid_search(void *l, void *r, size_t size)
{
    char *a = l;
    char *b = r;
    int c = (b - a) / 2;
    int d = size / sizeof(char);
    int e = c / d;
    return a + e * size;
}

void *bin_search(void *base, void *key, size_t size, int (*compare)(void *, void *))
{
    void *l = base, *r = key;
    while (l < r)
    {
        void *mid = mid_search(l, r, size);
        if (compare(key, mid) < 0)
            r = mid;
        else
            l = inc(mid, size);
    }
    return l;
}

void assign(void *dst, void *src, size_t size)
{
    char *dst_ch = dst, *src_ch = src;
    int n = size / sizeof(char);
    for (int i = 0; i < n; i++)
        *dst_ch++ = *src_ch++;
}

void shift(void *r, void *l, size_t size)
{
    void *tmp = r;
    void *tmp1 = dec(tmp, size);
    while (tmp > l)
    {
        assign(tmp, tmp1, size);
        tmp = dec(tmp, size);
        tmp1 = dec(tmp1, size);
    }
}


int bin_insertion_sort(void *base, size_t num, size_t size, int (*compare)(void *, void *))
{
    if (base == NULL)
        return NO_DATA;
    if (size < 1 || compare == NULL || num < 1)
        return WRONG_DATA;
    int n = (int) num;
    if (n < 2)
        return 0;
    void *key = inc(base, size);
    for (int i = 1; i < n; i++)
    {
        void *p = bin_search(base, key, size, compare);
        void *tmp = calloc(1, size);
        if (tmp == NULL)
            return MEM_ERROR;
        assign(tmp, key, size);
        shift(key, p, size);
        assign(p, tmp, size);
        free(tmp);
        key = inc(key, size);
    }
    return 0;
}

int swap(void *a, void *b, size_t size)
{
    void *tmp = malloc(size);
    if (!tmp)
    {
        free(tmp);
        return MEM_ERROR;
    }
    assign(tmp, a, size);
    assign(a, b, size);
    assign(b, tmp, size);
    free(tmp);
    return 0;
}

int buble_sort(void *base, size_t num, size_t size, int (*compare)(void *, void *))
{
    if (base == NULL)
        return NO_DATA;
    if (size < 1 || compare == NULL || num < 1)
        return WRONG_DATA;
    int n = (int) num;
    if (n < 2)
        return 0;
    void *end = base, *key_i = base;
    for (int i = 0; i < num; i++)
        end = inc(end, size);
    int rc;
    while (key_i < end)
    {
        void *key_j = dec(end, size);
        while (key_j > key_i)
        {
            void *tmp_key = dec(key_j, size);
            if (compare(key_j, tmp_key) < 0)
            {
                rc = swap(tmp_key, key_j, size);
                if (rc)
                    return rc;
            }
            key_j = dec(key_j, size);
        }
        key_i = inc(key_i, size);
    }
    return 0;
}


int sorting_key_strap(struct show_table *table, int (*sort)(void *, size_t, size_t, int (*compare)(void *, void *)))
{
    struct show_table_h_sort handl;
    handl.list = calloc(table->size, sizeof(struct show_h_sort));
    if (!handl.list)
    {
        free(handl.list);
        return MEM_ERROR;
    }
    handl.size = table->size;
    for (int i = 0; i < table->size; i++)
    {
        strcpy(handl.list[i].show, table->list[i].show);
        handl.list[i].index = table->list[i].index;
    }
    int rc = sort(handl.list, handl.size, sizeof(struct show_h_sort), cmp_show_name_key);
    if (rc)
    {
        free(handl.list);
        return rc;
    }
//    print_table_with_key_sort(table, &handl);
    free(handl.list);
    return 0;
}

void copy_elem(struct show *dst, struct show *src)
{
    dst->index = src->index;
    strcpy(dst->theater, src->theater);
    strcpy(dst->show, src->show);
    strcpy(dst->director, src->director);
    dst->min_price = src->min_price;
    dst->max_price = src->max_price;
    dst->cur_type = src->cur_type;
    switch (src->cur_type)
    {
        case CHILD:
            dst->child.target_age = src->child.target_age;
            dst->child.genre = src->child.genre;
            break;
        case ADULT:
            dst->adult.genre = src->adult.genre;
            break;
        case MUSIC:
            strcpy(dst->music.composer, src->music.composer);
            strcpy(dst->music.country, src->music.country);
            dst->music.min_age = src->music.min_age;
            dst->music.duration = src->music.duration;
        default:
            break;
    }
}

int sorting_strap(struct show_table *table, int (*sort)(void *, size_t, size_t, int (*compare)(void *, void *)))
{
    struct show_table table_cpy;
    table_cpy.list = calloc(table->size, sizeof(struct show));
    if (!table_cpy.list)
    {
        free(table_cpy.list);
        return MEM_ERROR;
    }
    table_cpy.size = table->size;
    for (int i = 0; i < table->size; i++)
        copy_elem(&table_cpy.list[i], &table->list[i]);
    int rc = sort(table_cpy.list, table_cpy.size, sizeof(struct show), cmp_show_name);
    if (rc)
    {
        free(table_cpy.list);
        return rc;
    }
//    print(&table_cpy);
    free(table_cpy.list);
    return 0;
}

int bin_insertion_sort_key(struct show_table *table)
{
    int rc = sorting_key_strap(table, bin_insertion_sort);
    if (rc)
        return rc;
    return 0;
}

int buble_sort_key(struct show_table *table)
{
    int rc = sorting_key_strap(table, buble_sort);
    if (rc)
        return rc;
    return 0;
}

int bin_insertion_sort_table(struct show_table *table)
{
    int rc = sorting_strap(table, bin_insertion_sort);
    if (rc)
        return rc;
    return 0;
}

int buble_sort_table(struct show_table *table)
{
    int rc = sorting_strap(table, buble_sort);
    if (rc)
        return rc;
    return 0;
}
