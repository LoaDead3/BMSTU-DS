#include "../inc/sl_list_io.h"

void list_print(sl_list *head)
{
    for (; head ; head = head->next)
        printf((!head->next) ? "%s" : "%s,", head->data);
    printf("\n");
}
