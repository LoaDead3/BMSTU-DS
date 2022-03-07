#include "../inc/graph.h"

void edge_free_node(edge *node)
{
    free(node);
}

void edge_free_list(edge *head)
{
    edge *next = NULL;
    for (; head; head = next)
    {
        next = head->next;
        edge_free_node(head);
    }
}

edge *edge_init_node(int start, int end)
{
    edge *node = calloc(1, sizeof(edge));
    if (node != NULL)
    {
        node->start = start;
        node->end = end;
    }
    return node;
}

edge *edge_push_back(edge *head, edge *node)
{
    if (!head)
        head = node;
    else
    {
        edge *cur = head;
        for (; cur->next; cur = cur->next);
        cur->next = node;
    }
    return head;
}

edge *edge_remove(edge *head, int num)
{
    edge *new = NULL;
    if (!head)
        return new;
    edge *nxt = head->next;
    while (head && (head->start == num || head->end == num))
    {
        nxt = head->next;
        edge_free_node(head);
        head = nxt;
    }
    if(!head)
        return NULL;
    new = head;
    edge *prev = head;
    head = head->next;
    for (; head; head = head->next)
    {
        if (head->start == num || head->end == num)
        {
            prev->next = head->next;
            edge_free_node(head);
            head = prev;
        }
        prev = head;
    }
    return new;
}

void graph_free(graph *gr)
{
    if (!gr)
        return;
    edge_free_list(gr->edge_list);
}

void graph_add_edge(graph *gr, edge *node)
{
    gr->edge_list = edge_push_back(gr->edge_list, node);
}

int graph_is_edge_exist(graph *gr, int d1, int d2)
{
    int res = 0;
    edge *cur = gr->edge_list;
    while (cur && (cur->start <= d1 || (cur->start == d1 && cur->end <= d2)))
    {
        if (cur->start == d1 && cur->end == d2)
        {
            res = 1;
            break;
        }
        cur = cur->next;
    }
    return res;
}

void graph_remove_edge(graph *gr, int num)
{
    gr->edge_list = edge_remove(gr->edge_list, num);
    gr->v_num--;
}

int graph_copy(graph *dst, graph *src)
{
    edge *pdst = NULL, *psrc = src->edge_list;
    for (; psrc; psrc = psrc->next)
    {
        edge *cur = edge_init_node(psrc->start, psrc->end);
        if (!cur)
        {
            edge_free_list(psrc);
            return MEM_ERROR;
        }
        pdst = edge_push_back(pdst, cur);
    }
    dst->v_num = src->v_num;
    dst->edge_list = pdst;
    return NO_ERRORS;
}

int get_adj_list(graph *gr, int num, int **adj, int *n)
{
    edge *cur = gr->edge_list;
    *n = 0;
    *adj = calloc(gr->v_num, sizeof(int));
    if (!(*adj))
        return MEM_ERROR;
    for (; cur; cur = cur->next)
    {
        if (cur->start == num)
            (*adj)[(*n)++] = cur->end;
        if (cur->end == num)
            (*adj)[(*n)++] = cur->start;
    }
    if (*n == 0)
    {
        free(*adj);
        return NO_ADJ;
    }
    int *tmp = realloc(*adj, sizeof(int) * *n);
    if (!tmp)
    {
        free(*adj);
        return MEM_ERROR;
    }
    *adj = tmp;
    return NO_ERRORS;
}

int dfs_tree_check(graph *gr, int start, int *visited)
{
    int res = 1;
    visited[start - 1] = 1;
    int *adj = NULL, n = 0;
    get_adj_list(gr, start, &adj, &n);
    for (int i = 0; i < n; i++)
    {
        if (visited[adj[i] - 1] == 2)
        {
            res = 0;
            break;
        }
        if (visited[adj[i] - 1] == 1)
            continue;
        int tmp = dfs_tree_check(gr, adj[i], visited);
        if (tmp == 0)
        {
            res = 0;
            break;
        }
    }
    visited[start - 1] = 2;
    free(adj);
    return res;
}

int get_name(int *rename, int *rn_last, int num)
{
    for (int i = 0; i < *rn_last; i++)
    {
        if(rename[i] == num)
            return i + 1;
    }
    rename[*rn_last] = num;
    return ++(*rn_last);
}

int get_val(int *rename, int num)
{
    return rename[num - 1];
}


int graph_is_tree(graph *gr, int *res)
{
    int *visited = calloc(gr->v_num, sizeof(int));
    if (!visited)
        return MEM_ERROR;
    int *rename = calloc(gr->v_num, sizeof(int));
    int rn_last = 0;
    edge *iter = gr->edge_list;
    for (; iter; iter = iter->next)
    {
        iter->start = get_name(rename, &rn_last, iter->start);
        iter->end = get_name(rename, &rn_last, iter->end);
    }
    *res = dfs_tree_check(gr, gr->edge_list[0].start, visited);
    iter = gr->edge_list;
    for (; iter; iter = iter->next)
    {
        iter->start = get_val(rename, iter->start);
        iter->end = get_val(rename, iter->end);
    }
    free(rename);
    free(visited);
    return NO_ERRORS;
}

