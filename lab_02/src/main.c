#include <stdio.h>

#include "../head/show_table.h"
#include "../head/show_table_io.h"
#include "../head/error.h"
#include "../head/sorts.h"


int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    if (argc != 2)
        return error_handler(ARG_ERROR);
    struct show_table table;
    int rc;
    FILE *f = fopen(argv[1], "r");
    if (!f)
        return error_handler(FILE_ERROR);
    printf("An introduction to the repertoire of theaters containing:\n"
           "the name of the theater, performance, director, ticket price\n"
           "range, performance type: for children - for what age, type \n"
           "(fairy tale, play); adult - play, drama, comedy); musical - composer,\n"
           " country, minimum age, duration). All strings no more than 30 characters.\n");
    rc = input(f, &table);
    fclose(f);
    if (rc)
        return error_handler(rc);
    int choice = 1;
    while (choice != 0)
    {
        printf("Choice menu item\n1-Add element\n2-Del element\n"
               "3-Bring out musical performances with suitable age limit and duration\n"
               "4-Print sorted table with key table (binary insertion sort)\n"
               "5-Print sorted table with key table (bubble sort)\n"
               "6-Print sorted table (binary insertion sort)\n"
               "7-Print sorted table(bubble sort)\n"
               "8-Print\n0-Exit\nChoice:");
        rc = scanf("%d", &choice);
        if (rc != 1)
        {
            free(table.list);
            return error_handler(WRONG_DATA);
        }
        switch (choice)
        {
            case 0:
                break;
            case 1:
                rc = add(&table);
                if (rc)
                {
                    free(table.list);
                    return error_handler(rc);
                }
                break;
            case 2:
                rc = del(&table);
                if (rc)
                {
                    free(table.list);
                    return error_handler(rc);
                }
                break;
            case 3:
            {
                rc = print_filtred_shows(&table);
                if (rc)
                {
                    free(table.list);
                    return error_handler(rc);
                }
                break;
            }
            case 4:
                rc = bin_insertion_sort_key(&table);
                if (rc)
                {
                    free(table.list);
                    return error_handler(rc);
                }
                break;
            case 5:
                rc = buble_sort_key(&table);
                if (rc)
                {
                    free(table.list);
                    return error_handler(rc);
                }
                break;
            case 6:
                rc = bin_insertion_sort_table(&table);
                if (rc)
                {
                    free(table.list);
                    return error_handler(rc);
                }
                break;
            case 7:
                rc = buble_sort_table(&table);
                if (rc)
                {
                    free(table.list);
                    return error_handler(rc);
                }
                break;
            case 8:
                print(&table);
                break;
            default:
                printf("No such item\n");
                break;
        }
    }
    free(table.list);
    return 0;
}