#include "../head/error.h"

int error_handler(int error)
{
    switch (error)
    {
        case ARG_ERROR:
            printf("CMD arguments error\n");
            break;
        case FILE_ERROR:
            printf("File error\n");
            break;
        case TO_LONG_STR:
            printf("String overflow\n");
            break;
        case MEM_ERROR:
            printf("Memory error\n");
            break;
        case WRONG_DATA:
            printf("Wrong input data\n");
            break;
        case NO_DATA:
            printf("No data\n");
            break;
        default:
            printf("Error handling error\n");
            break;
    }
    char *tmp;
    scanf("%s", &tmp);
    return error;
}