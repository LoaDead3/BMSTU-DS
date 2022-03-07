#include <stdio.h>
#include <time.h>

#include "../inc/err.h"
#include "../inc/tree.h"
#include "../inc/tree_io.h"
#include "../inc/hash_table.h"
#include "../inc/hash_table_io.h"
#include "../inc/fl.h"

#define DATA_SIZE 15

#define CMP_NUM 1000
#define CMP_TABLE_SIZE 500

int randint(double min, double max)
{
    return (int) ((max - min) * ((double) rand() / (double) RAND_MAX) + min);
}

void randword(char *word, double min, double max)
{
    int size = randint(min, max);
    for (int i = 0; i < size; i++)
        word[i] = (char) randint(97, 122);
    word[size - 1] = '\0';
}

void gen_data(char *file_name, int n, int min, int max)
{
    FILE *f = fopen(file_name, "w");
    for (int i = 0; i < n; i++)
    {
        char word[20] = "";
        randword(word, min, max);
        fprintf(f, "%s\n", word);
    }
    fclose(f);
}

size_t getFileSize(const char *file_name)
{
    size_t _file_size = 0;
    FILE *fd = fopen(file_name, "rb");
    if (fd == NULL)
    {
        _file_size = -1;
    }
    else
    {
        fseek(fd, 0, SEEK_END);
        _file_size = ftell(fd);
        fclose(fd);
    }
    return _file_size;
}

void title()
{
    printf("The program displays DDP, AVL tree and hash table. Allows you\n"
           "to add and search for fields in these data structures, comparing performance.\n");
}

void mes(int num)
{
    char arr[CMP_NUM][20];
    for (int i = 0; i < CMP_NUM; i++)
    {
        char tmp[20] = "";
        randword(tmp, 2, 15);
        strcpy(arr[i], tmp);
    }
    double it1 = 0, it2 = 0, it3 = 0, it4 = 0;
    double in1 = 0, in2 = 0, in3 = 0, in4 = 0;
    bs_tree *bs = NULL;
    avl_tree *avl = NULL;
    hash_table table = {NULL, 0};

    clock_t begin = clock();
    for (int i = 0; i < CMP_NUM; i++)
    {
        int tmp = 0;
        bs_tree_insert_node_char(&bs, arr[i], &tmp);
        in1 += tmp;
    }
    clock_t end = clock();
    it1 = ((double) (end - begin));
    it1 /= CMP_NUM;
    in1 /= CMP_NUM;

    begin = clock();
    for (int i = 0; i < CMP_NUM; i++)
    {
        int tmp = 0;
        avl_tree_insert_node_char(&avl, arr[i], &tmp);
        in2 += tmp;
    }
    end = clock();
    it2 = ((double) (end - begin));
    it2 /= CMP_NUM;
    in2 /= CMP_NUM;

    begin = clock();
    hash_table_init(&table, CMP_TABLE_SIZE);
    for (int i = 0; i < CMP_NUM; i++)
    {
        int tmp = 0;
        hash_table_insert_char(&table, arr[i], &tmp);
        in3 += tmp;
    }
    end = clock();
    it3 = ((double) (end - begin));
    it3 /= CMP_NUM;
    in3 /= CMP_NUM;

    char ff[] = "ff.txt";
    FILE *f = fopen(ff, "w");
    fclose(f);
    begin = clock();
    for (int i = 0; i < CMP_NUM; i++)
    {
        file_write(ff, arr[i]);
    }
    end = clock();
    it4 = ((double) (end - begin));
    it4 /= CMP_NUM;
    in4 = 1;

    double n1 = 0, n2 = 0, n3 = 0, n4 = 0;
    double st1 = 0, st2 = 0, st3 = 0, st4 = 0;

    begin = clock();
    for (int i = 0; i < CMP_NUM; i++)
    {
        int tmp = 0;
        bs_tree_search_char(bs, arr[i], &tmp);
        n1 += tmp;
    }
    end = clock();
    st1 = ((double) (end - begin));
    st1 /= CMP_NUM;
    n1 /= CMP_NUM;

    begin = clock();
    for (int i = 0; i < CMP_NUM; i++)
    {
        int tmp = 0;
        avl_tree_search_char(avl, arr[i], &tmp);
        n2 += tmp;
    }
    end = clock();
    st2 = ((double) (end - begin));
    st2 /= CMP_NUM;
    n2 /= CMP_NUM;

    begin = clock();
    for (int i = 0; i < CMP_NUM; i++)
    {
        int tmp = 0;
        hash_table_search_char(&table, arr[i], &tmp);
        n3 += tmp;
    }
    end = clock();
    st3 = ((double) (end - begin));
    st3 /= CMP_NUM;
    n3 /= CMP_NUM;

    begin = clock();
    for (int i = 0; i < CMP_NUM; i++)
    {
        int tmp = 0;
        file_search(ff, arr[i], &tmp);
        n4 += tmp;
    }
    end = clock();
    st4 = ((double) (end - begin));
    st4 /= CMP_NUM;
    n4 /= CMP_NUM;

    size_t arr_size = 0;
    for (int i = 0; i < CMP_NUM; i++)
        arr_size += strlen(arr[i]) * sizeof(char);

    size_t m1 = sizeof(bs_tree) * CMP_NUM + sizeof(bs_tree *) + arr_size;
    size_t m2 = sizeof(avl_tree) * CMP_NUM + sizeof(avl_tree *) + arr_size;
    size_t m3 = sizeof(table) + sizeof(sl_list *) * table.size + sizeof(sl_list) * CMP_NUM + arr_size;
    size_t m4 = getFileSize(ff);

    bs_tree_export_to_dot("bs.gv", "bs", bs);
    avl_tree_export_to_dot("avl.gv", "avl", avl);
//    hash_table_print(&table);

    printf("Insert (time|cmp):\nbs: %lf | %lf\navl: %lf | %lf\ntable: %lf | %lf\nfile : %lf | %lf\n", it1, in1, it2,
           in2, it3, in3, it4, in4);
    printf("Search (time|cmp):\nbs: %lf | %lf\navl: %lf | %lf\ntable: %lf | %lf\nfile: %lf | %lf\n", st1, n1, st2, n2,
           st3, n3,
           st4, n4);
    printf("MEM:\nbs: %lu\navl: %lu\ntable: %lu\nfile: %lu\n", m1, m2, m3, m4);
    bs_tree_free(bs);
    avl_tree_free(avl);
    hash_table_free(&table);
}

