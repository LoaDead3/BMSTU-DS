#include <stdio.h>
#include <time.h>

#include "../head/calc.h"
#include "../head/stack.h"


#define N 8000
#define ITER 100

int main()
{
    double t1 = 0, t2 = 0;
    size_t m1 = 0, m2 = 0;
    stack_arr stackArr;
    stack_list stackList;
    memset(&stackArr, 0, sizeof(stackArr));
    memset(&stackList, 0, sizeof(stackList));
    char buf[VAL_LEN];
    char tok[] = "jgcahdbnaskdua";
    clock_t begin = clock();
    for (int i = 0; i < ITER; i++)
    {
        for (int j = 0; j < N; j++)
            arr_push(&stackArr, tok);
        for (int j = 0; j < N; j++)
            arr_pop(&stackArr, buf);
    }
    clock_t end = clock();
    t1 = ((double) (end - begin));
    t1 /= ITER;
    t1 /= CLOCKS_PER_SEC;
    m1 = sizeof(char) * (VAL_LEN + 1) * ARR_LEN + sizeof(int);

    clock_t begin1 = clock();
    for (int i = 0; i < ITER; i++)
    {
        for (int j = 0; j < N; j++)
            list_push(&stackList, tok);
        for (int j = 0; j < N; j++)
            list_pop(&stackList, buf, NULL);
    }
    clock_t end1 = clock();
    t2 = ((double) (end1 - begin1));
    t2 /= ITER;
    t2 /= CLOCKS_PER_SEC;
    m2 += sizeof(sl_list_token) * N + sizeof(sl_list_token *);

    printf("%Iu %Iu\n", sizeof(sl_list_token), sizeof(char) * (VAL_LEN + 1));
    printf("Arr: %lf %Iu\nList: %lf %Iu\n", t1, m1, t2, m2);
    return 0;
}