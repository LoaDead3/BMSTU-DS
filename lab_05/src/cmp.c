#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../inc/queues.h"
#include "../inc/sl_list.h"

#define BUFF_SIZE 4
#define ITER 1000
#define N 10000

void print_list(queue_list *list)
{
    sl_list *cur = list->begin;
    for (; cur; cur = cur->next)
    {
        printf("%d ", cur->data);
    }
    printf("\n");
}

void print_arr(queue_arr *arr)
{
    for (int i = 0; i < ARR_SIZE; i++)
        printf("%d ", arr->arr[i]);
    printf("\n");
}

int measure()
{
    int rc = 0;
    double t1 = 0, t2 = 0;
    size_t m1 = 0, m2 = 0;
    queue_arr queueArr;
    queue_list queueList;
    int tmp = 0;


    clock_t begin = clock();
    for (int i = 0; i < ITER; i++)
    {
        queueArr.pin = 0;
        queueArr.pout = 0;
        queueArr.is_not_empty = 0;
        for (int j = 0; j < N; j++)
        {
            rc = queue_arr_push(&queueArr, j);
            if (rc)
                return rc;
        }
//        print_arr(&queueArr);
        for (int j = 0; j < N; j++)
        {
            rc = queue_arr_pop(&queueArr, &tmp);
            if (rc)
                return rc;
        }
    }
    clock_t end = clock();
    t1 = ((double) (end - begin));
    t1 /= ITER;
    //    t1 /= CLOCKS_PER_SEC;
    m1 = sizeof(int) * (ARR_SIZE + 3);


    clock_t begin1 = clock();
    for (int i = 0; i < ITER; i++)
    {
        queueList.begin = NULL;
        queueList.end = NULL;
        for (int j = 0; j < N; j++)
        {
            rc = queue_list_push(&queueList, j);
            if (rc)
                return rc;
        }
//        print_list(&queueList);
        for (int j = 0; j < N; j++)
        {
            rc = queue_list_pop(&queueList, &tmp, NULL);
            if (rc)
                return rc;
        }
    }
    clock_t end1 = clock();
//    printf("%ld %ld\n", begin, end);
//    printf("%ld %ld\n", begin1, end1);
    t2 = ((double) (end1 - begin1));
    t2 /= ITER;
    //    t2 /= CLOCKS_PER_SEC;
    m2 += sizeof(sl_list) * (N + 1);


//    printf("Arr: %Iu\nList: %Iu\n", sizeof(int), sizeof(sl_list));
    printf("Arr: %lf %lu\nList: %lf %lu\n", t1, m1, t2, m2);
    return rc;
}

int main()
{

    return measure();
}