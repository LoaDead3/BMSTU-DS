#include "matrix_io.h"

int arr_input(FILE *f, int *arr, int *n)
{
    char str[STR_LEN];
    *n = 0;
    char *ch = fgets(str, STR_LEN + 1, f);
    if (ch == NULL || strlen(str) > STR_LEN)
        return DATA_ERROR;
    char *pBegin, *pEnd;
    pBegin = str;
    pEnd = pBegin + 1;
    int elem = strtol(pBegin, &pEnd, 10);
    while (pBegin != pEnd)
    {
        arr[(*n)++] = elem;
        pBegin = pEnd;
        pEnd = pBegin + 1;
        elem = strtol(pBegin, &pEnd, 10);
    }
    if (*n == 0)
        return DATA_ERROR;
    return NO_ERROR;
}


int input(FILE *f, struct matrix *matrix)
{
    int tmp_n = matrix->n, rc = 0;
    matrix->n = 0;
    matrix->arr = calloc(tmp_n, sizeof(int *));
    if (!matrix->arr)
    {
        free(matrix->arr);
        return MEM_ERROR;
    }
    for (int i = 0; i < tmp_n; i++)
    {
        int tmp_m;
        int tmp_arr[ARR_LEN];
        rc = arr_input(f, tmp_arr, &tmp_m);
        if (rc)
        {
            matrix_free(matrix);
            return rc;
        }
        if (tmp_m != matrix->m)
        {
            matrix_free(matrix);
            return DATA_ERROR;
        }
        matrix->arr[i] = calloc(matrix->m, sizeof(int));
        if (!matrix->arr[i])
        {
            matrix_free(matrix);
            return MEM_ERROR;
        }
        for (int j = 0; j < matrix->m; j++)
            matrix->arr[i][j] = tmp_arr[j];
        matrix->n++;
    }
    if (matrix->n != 1)
    {
        char ch = fgetc(f);
        if (!(ch == EOF || isspace(ch)))
        {
            matrix_free(matrix);
            return DATA_ERROR;
        }
    }
    return NO_ERROR;
}

int sparse_input(FILE *f, struct sparse_matrix *matrix)
{
    struct matrix aux_matrix;
    aux_matrix.n = matrix->n;
    aux_matrix.m = matrix->m;
    int rc = input(f, &aux_matrix);
    if (rc)
        return rc;
    int tmp_len = 0;
    for (int i = 0; i < aux_matrix.n; i++)
        for (int j = 0; j < aux_matrix.m; j++)
            if (aux_matrix.arr[i][j] != 0)
                tmp_len++;
    matrix->a = calloc(tmp_len, sizeof(int));
    matrix->ia = calloc(tmp_len, sizeof(int));
    matrix->ja = calloc(aux_matrix.m, sizeof(int));
    if (!matrix->a || !matrix->ia || !matrix->ja)
    {
        matrix_free(&aux_matrix);
        sparse_matrix_free(matrix);
        return MEM_ERROR;
    }
    matrix->n = aux_matrix.n;
    matrix->m = aux_matrix.m;
    matrix->elem_num = 0;
    int flag = 0;
    for (int j = 0; j < aux_matrix.m; j++)
    {
        int flag1 = 0, begin_row = matrix->elem_num;
        for (int i = 0; i < aux_matrix.n; i++)
        {
            if (aux_matrix.arr[i][j] != 0)
            {
                flag = 1;
                flag1 = 1;
                matrix->a[matrix->elem_num] = aux_matrix.arr[i][j];
                matrix->ia[matrix->elem_num] = i;
                matrix->elem_num++;
            }
        }
        if (flag1)
            matrix->ja[j] = begin_row;
        else
            matrix->ja[j] = (flag) ? matrix->ja[j - 1] : -1;
    }
    matrix_free(&aux_matrix);
    return NO_ERROR;
}

int input_by_dots(FILE *f, struct matrix *matrix)
{
    int tmp_n = matrix->n, rc = 0, n = 0;
    while (1)
    {
        if (f == stdin)
            printf("Input dots num:");
        rc = fscanf(f, "%d", &n);
        if (rc != 1 || n > matrix->n * matrix->m || n < 1)
        {
            if (f == stdin)
                printf("Wrong value\n");
            continue;
        }
        break;
    }
    matrix->n = 0;
    matrix->arr = calloc(tmp_n, sizeof(int *));
    if (!matrix->arr)
    {
        free(matrix->arr);
        return MEM_ERROR;
    }
    for (int i = 0; i < tmp_n; i++)
    {
        matrix->arr[i] = calloc(matrix->m, sizeof(int));
        matrix->n++;
        if (!matrix->arr[i])
        {
            matrix_free(matrix);
            return MEM_ERROR;
        }

    }
    for (int i = 0; i < n; i++)
    {
        int x, y, elem, err_count = 0;
        while (1)
        {
            if (f == stdin)
                printf("Input i:");
            rc = fscanf(f, "%d", &x);
            if (rc != 1 || x < 0 || x >= matrix->n)
                err_count++;
            if (f == stdin)
                printf("Input j:");
            rc = fscanf(f, "%d", &y);
            if (rc != 1 || y < 0 || y >= matrix->m)
                err_count++;
            if (f == stdin)
                printf("Input value:");
            rc = fscanf(f, "%d", &elem);
            if (rc != 1)
                err_count++;
            if (err_count == 0)
                break;
            if (f == stdin)
                printf("Wrong value\n");
            err_count = 0;
        }
        matrix->arr[x][y] = elem;
    }
//    fgetc(f);
    return NO_ERROR;
}

