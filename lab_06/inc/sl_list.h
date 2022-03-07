#ifndef DTS_SL_LIST_H
#define DTS_SL_LIST_H

#include <stdlib.h>
#include <string.h>

typedef struct sl_list sl_list;

struct sl_list
{
    char *data;
    sl_list *next;
};

void sl_list_free_node(sl_list *node);

void sl_list_free_list(sl_list *head);

sl_list *sl_list_init_node(char *data);

sl_list *sl_list_push_back(sl_list *head, sl_list *node, int *n);

sl_list *sl_list_pop_back(sl_list *head, sl_list *node);

sl_list *sl_list_pop_front(sl_list *head, sl_list *node);

sl_list *sl_list_search(sl_list *head, char *data, int *n);

sl_list *sl_list_remove(sl_list *head, char *data, sl_list **res);

#endif 
