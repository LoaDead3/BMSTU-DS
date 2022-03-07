#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

#define ARG_ERROR 1
#define FILE_ERROR 2
#define TO_LONG_STR 3
#define MEM_ERROR 4
#define WRONG_DATA 5
#define NO_DATA 6

int error_handler(int error);

#endif