int sparse_input_by_dots(FILE *f, struct sparse_matrix *matrix)
{
    struct matrix aux_matrix;
    aux_matrix.n = matrix->n;
    aux_matrix.m = matrix->m;
    int rc = input_by_dots(f, &aux_matrix);
    if (rc)
        return rc;
    int tmp_len = 0;
    for (int i = 0; i < aux_matrix.n; i++)
        for (int j = 0; j < aux_matrix.m; j++)
            if (aux_matrix.arr[i][j] != 0)
                tmp_len++;
    matrix->a = calloc(tmp_len, sizeof(int));
    matrix->ia = calloc(tmp_len, sizeof(int));
    matrix->ja = calloc(aux_matrix.m, sizeof(int));
    if (!matrix->a || !matrix->ia || !matrix->ja)
    {
        matrix_free(&aux_matrix);
        sparse_matrix_free(matrix);
        return MEM_ERROR;
    }
    matrix->n = aux_matrix.n;
    matrix->m = aux_matrix.m;
    matrix->elem_num = 0;
    int flag = 0;
    for (int j = 0; j < aux_matrix.m; j++)
    {
        int flag1 = 0, begin_row = matrix->elem_num;
        for (int i = 0; i < aux_matrix.n; i++)
        {
            if (aux_matrix.arr[i][j] != 0)
            {
                flag = 1;
                flag1 = 1;
                matrix->a[matrix->elem_num] = aux_matrix.arr[i][j];
                matrix->ia[matrix->elem_num] = i;
                matrix->elem_num++;
            }
        }
        if (flag1)
            matrix->ja[j] = begin_row;
        else
            matrix->ja[j] = (flag) ? matrix->ja[j - 1] : -1;
    }
    matrix_free(&aux_matrix);
    return NO_ERROR;
}

int str_matrix_input(FILE *f, struct matrix *matrix)
{
    if (f == stdin)
        printf("Input num of rows:");
    int rc = fscanf(f, "%d", &matrix->n);
    if (rc != 1 || matrix->n != 1)
        return DATA_ERROR;
    if (f == stdin)
        printf("Input num of columns:");
    rc = fscanf(f, "%d", &matrix->m);
    if (rc != 1 || matrix->m < 1)
        return DATA_ERROR;
    fgetc(f);
    rc = input(f, matrix);
    if (rc)
        return rc;
    return NO_ERROR;
}

int matrix_input(FILE *f, struct matrix *matrix)
{
    if (f == stdin)
        printf("Input num of rows:");
    int rc = fscanf(f, "%d", &matrix->n);
    if (rc != 1 || matrix->n < 1)
        return DATA_ERROR;
    if (f == stdin)
        printf("Input num of columns:");
    rc = fscanf(f, "%d", &matrix->m);
    if (rc != 1 || matrix->m < 1)
        return DATA_ERROR;
    fgetc(f);
    rc = input(f, matrix);
    if (rc)
        return rc;
    return NO_ERROR;
}

int sparse_str_matrix_input(FILE *f, struct sparse_matrix *matrix)
{
    if (f == stdin)
        printf("Input num of rows:");
    int rc = fscanf(f, "%d", &matrix->n);
    if (rc != 1 || matrix->n != 1)
        return DATA_ERROR;
    if (f == stdin)
        printf("Input num of columns:");
    rc = fscanf(f, "%d", &matrix->m);
    if (rc != 1 || matrix->m < 1)
        return DATA_ERROR;
    fgetc(f);
    rc = sparse_input(f, matrix);
    if (rc)
        return rc;
    return NO_ERROR;
}

int sparse_matrix_input(FILE *f, struct sparse_matrix *matrix)
{
    if (f == stdin)
        printf("Input num of rows:");
    int rc = fscanf(f, "%d", &matrix->n);
    if (rc != 1 || matrix->n < 1)
        return DATA_ERROR;
    if (f == stdin)
        printf("Input num of columns:");
    rc = fscanf(f, "%d", &matrix->m);
    if (rc != 1 || matrix->m < 1)
        return DATA_ERROR;
    fgetc(f);
    rc = sparse_input(f, matrix);
    if (rc)
        return rc;
    return NO_ERROR;
}