int dfs_find_component(graph *gr, int start, int *visited, graph *comp)
{
    int res = 0;
    visited[start - 1] = 1;
    int *adj = NULL, n = 0;
    get_adj_list(gr, start, &adj, &n);
    for (int i = 0; i < n; i++)
    {
        if (visited[adj[i] - 1] == 1)
            continue;
        edge *cur = edge_init_node(start, adj[i]);
        if (!cur)
            return MEM_ERROR;
        comp->edge_list = edge_push_back(comp->edge_list, cur);
        if (visited[adj[i] - 1] == 0)
        {
            res = dfs_find_component(gr, adj[i], visited, comp);
            if (res)
                return res;
        }
    }
    visited[start - 1] = 2;
    return res;
}

int find_all_components(graph *gr, graph **comps, int *n)
{
    int *visited = calloc(gr->v_num, sizeof(int));
    int *rename = calloc(gr->v_num, sizeof(int));
    int rn_last = 0;
    *comps = calloc(gr->v_num, sizeof(graph));
    if (!visited)
        return MEM_ERROR;
    *n = 0;
    int rc = 0;
    edge *iter = gr->edge_list;
    for (; iter; iter = iter->next)
    {
        iter->start = get_name(rename, &rn_last, iter->start);
        iter->end = get_name(rename, &rn_last, iter->end);
    }
    while (1)
    {
        int i = 0, flag = 0;
        for (; i < gr->v_num; i++)
            if (visited[i] < 1)
            {
                flag = 1;
                break;
            }
        if (flag == 0)
            break;
        rc = dfs_find_component(gr, i + 1, visited, &(*comps)[*n]);
        if (rc)
        {
            for (int j = 0; j < *n + 1; j++)
                graph_free(comps[j]);
            free(visited);
            return MEM_ERROR;
        }
        int tmp = 0;
        for (; i < gr->v_num; i++)
        {
            if (visited[i] == 2)
            {
                tmp++;
                visited[i] = 3;
            }
        }
        iter = (*comps)[*n].edge_list;
        for (; iter; iter = iter->next)
        {
            iter->start = get_val(rename, iter->start);
            iter->end = get_val(rename, iter->end);
        }
        (*comps)[*n].v_num = tmp;
        (*n)++;
    }
    free(rename);
    free(visited);
    return NO_ERRORS;
};

int show_tree_in_graph(graph *gr)
{
    int i = 1, rc = 0;
    edge *cnt = gr->edge_list;
    for (; cnt; cnt = cnt->next)
    {
        graph cur = {0, NULL};
        rc = graph_copy(&cur, gr);
        if (rc)
        {
            graph_free(&cur);
            return rc;
        }
        graph_remove_edge(&cur, i);
        if(cur.v_num == 0)
        {
            printf("After del there are no graph\n");
            graph_free(&cur);
            return NO_ERRORS;
        }
        int *check = calloc(gr->v_num, sizeof(int));
        edge *ch = cur.edge_list;
        for (; ch; ch = ch->next)
        {
            check[ch->start - 1]++;
            check[ch->end - 1]++;
        }
        int is_tree = 0, tree_num = 0;
        for (int j = 0; j < gr->v_num; j++)
        {
            if (check[j] < 1 && i != j + 1)
            {
                is_tree = 1;
                tree_num = j + 1;
                break;
            }
        }
        free(check);
        if (is_tree)
        {
            printf("The graph can turn into a tree by removing the vertex %d\n"
                   "The tree consists of one vertex %d", i, tree_num);
            graph_free(&cur);
            return NO_ERRORS;
        }
        graph *comp = NULL;
        int n = 0;
        rc = find_all_components(&cur, &comp, &n);
        if (rc)
        {
            graph_free(&cur);
            return rc;
        }
        for (int j = 0; j < n; j++)
        {
            int tmp = 0;
            rc = graph_is_tree(&comp[j], &tmp);
            if (rc)
            {
                for (int k = 0; k < n; k++)
                    graph_free(&comp[k]);
//                    graph_free(&cur);
                return rc;
            }
            if (tmp == 1)
            {
                printf("The graph can turn into a tree by removing the vertex %d\n"
                       "Output in svg file\n", i);
                rc = graph_print(&comp[j], "res");
                for (int k = 0; k < n; k++)
                    graph_free(&comp[k]);
//                    graph_free(&cur);
                return NO_ERRORS;
            }
        }
        for (int k = 0; k < n; k++)
            graph_free(&comp[k]);
//        graph_free(&cur);
        i++;
    }
    printf("A graph cannot turn into a tree\n");
    return NO_ERRORS;
}

