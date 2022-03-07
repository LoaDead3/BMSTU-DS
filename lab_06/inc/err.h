#ifndef DTS_ERR_H
#define DTS_ERR_H

#include <stdio.h>

#define NO_ERRORS 0
#define ARG_ERROR 1
#define FILE_ERROR 2
#define ADD_EXISTED_ELEM_IN_TREE 3
#define EMPTY_FILE 4
#define DATA_ERROR 5
#define MEM_ERROR 6

int err_handl(int rc);

#endif 