int str_matrix_input_by_dots(FILE *f, struct matrix *matrix)
{
    if (f == stdin)
        printf("Input num of rows:");
    int rc = fscanf(f, "%d", &matrix->n);
    if (rc != 1 || matrix->n != 1)
        return DATA_ERROR;
    if (f == stdin)
        printf("Input num of columns:");
    rc = fscanf(f, "%d", &matrix->m);
    if (rc != 1 || matrix->m < 1)
        return DATA_ERROR;
    fgetc(f);
    rc = input_by_dots(f, matrix);
    if (rc)
        return rc;
    return NO_ERROR;
}

int matrix_input_by_dots(FILE *f, struct matrix *matrix)
{
    if (f == stdin)
        printf("Input num of rows:");
    int rc = fscanf(f, "%d", &matrix->n);
    if (rc != 1 || matrix->n < 1)
        return DATA_ERROR;
    if (f == stdin)
        printf("Input num of columns:");
    rc = fscanf(f, "%d", &matrix->m);
    if (rc != 1 || matrix->m < 1)
        return DATA_ERROR;
    fgetc(f);
    rc = input_by_dots(f, matrix);
    if (rc)
        return rc;
    return NO_ERROR;
}

int sparse_str_matrix_input_by_dots(FILE *f, struct sparse_matrix *matrix)
{
    if (f == stdin)
        printf("Input num of rows:");
    int rc = fscanf(f, "%d", &matrix->n);
    if (rc != 1 || matrix->n != 1)
        return DATA_ERROR;
    if (f == stdin)
        printf("Input num of columns:");
    rc = fscanf(f, "%d", &matrix->m);
    if (rc != 1 || matrix->m < 1)
        return DATA_ERROR;
    fgetc(f);
    rc = sparse_input_by_dots(f, matrix);
    if (rc)
        return rc;
    return NO_ERROR;
}

int sparse_matrix_input_by_dots(FILE *f, struct sparse_matrix *matrix)
{
    if (f == stdin)
        printf("Input num of rows:");
    int rc = fscanf(f, "%d", &matrix->n);
    if (rc != 1 || matrix->n < 1)
        return DATA_ERROR;
    if (f == stdin)
        printf("Input num of columns:");
    rc = fscanf(f, "%d", &matrix->m);
    if (rc != 1 || matrix->m < 1)
        return DATA_ERROR;
    fgetc(f);
    rc = sparse_input_by_dots(f, matrix);
    if (rc)
        return rc;
    return NO_ERROR;
}

void print(struct matrix *matrix)
{
    for (int i = 0; i < matrix->n; i++)
        for (int j = 0; j < matrix->m; j++)
            printf(((j == matrix->m - 1) ? "%d\n" : "%d "), matrix->arr[i][j]);
}

int sparse_print(struct sparse_matrix *matrix)
{
//    if (matrix->n > 15 || matrix->m > 15)
//    {
        printf("a: ");
        for (int i = 0; i < matrix->elem_num; i++)
            printf((i == matrix->elem_num - 1) ? "%d\n" : "%d ", matrix->a[i]);
        printf("ia: ");
        for (int i = 0; i < matrix->elem_num; i++)
            printf((i == matrix->elem_num - 1) ? "%d\n" : "%d ", matrix->ia[i]);
        printf("ja: ");
        for (int i = 0; i < matrix->m; i++)
            printf((i == matrix->m - 1) ? "%d\n" : "%d ", matrix->ja[i]);
//    }
//    else
//    {
//        struct matrix aux_matrix;
//        aux_matrix.m = matrix->m;
//        aux_matrix.n = 0;
//        aux_matrix.arr = calloc(matrix->n, sizeof(int *));
//        if (!aux_matrix.arr)
//        {
//            matrix_free(&aux_matrix);
//            return MEM_ERROR;
//        }
//        for (int i = 0; i < matrix->n; i++)
//        {
//            aux_matrix.arr[i] = calloc(matrix->m, sizeof(int));
//            aux_matrix.n++;
//            if (!aux_matrix.arr[i])
//            {
//                matrix_free(&aux_matrix);
//                return MEM_ERROR;
//            }
//        }
//        int last_ja = -1;
//        int z = 0;
//        for (int i = 0; i < matrix->m; i++)
//        {
//            if (matrix->ja[i] == last_ja)
//                continue;
//            else
//            {
//                last_ja = matrix->ja[i];
//                int last_ia = -1;
//                while (last_ia < matrix->ia[z])
//                {
//                    aux_matrix.arr[matrix->ia[z]][i] = matrix->a[z];
//                    last_ia = matrix->ia[z];
//                    z++;
//                }
//            }
//        }
//        print(&aux_matrix);
//        matrix_free(&aux_matrix);
//    }
    return NO_ERROR;
}