#include <locale.h>

#include "stdio.h"
#include "LArif.h"
#include "io.h"

void error_message(int n)
{
    if (n == 0)
        return;
    else if (n == INP_ERROR)
    { printf("Input error"); }
    else if (n == OVERF_ERROR)
        printf("Ошибка переполнения");
    else if (n == EMPTY_INP_ERROR)
        printf("Пустая строка на входе");
}

int main()
{
    setlocale(0, "");;
    printf("Программа умножает два вещественных числа, введённых пользователем,\n"
           " и вывод результат на экран. Число может вводиться как целое,\n"
           " дробное(через точку), или в экспоненциальной форме. Мантисса\n"
           " длинной не более 30 символов и порядок длинной не более 5 символов.\n"
           "Число выводится в нормированном экспоненциальном виде (+-0.(число)E+-(порядок).\n");
    struct l_arif a, b;
    int rc;
    rc = input(&a);
    if (rc)
    {
        error_message(rc);
        return rc;
    }
    rc = input(&b);
    if (rc)
    {
        error_message(rc);
        return rc;
    }
    struct l_arif c = sub(&a, &b);
    print(c);
    return 0;
}
