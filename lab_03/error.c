#include "error.h"

int error_hand(int rc)
{
    switch (rc)
    {
        case ARG_ERROR:
            printf("CMD arguments error\n");
            break;
        case FILE_ERROR:
            printf("Opening file error\n");
            break;
        case DATA_ERROR:
            printf("Wrong data\n");
            break;
        case MEM_ERROR:
            printf("Memory error\n");
            break;
        case IMP_MATRIX_MULT:
            printf("Impossible matrix multiplication\n");
            break;
        default:
            break;
    }
    return rc;
}