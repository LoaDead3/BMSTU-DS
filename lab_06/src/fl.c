#include "../inc/fl.h"

int file_write(char *file_name, char *data)
{
    FILE *f = fopen(file_name, "a");
    if(!f)
        return FILE_ERROR;
    fprintf(f, "%s\n", data);
    fclose(f);
    return NO_ERRORS;
}

int file_search(char *file_name, char *data, int *n)
{
    *n = 0;
    FILE *f = fopen(file_name, "r");
    int rc = 0, is_find = 0;
    while (rc != EOF)
    {
        char tmp[128] = "";
        rc = fscanf(f, "%s", tmp);
        (*n)++;
        if(strcmp(tmp, data) == 0)
        {
            is_find = 1;
            break;
        }
    }
    fclose(f);
    return is_find;
}