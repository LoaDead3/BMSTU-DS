#include "../inc/tree.h"

int bs_tree_cmp(bs_tree *n1, bs_tree *n2)
{
    return strcmp(n1->data, n2->data);
}

void bs_tree_node_free(bs_tree *node)
{
    free(node->data);
    free(node);
}

void bs_tree_free(bs_tree *tree)
{
    if (!tree)
        return;
    bs_tree_free(tree->left);
    bs_tree_free(tree->right);
    bs_tree_node_free(tree);
}

bs_tree *bs_tree_node_init(char *data)
{
    bs_tree *node = calloc(1, sizeof(bs_tree));
    if (node != NULL)
    {
        node->data = calloc(strlen(data) + 1, sizeof(char));
        if (!node->data)
        {
            bs_tree_node_free(node);
            node = NULL;
        }
        else
            strcpy(node->data, data);
    }
    return node;
}

int bs_tree_insert_node(bs_tree **tree, bs_tree *node, int *n)
{
    if (!node)
        return DATA_ERROR;
    int rc = NO_ERRORS;
    if (!(*tree))
        *tree = node;
    else if (bs_tree_cmp(node, *tree) < 0)
    {
        (*n)++;
        rc = bs_tree_insert_node(&(*tree)->left, node, n);
    }
    else if (bs_tree_cmp(node, *tree) > 0)
    {
        (*n)++;
        rc = bs_tree_insert_node(&(*tree)->right, node, n);
    }
    else
        rc = ADD_EXISTED_ELEM_IN_TREE;
    return rc;
}

int bs_tree_insert_node_char(bs_tree **tree, char *data, int *n)
{
    *n = 0;
    bs_tree *node = bs_tree_node_init(data);
    int rc = bs_tree_insert_node(tree, node, n);
    if (rc)
        bs_tree_node_free(node);
    return rc;
}

bs_tree *bs_tree_search(bs_tree *tree, bs_tree *node, int *n)
{
    if (!node || !tree)
        return NULL;
    bs_tree *res = NULL;
    if (bs_tree_cmp(node, tree) < 0)
    {
        (*n)++;
        res = bs_tree_search(tree->left, node, n);
    }
    else if (bs_tree_cmp(node, tree) > 0)
    {
        (*n)++;
        res = bs_tree_search(tree->right, node, n);
    }
    else
        res = tree;
    return res;
}

bs_tree *bs_tree_search_char(bs_tree *tree, char *data, int *n)
{
    *n = 0;
    bs_tree *node = bs_tree_node_init(data);
    bs_tree *res = bs_tree_search(tree, node, n);
    bs_tree_node_free(node);
    return res;
}

bs_tree *bs_tree_search_max(bs_tree *tree)
{
    if (!tree)
        return NULL;
    if (!tree->right)
        return tree;
    return bs_tree_search_max(tree->right);
}

void assign(bs_tree *dst, bs_tree *src)
{
    if (strlen(dst->data) != strlen(src->data))
    {
        char *tmp = realloc(dst->data, (strlen(src->data) + 1) * sizeof(char));
        if (!tmp)
            return;
        dst->data = tmp;
    }
    strcpy(dst->data, src->data);
    dst->data[strlen(src->data)] = '\0';
}

bs_tree *bs_tree_remove(bs_tree *node, char *data)
{
    if (node == NULL)
        return NULL;
    if (strcmp(data, node->data) < 0)
        node->left = bs_tree_remove(node->left, data);
    else if (strcmp(data, node->data) > 0)
        node->right = bs_tree_remove(node->right, data);
    else if (node->left != NULL && node->right != NULL)
    {
        assign(node, bs_tree_search_max(node->left));
        node->left = bs_tree_remove(node->left, node->data);
    }
    else
    {
        if (node->left != NULL)
        {
            assign(node, node->left);
            bs_tree *tmp = node->left;
            node->right = node->left->right;
            node->left = node->left->left;
            bs_tree_node_free(tmp);
        }
        else if (node->right)
        {
            assign(node, node->right);
            bs_tree *tmp = node->right;
            node->left = node->right->left;
            node->right = node->right->right;
            bs_tree_node_free(tmp);
        }
        else
        {
            bs_tree_node_free(node);
            node = NULL;
        }
    }
    return node;
}


