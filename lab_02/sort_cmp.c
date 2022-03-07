#include <stdio.h>
#include <time.h>
//#include "head/show_table.h"
#include "head/show_table_io.h"
#include "head/sorts.h"

int main()
{
    double tbub1 = 0, tbub2 = 0;
    double tbin1 = 0, tbin2 = 0;
    struct show_table table;
    FILE *f = fopen("data.txt", "r");
    if(!f)
        return 1;
    input(f, &table);
    fclose(f);
    int rc = 0;
    for (int i = 0; i < 5; i++)
    {
        clock_t begin = clock();
        rc = sorting_key_strap(&table,buble_sort);
        clock_t endt = clock();
        tbub1 += (double) (endt - begin);
    }
    tbub1 /= 5;
    size_t s1 = 0;
    for (int i = 0; i < table.size; i++)
    {
        s1 += sizeof(table.list[i]) + sizeof(table.list[i].show) + sizeof(int);
    }
    s1+= sizeof(int) + sizeof(int*);
    printf("Buble sort with key:%.3lf %lld\n", tbub1 / CLOCKS_PER_SEC, s1);

    for (int i = 0; i < 5; i++)
    {
        clock_t begin = clock();
        rc=sorting_strap(&table,buble_sort);
        clock_t endt = clock();
        tbub2 += (double)(endt - begin);
    }
    tbub2 /= 5;
    size_t s2 = 0;
    for (int i = 0; i < table.size; i++)
    {
        s2 += sizeof(table.list[i]);
    }
    s2+= sizeof(int) + sizeof(int*);
    printf("Buble sort without key:%.3lf %lld\n", tbub2 / CLOCKS_PER_SEC, s2);

    for (int i = 0; i < 5; i++)
    {
        clock_t begin = clock();
        sorting_key_strap(&table,bin_insertion_sort);
        clock_t endt = clock();
        tbin1 += (double)(endt - begin);
    }
    size_t s3 = 0;
    for (int i = 0; i < table.size; i++)
    {
        s3 += sizeof(table.list[i]) + sizeof(table.list[i].show) + sizeof(int);
    }
    s3+= sizeof(int) + sizeof(int*);
    tbin1 /= 5;
    printf("Bin insertion sort with key:%.3lf %lld\n", tbin1 / CLOCKS_PER_SEC, s3);

    for (int i = 0; i < 5; i++)
    {
        clock_t begin = clock();
        sorting_strap(&table,bin_insertion_sort);
        clock_t endt = clock();
        tbin2 += (double)(endt - begin);
    }
    tbin2 /= 5;
    size_t s4 = 0;
    for (int i = 0; i < table.size; i++)
    {
        s4 += sizeof(table.list[i]);
    }
    s4+= sizeof(int) + sizeof(int*);
    printf("Bin insertion without key:%.3lf %lld\n", tbin2 / CLOCKS_PER_SEC, s4);
    return 0;
}
