#include "../inc/err.h"

int err_handl(int rc)
{
    switch (rc)
    {
        case NO_ERRORS:
        {
            printf("No error\n");
            break;
        }
        case ARG_ERROR:
        {
            printf("Wrong program arguments\n");
            break;
        }
        case FILE_ERROR:
        {
            printf("File error\n");
            break;
        }
        case ADD_EXISTED_ELEM_IN_TREE:
        {
            printf("Element existed\n");
            break;
        }
        case EMPTY_FILE:
        {
            printf("Empty file\n");
            break;
        }
        case DATA_ERROR:
        {
            printf("Data error\n");
            break;
        }
        case MEM_ERROR:
        {
            printf("Memory error\n");
            break;
        }
        default:
        {
            printf("Unknown error\n");
            break;
        }
    }
    return rc;
}

