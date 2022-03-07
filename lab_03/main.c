#include <stdio.h>

#include "error.h"
#include "matrix.h"
#include "matrix_io.h"

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    FILE *f;
    if (argc == 2)
        f = fopen(argv[1], "r");
    else if (argc == 1)
        f = stdin;
    else
        return error_hand(ARG_ERROR);
    if (!f)
        return error_hand(FILE_ERROR);
    int rc = 0;
    struct sparse_matrix matrix_v, matrix, res_matrix;
    printf("The program multiplies the matrix row by matrix using the sparse form. You can enter\n"
           "data in standard form and by points. If the result of the matrix is less than 15 * 15,\n"
           "then it is displayed in the normal form, otherwise in the sparse form.\n");

    while (1)
    {
        if(f == stdin)
            printf("Chose input type\n1-Standart input\n2-Input by dots\nChoice:");
        int c = 0;
        rc = fscanf(f, "%d", &c);
        if (rc != 1)
            return error_hand(DATA_ERROR);
        if (c == 1)
        {
            if(f == stdin)
                printf("Input matrix string\n");
            rc = sparse_str_matrix_input(f, &matrix_v);
            if (rc)
                return error_hand(rc);
            if(f == stdin)
                printf("Input matrix\n");
            rc = sparse_matrix_input(f, &matrix);
            if (rc)
            {
                sparse_matrix_free(&matrix_v);
                return error_hand(rc);
            }
            break;
        }
        else if (c == 2)
        {
            if(f == stdin)
                printf("Input matrix string\n");
            rc = sparse_str_matrix_input_by_dots(f, &matrix_v);
            if (rc)
                return error_hand(rc);
            if(f == stdin)
                printf("Input matrix\n");
            rc = sparse_matrix_input_by_dots(f, &matrix);
            if (rc)
            {
                sparse_matrix_free(&matrix_v);
                return error_hand(rc);
            }
            printf("Str:\n");
            sparse_print(&matrix_v);
            printf("Matrix:\n");
            sparse_print(&matrix);
            printf("\n");
            break;
        }
        else
        {
            printf("Wrong menu item\n");
        }
    }
    rc = sparse_mult_matrix(&matrix_v, &matrix, &res_matrix);
    if (error_hand(rc))
    {
        sparse_matrix_free(&matrix_v);
        sparse_matrix_free(&matrix);
        return rc;
    }
    sparse_print(&matrix_v);
    printf("\n");
    sparse_print(&matrix);
    printf("\n");
    printf("Result:\n");
    rc = sparse_print(&res_matrix);
    sparse_matrix_free(&matrix_v);
//    printf("1\n");
    sparse_matrix_free(&matrix);
//    printf("2\n");
    sparse_matrix_free(&res_matrix);
//    printf("3\n");
    if(rc)
        error_hand(rc);
    return NO_ERROR;
}
