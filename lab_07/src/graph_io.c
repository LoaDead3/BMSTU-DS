#include "../inc/graph_io.h"

int str_input(FILE *f, int **arr, int *n)
{
    *n = 0;
    char str[STR_LEN];
    char *check = fgets(str, STR_LEN, f);
    if (!check || strlen(str) == STR_LEN)
        return DATA_ERROR;
    char *tmp_n = strchr(str, '\n');
    if (tmp_n != NULL)
        *tmp_n = '\0';
    char *tmp_r = strchr(str, '\r');
    if (tmp_r != NULL)
        *tmp_r = '\0';
    if (strlen(str) < 1)
        return EMPTY_STR;
    char *pbegin = NULL, *pend = NULL;
    pbegin = str;
    pend = pbegin + 1;
    int elem = strtol(pbegin, &pend, 10);
    int mem_size = 10;
    *arr = calloc(mem_size, sizeof(int));
    if (!(*arr))
        return MEM_ERROR;
    while (pbegin != pend)
    {
        (*arr)[(*n)++] = elem;
        if (*n == mem_size)
        {
            mem_size *= 2;
            int *tmp = realloc(*arr, sizeof(int) * mem_size);
            if (!tmp)
            {
                free(*arr);
                return MEM_ERROR;
            }
            *arr = tmp;
        }
        pbegin = pend;
        pend = pbegin + 1;
        elem = strtol(pbegin, &pend, 10);
    }
    int *tmp = realloc(*arr, sizeof(int) * (*n));
    if (!tmp)
    {
        free(*arr);
        return MEM_ERROR;
    }
    *arr = tmp;
    return NO_ERRORS;
}

int int_cmp(const void *d1, const void *d2)
{
    return *((int *) d1) - *((int *) d2);
}

int graph_input(graph *gr, char *filename)
{
    gr->edge_list = NULL;
    gr->v_num = 0;
    int rc = NO_ERRORS;
    FILE *f = fopen(filename, "r");
    if (!f)
        return FILE_ERROR;
    int sz = 0;
    int ic = 0;
    ic = fscanf(f, "%d", &sz);
    if(ic == EOF)
    {
        fclose(f);
        return EMPTY_FILE;
    }
    if (ic != 1 || sz < 1)
    {
        fclose(f);
        return DATA_ERROR;
    }
    gr->v_num = sz;
    for (int i = 0; i < sz; i++)
    {
        int *arr = NULL, n = 0;
        rc = str_input(f, &arr, &n);
        if (rc == EMPTY_STR)
        {
            free(arr);
            i--;
            continue;
        }
        if (rc)
        {
            fclose(f);
            free(arr);
            graph_free(gr);
            return rc;
        }
        qsort(arr, n, sizeof(int), int_cmp);
        for (int j = 0; j < n; j++)
        {
            if (arr[j] < 1 || arr[j] > sz)
            {
                fclose(f);
                free(arr);
                graph_free(gr);
                return DATA_ERROR;
            }
            if (arr[j] < i + 1)
            {
                if (graph_is_edge_exist(gr, arr[j], i + 1) == 0)
                {
                    fclose(f);
                    free(arr);
                    graph_free(gr);
                    return DATA_ERROR;
                }
            }
            else
            {
                edge *cur = edge_init_node(i + 1, arr[j]);
                if (!cur)
                {
                    fclose(f);
                    free(arr);
                    graph_free(gr);
                    return MEM_ERROR;
                }
                graph_add_edge(gr, cur);
            }
        }
        free(arr);
    }
    fclose(f);
    return rc;
}

int graph_print(graph *gr, char *filename)
{
    char fl[80];
    sprintf(fl, "%s.gv", filename);
    FILE *f = fopen(fl, "w");
    if (!f)
        return OUTPUT_ERROR;
    fprintf(f, "strict graph {\n");
    edge *cur = gr->edge_list;
    for (; cur; cur = cur->next)
        fprintf(f, "%d -- %d\n", cur->start, cur->end);
    fprintf(f, "}\n");
    fclose(f);
    char comand[80];
    sprintf(comand, "dot -Tsvg %s.gv > svg/%s.svg", filename, filename);
    system(comand);
    return NO_ERRORS;
}