void bs_tree_nlr_detour(bs_tree *tree)
{
    if (!tree)
        return;
    bs_tree_node_print(tree);
    bs_tree_nlr_detour(tree->left);
    bs_tree_nlr_detour(tree->right);
}

void bs_tree_lnr_detour(bs_tree *tree)
{
    if (!tree)
        return;
    bs_tree_lnr_detour(tree->left);
    bs_tree_node_print(tree);
    bs_tree_lnr_detour(tree->right);
}

void bs_tree_lrn_detour(bs_tree *tree)
{
    if (!tree)
        return;
    bs_tree_lrn_detour(tree->left);
    bs_tree_lrn_detour(tree->right);
    bs_tree_node_print(tree);
}

//AVL

int avl_tree_cmp(avl_tree *n1, avl_tree *n2)
{
    return strcmp(n1->data, n2->data);
}

void avl_tree_node_free(avl_tree *node)
{
    free(node->data);
    free(node);
}

void avl_tree_free(avl_tree *tree)
{
    if (!tree)
        return;
    avl_tree_free(tree->left);
    avl_tree_free(tree->right);
    avl_tree_node_free(tree);
}

avl_tree *avl_tree_node_init(char *data)
{
    avl_tree *node = calloc(1, sizeof(avl_tree));
    if (node != NULL)
    {
        node->data = calloc(strlen(data) + 1, sizeof(char));
        if (!node->data)
        {
            avl_tree_node_free(node);
            node = NULL;
        }
        else
            strcpy(node->data, data);
    }
    return node;
}

avl_tree *_avl_tree_create(char **arr, int l, int r)
{
    if (r < l)
        return NULL;
    int mid = (l + r) / 2;
    avl_tree *node = avl_tree_node_init(arr[mid]);
    node->height = 1;
    node->left = _avl_tree_create(arr, l, mid - 1);
    node->right = _avl_tree_create(arr, mid + 1, r);
    if (node->right != NULL && node->left != NULL)
    {
        if (node->left->height >= node->right->height)
            node->height = node->left->height + 1;
        else
            node->height = node->right->height + 1;
    }
    else if (node->right != NULL)
        node->height = node->right->height + 1;
    else if (node->left != NULL)
        node->height = node->left->height + 1;
    return node;
}

avl_tree *avl_tree_create(char **arr, int n)
{
    return _avl_tree_create(arr, 0, n - 1);
}

int height(avl_tree *node)
{
    return node ? node->height : 0;
}

int bfactor(avl_tree *node)
{
    return height(node->right) - height(node->left);
}

void fix_height(avl_tree *node)
{
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl > hr ? hl : hr) + 1;
}

avl_tree *rotate_right(avl_tree *node)
{
    avl_tree *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    fix_height(node);
    fix_height(tmp);
    return tmp;
}

avl_tree *rotateleft(avl_tree *node)
{
    avl_tree *rmp = node->right;
    node->right = rmp->left;
    rmp->left = node;
    fix_height(node);
    fix_height(rmp);
    return rmp;
}

