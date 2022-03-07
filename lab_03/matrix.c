#include "matrix.h"


void matrix_free(struct matrix *matrix)
{
    for (int i = 0; i < matrix->n; i++)
        free(matrix->arr[i]);
    free(matrix->arr);
}


void sparse_matrix_free(struct sparse_matrix *matrix)
{
    free(matrix->a);
    free(matrix->ia);
    free(matrix->ja);
}

int mult_matrix(struct matrix *matrix1, struct matrix *matrix2, struct matrix *res_matrix)
{
    if (matrix1->m != matrix2->n)
        return IMP_MATRIX_MULT;
    res_matrix->arr = calloc(matrix1->n, sizeof(int *));
    if (!res_matrix->arr)
    {
        matrix_free(res_matrix);
        return MEM_ERROR;
    }
    res_matrix->m = matrix2->m;
    res_matrix->n = 0;
    for (int i = 0; i < matrix1->n; i++)
    {
        res_matrix->arr[res_matrix->n++] = calloc(res_matrix->m, sizeof(int));
        if (!res_matrix->arr[i])
        {
            matrix_free(res_matrix);
            return MEM_ERROR;
        }
    }
    if (!res_matrix->arr[0])
    {
        matrix_free(res_matrix);
        return MEM_ERROR;
    }
    for (int i = 0; i < matrix1->n; i++)
        for (int j = 0; j < matrix2->m; j++)
            for (int k = 0; k < matrix1->m; k++)
                res_matrix->arr[i][j] += matrix1->arr[i][k] * matrix2->arr[k][j];
    return NO_ERROR;
}

int in_arr(int *arr, int n, int a)
{
    if (a == 0)
    {
        if (arr[0] != -1)
            return 1;
    }
    else
    {
        if (arr[a - 1] != arr[a])
            return 1;
    }
    return 0;
}

int get_elem(struct sparse_matrix *matrix, int index)
{
    return matrix->a[matrix->ja[index]];
}

int next_ja(struct sparse_matrix *matrix, int i)
{
    int cur = matrix->ja[i];
    int tmp = matrix->elem_num;
    for (int j = i; j < matrix->m; j++)
    {
        int a = matrix->ja[j];
        if (matrix->ja[j] > cur)
        {
            tmp = matrix->ja[j];
            break;
        }
    }
    return tmp;
}


int sparse_mult_matrix(struct sparse_matrix *matrix1, struct sparse_matrix *matrix2, struct sparse_matrix *res_matrix)
{
    if (matrix1->m != matrix2->n)
        return IMP_MATRIX_MULT;
    res_matrix->a = calloc(matrix2->m, sizeof(int));
    res_matrix->ia = calloc(matrix2->m, sizeof(int));
    res_matrix->ja = calloc(matrix2->m, sizeof(int));
    if (!res_matrix->a || !res_matrix->ia || !res_matrix->ja)
    {
        sparse_matrix_free(res_matrix);
        return MEM_ERROR;
    }
    res_matrix->elem_num = 0;
    res_matrix->n = 1;
    res_matrix->m = matrix2->m;
    int last_begin = -1, z = 0, tmp_start = -1, c = 0;
    for (int i = 0; i < matrix2->m; i++)
    {
        if (matrix2->ja[i] == last_begin)
        {
            res_matrix->ja[c++] = tmp_start;
            continue;
        }
        else
        {
            int tmp = 0;
            while (z < next_ja(matrix2, i))
            {
                if (in_arr(matrix1->ja, matrix1->m, matrix2->ia[z]))
                    tmp += matrix2->a[z] * get_elem(matrix1, matrix2->ia[z]);
                z++;
            }
            if (tmp != 0)
            {
                res_matrix->ja[c++] = ++tmp_start;
//                tmp_start = i;
                last_begin = matrix2->ja[i];
                res_matrix->a[res_matrix->elem_num] = tmp;
                res_matrix->elem_num++;
            }
            else
                res_matrix->ja[c++] = tmp_start;
        }
    }
    if (res_matrix->elem_num != 0)
    {
        int *tmp1 = realloc(res_matrix->a, sizeof(int) * res_matrix->elem_num);
        if (!tmp1)
        {
            free(tmp1);
            sparse_matrix_free(res_matrix);
            return MEM_ERROR;
        }
        int *tmp2 = realloc(res_matrix->ia, sizeof(int) * res_matrix->elem_num);
        if (!tmp2)
        {
            free(tmp2);
            sparse_matrix_free(res_matrix);
            return MEM_ERROR;
        }
    }
    return NO_ERROR;
}