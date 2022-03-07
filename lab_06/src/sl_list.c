#include "../inc/sl_list.h"

void sl_list_free_node(sl_list *node)
{
    free(node->data);
    free(node);
}

void sl_list_free_list(sl_list *head)
{
    sl_list *next = NULL;
    for (; head; head = next)
    {
        next = head->next;
        sl_list_free_node(head);
    }
}

sl_list *sl_list_init_node(char *data)
{
    if (data == NULL)
        return NULL;
    sl_list *node = calloc(1, sizeof(sl_list));
    if (node != NULL)
    {
        node->data = calloc(strlen(data) + 1, sizeof(char));
        if (!node->data)
        {
            sl_list_free_node(node);
            node = NULL;
        }
        else
            strcpy(node->data, data);
    }
    return node;
}


sl_list *sl_list_push_back(sl_list *head, sl_list *node, int *n)
{
    *n = 0;
    if (!head)
        head = node;
    else
    {
        sl_list *cur = head;
        for (; cur->next; cur = cur->next)
            (*n)++;
        cur->next = node;
    }
    return head;
}

sl_list *sl_list_pop_back(sl_list *head, sl_list *node)
{
    if (!head)
        return NULL;
    sl_list *cur = head, *prev = head;
    for (; cur->next; cur = cur->next)
        prev = cur;
    prev->next = NULL;
    node = cur;
    if (cur == head)
        head = NULL;
    return head;
}

sl_list *sl_list_pop_front(sl_list *head, sl_list *node)
{
    if (!head)
        return NULL;
    node = head;
    return head->next;
}

//int sl_list_cmp_node(sl_list *n1, sl_list *n2)
//{
//    return strcmp(n1->data, n2->data);
//}

sl_list *sl_list_search(sl_list *head, char *data, int *n)
{
    *n = 0;
    for (; head && strcmp(head->data, data) != 0; head = head->next, (*n)++);
    return head;
}

sl_list *sl_list_remove(sl_list *head, char *data, sl_list **res)
{
    sl_list *new = NULL;
    *res = NULL;
    if (!head)
        return new;
    if (strcmp(head->data, data) == 0)
    {
        new = head->next;
        *res = head;
    }
    else
    {
        new = head;
        sl_list *prev = head;
        for (; head && strcmp(head->data, data) != 0; head = head->next)
            prev = head;
        if (head)
        {
            prev->next = head->next;
            *res = head;
        }
    }
    return new;
}

