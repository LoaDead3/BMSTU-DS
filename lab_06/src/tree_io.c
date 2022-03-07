#include "../inc/tree_io.h"

void bs_tree_node_print(bs_tree *node)
{
    printf("%s\n", node->data);
}

void bs_tree_apply_pre(bs_tree *tree, void (*f)(bs_tree *, void *), void *arg)
{
    if (!tree)
        return;
    f(tree, arg);
    bs_tree_apply_pre(tree->left, f, arg);
    bs_tree_apply_pre(tree->right, f, arg);
}

void bs_tree_to_dot(bs_tree *tree, void *f)
{
    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->data, tree->left->data);
    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->data, tree->right->data);
}

int bs_tree_export_to_dot(char *fl, char *tree_name, bs_tree *tree)
{
    FILE *f = fopen(fl, "w");
    if (!f)
        return FILE_ERROR;
    fprintf(f, "digraph %s {\n", tree_name);
    bs_tree_apply_pre(tree, bs_tree_to_dot, f);
    fprintf(f, "}\n");
    fclose(f);
    char comand[80];
    sprintf(comand, "dot -Tsvg %s > svg/bs_tree.svg", fl);
    system(comand);
    return NO_ERRORS;
}

int bs_tree_input(bs_tree **tree, char *filename)
{
    *tree = NULL;
    FILE *f = fopen(filename, "r");
    if(!f)
        return FILE_ERROR;
    char cur[20];
    int n = 0;
    while (fscanf(f, "%s", cur) != EOF)
    {
        n++;
        int tmp = 0;
        bs_tree_insert_node_char(tree, cur, &tmp);
    }
    fclose(f);
    if(n == 0)
        return EMPTY_FILE;
    return NO_ERRORS;
}

void free_tmp_arr(char **arr, int n)
{
    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}

void sort(char **arr, int n)
{
    for(int i = 0 ; i < n - 1; i++) {
        for(int j = 0 ; j < n - i - 1 ; j++) {
            if(strcmp(arr[j], arr[j + 1]) > 0) {
                char * tmp = arr[j];
                arr[j] = arr[j+1] ;
                arr[j+1] = tmp;
            }
        }
    }
}

int avl_tree_input(avl_tree **tree, char *filename)
{
    *tree = NULL;
    FILE *f = fopen(filename, "r");
    if(!f)
        return FILE_ERROR;
    char cur[124];
    int mem_size = 10, i = 0, n = 0;
    char **arr = calloc(mem_size, sizeof(char*));
    while (fscanf(f, "%s", cur) != EOF)
    {
        n++;
        arr[i] = calloc(strlen(cur) + 1, sizeof(char));
        strcpy(arr[i], cur);
        i++;
        if(i == mem_size)
        {
            mem_size *= 2;
            char **tmp = realloc(arr, sizeof(char*) * mem_size);
            if(!tmp)
            {
                free_tmp_arr(arr, i);
                return MEM_ERROR;
            }
            arr = tmp;
        }
    }
    if(n == 0)
    {
        fclose(f);
        free_tmp_arr(arr, i);
        return EMPTY_FILE;
    }
    mem_size = i;
    char **tmp = realloc(arr, sizeof(char*) * mem_size);
    if(!tmp)
    {
        free_tmp_arr(arr, i);
        return MEM_ERROR;
    }
    arr = tmp;
    sort(arr, i);
    *tree = avl_tree_create(arr, i);
    free_tmp_arr(arr, i);
    fclose(f);
    return NO_ERRORS;
}

void avl_tree_node_print(avl_tree *node)
{
    printf("%s\n", node->data);
}

void avl_tree_apply_pre(avl_tree *tree, void (*f)(avl_tree *, void *), void *arg)
{
    if (!tree)
        return;
    f(tree, arg);
    avl_tree_apply_pre(tree->left, f, arg);
    avl_tree_apply_pre(tree->right, f, arg);
}

void avl_tree_to_dot(avl_tree *tree, void *f)
{
    if (tree->left)
        fprintf(f, "%s -> %s;\n", tree->data, tree->left->data);
    if (tree->right)
        fprintf(f, "%s -> %s;\n", tree->data, tree->right->data);
}

int avl_tree_export_to_dot(char *fl, char *tree_name, avl_tree *tree)
{
    FILE *f = fopen(fl, "w");
    if (!f)
        return FILE_ERROR;
    fprintf(f, "digraph %s {\n", tree_name);
    avl_tree_apply_pre(tree, avl_tree_to_dot, f);
    fprintf(f, "}\n");
    fclose(f);
    char comand[80];
    sprintf(comand, "dot -Tsvg %s > svg/avl_tree.svg", fl);
    system(comand);
    return NO_ERRORS;
}