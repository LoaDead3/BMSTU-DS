#include <stdio.h>

#include "../inc/graph_io.h"
#include "../inc/graph.h"

int main(int argc, char *argv[])
{
    printf("The program allows you to check whether it is possible,\n"
           "by removing a vertex from the graph, to make it a tree and\n"
           "display the result on the screen in graphical form\n\n");
    if (argc != 2)
        return err_handl(ARG_ERROR);
    graph gr;
    int rc = graph_input(&gr, argv[1]);
    if (rc)
        return err_handl(rc);
    int res = 0;
    graph_is_tree(&gr, &res);
    if (res == 1)
    {
        printf("The graph is already a tree\n");
        graph_free(&gr);
        return NO_ERRORS;
    }
    int c = 1;
    while (c != 0)
    {
        printf("\nChoice menu item:\n1 - Print graph\n"
               "2 - Checking whether a tree can be obtained by removing the vertex\n0 - Exit\nChoice:");
        if ((scanf("%d", &c)) != 1)
        {
            printf("Wrong choice\n");
            char trash[20] = "";
            scanf("%s", trash);
            continue;
        }
        switch (c)
        {
            case 1:
            {
                rc = graph_print(&gr, "graph");
                break;
            }
            case 2:
            {
                rc = show_tree_in_graph(&gr);
                break;
            }
            case 0:
                break;
            default:
                printf("Wrong choice\n");
                break;
        }
        if (rc)
        {
            graph_free(&gr);
            return err_handl(rc);
        }
    }
    graph_free(&gr);
    return 0;
}