avl_tree *balance(avl_tree *node)
{
    fix_height(node);
    if (bfactor(node) == 2)
    {
        if (bfactor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotateleft(node);
    }
    if (bfactor(node) == -2)
    {
        if (bfactor(node->left) > 0)
            node->left = rotateleft(node->left);
        return rotate_right(node);
    }
    return node;
}


int avl_tree_insert_node(avl_tree **tree, avl_tree *node, int *n)
{
    if (!node)
        return DATA_ERROR;
    int rc = NO_ERRORS;
    if (!(*tree))
        *tree = node;
    else if (avl_tree_cmp(node, *tree) < 0)
    {
        (*n)++;
        rc = avl_tree_insert_node(&(*tree)->left, node, n);
    }
    else if (avl_tree_cmp(node, *tree) > 0)
    {
        (*n)++;
        rc = avl_tree_insert_node(&(*tree)->right, node, n);
    }
    else
        rc = ADD_EXISTED_ELEM_IN_TREE;
    *tree = balance(*tree);
    return rc;
}

int avl_tree_insert_node_char(avl_tree **tree, char *data, int *n)
{
    *n = 0;
    avl_tree *node = avl_tree_node_init(data);
    int rc = avl_tree_insert_node(tree, node, n);
    if (rc)
        avl_tree_node_free(node);
    return rc;
}

avl_tree *avl_tree_search(avl_tree *tree, avl_tree *node, int *n)
{
    if (!node || !tree)
        return NULL;
    avl_tree *res = NULL;
    if (avl_tree_cmp(node, tree) < 0)
    {
        (*n)++;
        res = avl_tree_search(tree->left, node, n);
    }
    else if (avl_tree_cmp(node, tree) > 0)
    {
        (*n)++;
        res = avl_tree_search(tree->right, node, n);
    }
    else
        res = tree;
    return res;
}

avl_tree *avl_tree_search_char(avl_tree *tree, char *data, int *n)
{
    *n = 0;
    avl_tree *node = avl_tree_node_init(data);
    avl_tree *res = avl_tree_search(tree, node, n);
    avl_tree_node_free(node);
    return res;
}

avl_tree *avl_tree_search_max(avl_tree *tree)
{
    if (!tree)
        return NULL;
    if (!tree->right)
        return tree;
    return avl_tree_search_max(tree->right);
}

void avl_assign(avl_tree *dst, avl_tree *src)
{
    if (strlen(dst->data) != strlen(src->data))
    {
        char *tmp = realloc(dst->data, (strlen(src->data) + 1) * sizeof(char));
        if (!tmp)
            return;
        dst->data = tmp;
    }
    strcpy(dst->data, src->data);
    dst->data[strlen(src->data)] = '\0';
}

avl_tree *avl_tree_remove(avl_tree *node, char *data)
{
    if (node == NULL)
        return NULL;
    if (strcmp(data, node->data) < 0)
        node->left = avl_tree_remove(node->left, data);
    else if (strcmp(data, node->data) > 0)
        node->right = avl_tree_remove(node->right, data);
    else if (node->left != NULL && node->right != NULL)
    {
        avl_assign(node, avl_tree_search_max(node->left));
        node->left = avl_tree_remove(node->left, node->data);
    }
    else
    {
        if (node->left != NULL)
        {
            avl_assign(node, node->left);
            avl_tree *tmp = node->left;
            node->right = node->left->right;
            node->left = node->left->left;
            avl_tree_node_free(tmp);
        }
        else if (node->right)
        {
            avl_assign(node, node->right);
            avl_tree *tmp = node->right;
            node->left = node->right->left;
            node->right = node->right->right;
            avl_tree_node_free(tmp);
        }
        else
        {
            avl_tree_node_free(node);
            node = NULL;
        }
    }
    if (node != NULL)
        node = balance(node);
    return node;
}

void avl_tree_nlr_detour(avl_tree *tree)
{
    if (!tree)
        return;
    avl_tree_node_print(tree);
    avl_tree_nlr_detour(tree->left);
    avl_tree_nlr_detour(tree->right);
}

void avl_tree_lnr_detour(avl_tree *tree)
{
    if (!tree)
        return;
    avl_tree_lnr_detour(tree->left);
    avl_tree_node_print(tree);
    avl_tree_lnr_detour(tree->right);
}

void avl_tree_lrn_detour(avl_tree *tree)
{
    if (!tree)
        return;
    avl_tree_lrn_detour(tree->left);
    avl_tree_lrn_detour(tree->right);
    avl_tree_node_print(tree);
}
