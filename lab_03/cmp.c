#include <stdio.h>
#include <time.h>
#include "matrix_io.h"
#include "matrix.h"

int cmp(char *file, int pers)
{
    double t1 = 0, t2 = 0;
    unsigned long long s1 = 0, s2 = 0;
    FILE *f = fopen(file, "r");
    if (!f)
        return 1;
    struct matrix matrix_v, matrix, res_matrix;
    int rc = str_matrix_input(f, &matrix_v);
    if (rc)
        return rc;
    rc = matrix_input(f, &matrix);
    if (rc)
    {
        matrix_free(&matrix_v);
        return rc;
    }
    for (int i = 0; i < 5; i++)
    {
        clock_t begin = clock();
        rc = mult_matrix(&matrix_v, &matrix, &res_matrix);
        clock_t end = clock();
        if (rc)
        {
            matrix_free(&matrix_v);
            matrix_free(&matrix);
            return rc;
        }
        t1 += ((double) (end - begin));
        matrix_free(&res_matrix);
    }
    t1  /= 5;
    s1 += sizeof(int) * (matrix_v.m * matrix_v.n + 2) + sizeof(int *) * (matrix_v.n + 1);
    s1 += sizeof(int) * (matrix.m * matrix.n + 2) + sizeof(int *) * (matrix.n + 1);
    s1 += sizeof(int) * (res_matrix.m * res_matrix.n + 2) + sizeof(int *) * (res_matrix.n + 1);
    matrix_free(&matrix_v);
    matrix_free(&matrix);
    rewind(f);

    printf("%d%\n", pers);
    printf("standart: %.3lf %llu\n", t1, s1);

    struct sparse_matrix sparseMatrix_v, sparseMatrix, res_sparseMatrix;
    rc = sparse_str_matrix_input(f, &sparseMatrix_v);
    if(rc)
        return rc;
    rc = sparse_matrix_input(f, &sparseMatrix);
    if(rc)
    {
        sparse_matrix_free(&sparseMatrix_v);
        return rc;
    }
    for (int i = 0; i < 5; i++)
    {
//        printf("%d\n", i);
        clock_t begin = clock();
        rc = sparse_mult_matrix(&sparseMatrix_v, &sparseMatrix, &res_sparseMatrix);
        clock_t end = clock();
        if (rc)
        {
            sparse_matrix_free(&sparseMatrix_v);
            sparse_matrix_free(&sparseMatrix);
            return rc;
        }
        t2 += ((double) (end - begin));
        sparse_matrix_free(&res_sparseMatrix);
    }
    t2 /= 5;
    s2+= sizeof(int) * (sparseMatrix_v.elem_num) * 2 + sizeof(int) * (sparseMatrix_v.m + 3) + sizeof(int *) * 3;
    s2+= sizeof(int) * (sparseMatrix.elem_num) * 2 + sizeof(int) * (sparseMatrix.m + 3) + sizeof(int *) * 3;
    s2+= sizeof(int) * (res_sparseMatrix.elem_num) * 2 + sizeof(int) * (res_sparseMatrix.m + 3) + sizeof(int *) * 3;
    sparse_matrix_free(&sparseMatrix_v);
    sparse_matrix_free(&sparseMatrix);

    printf("sparse: %.3lf %llu\n", t2, s2);
    return 0;
}

int main()
{
    setbuf(stdout, NULL);
    int rc = 0;
    rc = cmp("../data/data0.txt", 0);
    if(rc)
        return rc;
    rc = cmp("../data/data20.txt", 20);
    if(rc)
        return rc;
    rc = cmp("../data/data40.txt", 40);
    if(rc)
        return rc;
    rc = cmp("../data/data60.txt", 60);
    if(rc)
        return rc;
    rc = cmp("../data/data80.txt", 80);
    if(rc)
        return rc;
    rc = cmp("../data/data100.txt", 100);
    if(rc)
        return rc;
    return 0;
}

