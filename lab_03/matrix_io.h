#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "error.h"
#include "matrix.h"

#define STR_LEN 100000
#define ARR_LEN 50000

//Ввод стандартной строки матрицы
int str_matrix_input(FILE *f, struct matrix *matrix);

//Ввод стандартной матрицы
int matrix_input(FILE *f, struct matrix *matrix);

//Ввод разряженной строки матрицы
int sparse_str_matrix_input(FILE *f, struct sparse_matrix *matrix);

//Ввод разряженной матрицы
int sparse_matrix_input(FILE *f, struct sparse_matrix *matrix);

//Ввод стандартной строки матрицы по точкам
int str_matrix_input_by_dots(FILE *f, struct matrix *matrix);

//Ввод стандартной матрицы по точкам
int matrix_input_by_dots(FILE *f, struct matrix *matrix);

//Ввод разряженной строки матрицы по точкам
int sparse_str_matrix_input_by_dots(FILE *f, struct sparse_matrix *matrix);

//Ввод разряженной строки матрицы по точкам
int sparse_matrix_input_by_dots(FILE *f, struct sparse_matrix *matrix);

//Вывод стандартных строки матрицы и матрицы
void print(struct matrix *matrix);

//Вывод разряженных строки матрицы и матрицы
int sparse_print(struct sparse_matrix *matrix);

#endif