int bs_menu(char *filename)
{
    int rc = NO_ERRORS;
    bs_tree *bs = NULL;

    rc += bs_tree_input(&bs, filename);
    if (rc)
    {
        return err_handl(rc);
    }

    int c = 1;
    while (c != 0)
    {
        printf("\nChoice menu item:\n1 - Print bs-tree\n2 - Insert element\n3 - Del element\n4 - Search element\n5 - nlr detour\n"
               "6 - lnr detour\n7 - lrn detour\n0 - Exit\nChoice:");
        if ((scanf("%d", &c)) != 1)
        {
            printf("Wrong choice\n");
            char trash[20];
            scanf("%s", trash);
            continue;
        }
        switch (c)
        {
            case 1:
            {
                if (!bs)
                    printf("Empty tree\n");
                else
                    bs_tree_export_to_dot("bs.gv", "bs", bs);
                break;
            }
            case 2:
            {
                char buf[128] = "";
                printf("Input string:");
                scanf("%s", buf);
                int m = 0;
                rc = bs_tree_insert_node_char(&bs, buf, &m);
                if (rc)
                    err_handl(rc);
                rc = 0;
                break;
            }
            case 3:
            {
                if (!bs)
                    printf("Empty tree");
                else
                {
                    char buf[128] = "";
                    printf("Input string:");
                    scanf("%s", buf);
                    bs = bs_tree_remove(bs, buf);
                }
                break;
            }
            case 4:
            {
                if (!bs)
                    printf("Empty tree");
                else
                {
                    char buf[128] = "";
                    printf("Input string:");
                    scanf("%s", buf);
                    int n = 0;
                    bs_tree *res2 = bs_tree_search_char(bs, buf, &n);
                    if (!res2)
                        printf("Not found\n");
                    else
                        printf("%s | %d\n", res2->data, n);
                }
                break;
            }
            case 5:
            {
                bs_tree_nlr_detour(bs);
                break;
            }
            case 6:
            {
                bs_tree_lnr_detour(bs);
                break;
            }
            case 7:
            {
                bs_tree_lrn_detour(bs);
                break;
            }
            case 0:
                break;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
    bs_tree_free(bs);
    return rc;
}

int avl_menu(char *filename)
{
    int rc = NO_ERRORS;
    avl_tree *avl = NULL;

    rc += avl_tree_input(&avl, filename);
    if (rc)
    {
        return err_handl(rc);
    }

    int c = 1;
    while (c != 0)
    {
        printf("\nChoice menu item:\n1 - Print avl-tree\n2 - Insert element\n3 - Del element\n4 - Search element\n5 - nlr detour\n"
               "6 - lnr detour\n7 - lrn detour\n0 - Exit\nChoice:");
        if ((scanf("%d", &c)) != 1)
        {
            printf("Wrong choice\n");
            char trash[20];
            scanf("%s", trash);
            continue;
        }
        switch (c)
        {
            case 1:
            {
                if (!avl)
                    printf("Empty tree\n");
                else
                    avl_tree_export_to_dot("avl.gv", "avl", avl);
                break;
            }
            case 2:
            {
                char buf[128] = "";
                printf("Input string:");
                scanf("%s", buf);
                int m = 0;
                rc = avl_tree_insert_node_char(&avl, buf, &m);
                if (rc)
                    err_handl(rc);
                rc = 0;
                break;
            }
            case 3:
            {
                if (!avl)
                    printf("Empty tree");
                else
                {
                    char buf[128] = "";
                    printf("Input string:");
                    scanf("%s", buf);
                    avl = avl_tree_remove(avl, buf);
                }
                break;
            }
            case 4:
            {
                if (!avl)
                    printf("Empty tree");
                else
                {
                    char buf[128] = "";
                    printf("Input string:");
                    scanf("%s", buf);
                    int n = 0;
                    avl_tree *res2 = avl_tree_search_char(avl, buf, &n);
                    if (!res2)
                        printf("Not found\n");
                    else
                        printf("%s | %d\n", res2->data, n);
                }
                break;
            }
            case 5:
            {
                avl_tree_nlr_detour(avl);
                break;
            }
            case 6:
            {
                avl_tree_lnr_detour(avl);
                break;
            }
            case 7:
            {
                avl_tree_lrn_detour(avl);
                break;
            }
            case 0:
                break;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
    avl_tree_free(avl);
    return rc;
}

int hash_menu(char *filename)
{
    int rc = NO_ERRORS;
    int n = 0;
    hash_table table = {NULL, 0};
    printf("Input hash-table size:");
    while (1)
    {
        if ((scanf("%d", &n)) != 1 || n < 1)
        {
            printf("Wrong size\n");
            char trash[20];
            scanf("%s", trash);
            continue;
        }
        break;
    }
    hash_table_init(&table, n);
    rc = hash_table_input(&table, filename);
    if (rc)
    {
        return err_handl(rc);
    }
    table.oper_num = 0;
    table.cmp_sum = 0;
    int c = 1;
    while (c != 0)
    {
        printf("\nChoice menu item:\n1 - Print hash-table\n2 - Insert element\n3 - Del element\n4 - Search element\n5 - restructure\n0 - Exit\nChoice:");
        if ((scanf("%d", &c)) != 1)
        {
            printf("Wrong choice\n");
            char trash[20];
            scanf("%s", trash);
            continue;
        }
        switch (c)
        {
            case 1:
            {
                if (is_empty(&table))
                    printf("Empty table");
                else
                    hash_table_print(&table);
                break;
            }
            case 2:
            {
                char buf[128] = "";
                printf("Input string:");
                scanf("%s", buf);
                int cmp = 0;
                while (1)
                {
                    printf("Input max cmp:");
                    if ((scanf("%d", &cmp)) != 1)
                    {
                        printf("Wrong size\n");
                        char trash[20];
                        scanf("%s", trash);
                        continue;
                    }
                    if (n < 1)
                    {
                        printf("Wrong size\n");
                        continue;
                    }
                    break;
                }
                int cmp_n = 0;
                rc = hash_table_insert_char(&table, buf, &cmp_n);
                if (rc)
                    err_handl(rc);
                else
                {
                    double sr = (double) table.cmp_sum / (double) table.oper_num;
                    printf(" cmp num: %lf\n", sr);
                    if (sr > (double) cmp && table.oper_num > 0)
                    {
                        hash_table tmp = {NULL, 0, 0, 0};
                        rc = restruct(&tmp, &table);
                        if (rc)
                        {
                            err_handl(rc);
                            rc = 0;
                        }
                        else
                        {
                            hash_table_free(&table);
                            table.table = tmp.table;
                            table.size = tmp.size;
                        }
                    }
                }
                rc = 0;
                break;
            }
            case 3:
            {
                if (is_empty(&table))
                    printf("Empty table");
                else
                {
                    char buf[128] = "";
                    printf("Input string:");
                    scanf("%s", buf);

                    sl_list *node = hash_table_remove_char(&table, buf);
                    if (!node)
                        printf("Not such element\n");
                    else
                    {
                        printf("%s\n", node->data);
                        free(node->data);
                        free(node);
//                        double sr = (double) table.cmp_sum / (double) table.oper_num;
//                        printf(" cmp num: %lf\n", sr);
//                        if (sr > (double) cmp && table.oper_num > 0)
//                        {
//                            hash_table tmp = {NULL, 0, 0, 0 };
//                            rc = restruct(&tmp, &table);
//                            if (rc)
//                            {
//                                err_handl(rc);
//                                rc = 0;
//                            }
//                            else
//                            {
//                                hash_table_free(&table);
//                                table.table = tmp.table;
//                                table.size = tmp.size;
//                            }
//                        }
                    }
                }
                break;
            }
            case 4:
            {
                if (is_empty(&table))
                    printf("Empty table");
                else
                {
                    char buf[128] = "";
                    printf("Input string:");
                    scanf("%s", buf);
                    int cmp = 0;
                    while (1)
                    {
                        printf("Input max cmp:");
                        if ((scanf("%d", &cmp)) != 1)
                        {
                            printf("Wrong size\n");
                            char trash[20];
                            scanf("%s", trash);
                            continue;
                        }
                        if (n < 1)
                        {
                            printf("Wrong size\n");
                            continue;
                        }
                        break;
                    }
                    int n1 = 0;
                    sl_list *node = hash_table_search_char(&table, buf, &n1);
                    if (!node)
                        printf("Not found\n");
                    else
                    {
                        printf("%s | %d\n", node->data, n1);
                        double sr = (double) table.cmp_sum / (double) table.oper_num;
                        printf(" cmp num: %lf\n", sr);
                        if (sr > (double) cmp && table.oper_num > 0)
                        {
                            hash_table tmp = {NULL, 0, 0, 0};
                            rc = restruct(&tmp, &table);
                            if (rc)
                            {
                                err_handl(rc);
                                rc = 0;
                            }
                            else
                            {
                                hash_table_free(&table);
                                table.table = tmp.table;
                                table.size = tmp.size;
                            }
                        }
                    }
                }
                break;
            }
            case 5:
            {
                hash_table tmp = {NULL, 0};
                rc = restruct(&tmp, &table);
                if (rc)
                {
                    err_handl(rc);
                    rc = 0;
                }
                else
                {
                    hash_table_free(&table);
                    table.table = tmp.table;
                    table.size = tmp.size;
                }
                break;
            }
            case 0:
                break;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
    hash_table_free(&table);
    return rc;
}


int main(int argc, char *argv[])
{
    int rc = NO_ERRORS;
    setbuf(stdout, NULL);

    if (argc == 1)
    {
        gen_data("d.txt", DATA_SIZE, 1, 15);
        return 0;
    }
    if (argc > 2)
        return err_handl(ARG_ERROR);

    hash_table table = {NULL, 0, 0, 0};
    bs_tree *bs = NULL;
    avl_tree *avl = NULL;

    title();
    int n = 0;
    while (1)
    {
        printf("Input hash-table size:");
        if ((scanf("%d", &n)) != 1)
        {
            printf("Wrong size\n");
            char trash[20];
            scanf("%s", trash);
            continue;
        }
        if (n < 1)
        {
            printf("Wrong size\n");
            continue;
        }
        break;
    }
    hash_table_init(&table, n);
    rc = hash_table_input(&table, argv[1]);
    if (rc)
    {
        return err_handl(rc);
    }
    table.oper_num = 0;
    table.cmp_sum = 0;
    rc += bs_tree_input(&bs, argv[1]);
    if (rc)
    {
        hash_table_free(&table);
        return err_handl(rc);
    }
    rc += avl_tree_input(&avl, argv[1]);
    if (rc)
    {
        hash_table_free(&table);
        bs_tree_free(bs);
        return err_handl(rc);
    }
    int c = 1;
    while (c != 0)
    {
        printf("\nChoice menu item:\n1 - Print BS-tree\n2 - Print AVL-tree\n3 - Print hash-table\n4 - Add element\n"
               "5 - Search element\n6 - Performance measurement\n7 - Work with bs-tree\n8 - Work with avl-tree\n9 - Work with hash-table\n0 - Exit\nChoice:");
        if ((scanf("%d", &c)) != 1)
        {
            printf("Wrong choice\n");
            char trash[20];
            scanf("%s", trash);
            continue;
        }
        switch (c)
        {
            case 1:
            {
                if (!bs)
                    printf("Empty tree\n");
                else
                    bs_tree_export_to_dot("bs.gv", "bs", bs);
                break;
            }
            case 2:
                if (!bs)
                    printf("Empty tree\n");
                else
                    avl_tree_export_to_dot("avl.gv", "avl", avl);
                break;
            case 3:
                hash_table_print(&table);
                break;
            case 4:
            {
                char buf[128] = "";
                printf("Input string:");
                scanf("%s", buf);
                int cmp = 0;
                while (1)
                {
                    printf("Input max cmp:");
                    if ((scanf("%d", &cmp)) != 1)
                    {
                        printf("Wrong size\n");
                        char trash[20];
                        scanf("%s", trash);
                        continue;
                    }
                    if (n < 1)
                    {
                        printf("Wrong size\n");
                        continue;
                    }
                    break;
                }
                int cmp_n1 = 0, cmp_n2 = 0, cmp_n3 = 0;
                rc = bs_tree_insert_node_char(&bs, buf, &cmp_n1);
                if (rc)
                {
                    printf("bs:");
                    err_handl(rc);
                }
                else
                    printf("DS tree cmp num: %d\n", cmp_n1);
                rc = avl_tree_insert_node_char(&avl, buf, &cmp_n2);
                if (rc)
                {
                    printf("avl:");
                    err_handl(rc);
                }
                else
                    printf("AVL tree cmp num: %d\n", cmp_n2);
                rc = hash_table_insert_char(&table, buf, &cmp_n3);
                if (rc)
                {
                    printf(":");
                    err_handl(rc);
                }
                else
                {
                    printf("hash cmp num: %d\n", cmp_n3);
                    double sr = (double) table.cmp_sum / (double) table.oper_num;
                    printf("Average cmp num: %lf\n", sr);
                    if (sr > (double) cmp && table.oper_num > 0)
                    {
                        hash_table tmp = {NULL, 0, 0, 0};
                        rc = restruct(&tmp, &table);
                        if (rc)
                        {
                            err_handl(rc);
                            rc = 0;
                        }
                        else
                        {
                            hash_table_free(&table);
                            table.table = tmp.table;
                            table.size = tmp.size;
                        }
                    }
                }
                rc = 0;
                break;
            }
            case 5:
            {
                char buf[128] = "";
                printf("Input string:");
                scanf("%s", buf);
                int cmp = 0;
                while (1)
                {
                    printf("Input max cmp:");
                    if ((scanf("%d", &cmp)) != 1)
                    {
                        printf("Wrong size\n");
                        char trash[20];
                        scanf("%s", trash);
                        continue;
                    }
                    if (n < 1)
                    {
                        printf("Wrong size\n");
                        continue;
                    }
                    break;
                }
                int n1 = 0, n2 = 0, n3 = 0;
                bs_tree *res1 = bs_tree_search_char(bs, buf, &n1);
                printf("BS: ");
                if (!res1)
                    printf("Not found\n");
                else
                    printf("%s | %d\n", res1->data, n1);

                avl_tree *res2 = avl_tree_search_char(avl, buf, &n2);
                printf("AVL: ");
                if (!res2)
                    printf("Not found\n");
                else
                    printf("%s | %d\n", res2->data, n2);
                sl_list *res3 = hash_table_search_char(&table, buf, &n3);
                printf("Hash-table:");
                if (!res3)
                    printf("Not found\n");
                else
                    printf("%s | %d\n", res3->data, n3);
                double sr = (double) table.cmp_sum / (double) table.oper_num;
                printf("Average cmp num: %lf\n", sr);
                if (sr > (double) cmp && table.oper_num > 0)
                {
                    hash_table tmp = {NULL, 0, 0, 0};
                    rc = restruct(&tmp, &table);
                    if (rc)
                    {
                        err_handl(rc);
                        rc = 0;
                    }
                    else
                    {
                        hash_table_free(&table);
                        table.table = tmp.table;
                        table.size = tmp.size;
                    }
                }
                break;
            }
            case 6:
            {
                mes(1);
                break;
            }
            case 7:
            {
                bs_menu(argv[1]);
                break;
            }
            case 8:
            {
                avl_menu(argv[1]);
                break;
            }
            case 9:
            {
                hash_menu(argv[1]);
                break;
            }
            case 10:
            {
                hash_table tmp = {NULL, 0, 0, 0};
                rc = restruct(&tmp, &table);
                if (rc)
                {
                    err_handl(rc);
                    rc = 0;
                }
                else
                {
                    hash_table_free(&table);
                    table.table = tmp.table;
                    table.size = tmp.size;
                }
                break;
            }
            case 0:
                break;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
    bs_tree_free(bs);
    avl_tree_free(avl);
    hash_table_free(&table);
    return rc;
}