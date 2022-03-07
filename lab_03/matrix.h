#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

#include "error.h"

//Стандартная матрица
struct matrix
{
    int **arr;
    int n;
    int m;
};

//Разряженная матрица
struct sparse_matrix
{
    int *a;
    int *ia;
    int *ja;
    int n;
    int m;
    int elem_num;
};

// Высвобождение памяти стандартной матрицы
void matrix_free(struct matrix *matrix);

// Высвобождение памяти разряженной матрицы
void sparse_matrix_free(struct sparse_matrix *matrix);

// Умножение стандартных строки матрицы и матрицы
int mult_matrix(struct matrix *vector, struct matrix *matrix, struct matrix *res_matrix);

// Умножение разряженных строки матрицы и матрицы
int sparse_mult_matrix(struct sparse_matrix *matrix1, struct sparse_matrix *matrix2, struct sparse_matrix *res_matrix);

#endif
