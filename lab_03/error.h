#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

#define NO_ERROR 0
#define ARG_ERROR 1
#define FILE_ERROR 2
#define DATA_ERROR 3
#define MEM_ERROR 4
#define IMP_MATRIX_MULT 5

int error_hand(int rc);

#endif
