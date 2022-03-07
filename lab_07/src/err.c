#include "../inc/err.h"

int err_handl(int rc)
{
    switch (rc)
    {
        case ARG_ERROR:
            printf("Arg error\n");
            break;
        case FILE_ERROR:
            printf("File error\n");
            break;
        case EMPTY_FILE:
            printf("Empty file\n");
            break;
        case MEM_ERROR:
            printf("Mem error\n");
            break;
        case DATA_ERROR:
            printf("Data error\n");
            break;
        case OUTPUT_ERROR:
            printf("Output error\n");
            break;
    }
    return rc;
}
