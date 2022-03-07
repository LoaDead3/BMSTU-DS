#include "Io.h"

int mantissa_inp(struct l_arif *n, char **s)
{
    n->mantissa_sign = 1;
    if (**s == '+')
        (*s)++;
    else if (**s == '-')
    {
        n->mantissa_sign = 0;
        (*s)++;
    }
    int tmp_exp = 0, i = MANTISSA_LEN - 1;
    while (isdigit(**s) && i >= 0)
        n->mantissa[i--] = *(*s)++ - '0';
    if (**s == '.')
    {
        (*s)++;
        while (isdigit(**s) && i >= 0)
        {
            n->mantissa[i--] = *(*s)++ - '0';
            tmp_exp++;
        }
    }
    if (isdigit(**s))
        return OVERF_ERROR;
    n->mantissa_len = MANTISSA_LEN - i - 1;
    n->exp -= tmp_exp;
    if (i > 0)
    {
        i++;
        int null_counter = 0;
        for (int j = i; j < MANTISSA_LEN - 1; j++)
        {
            if (n->mantissa[i] != 0)
                break;
            null_counter++;
        }
        n->mantissa_len -= null_counter;
        n->exp += null_counter;
        for (int j = 0; j < n->mantissa_len; j++)
        {
            n->mantissa[j] = n->mantissa[j + i + null_counter];
            n->mantissa[j + i + null_counter] = 0;
        }
    }
    return 0;
}


int exp_input(struct l_arif *n, char **s)
{
    if (**s == 'e' || **s == 'E')
        (*s)++;
    else
        return 0;
    int tmp_sign = 1;
    if (**s == '-')
    {
        tmp_sign = -1;
        (*s)++;
    }
    char *cpy_s = *s;
    int l = 0;
    while (isdigit(*cpy_s++))
        l++;
    if (n->mantissa_len == 0)
    {
        if (l == 0)
            return INP_ERROR;
        n->mantissa[0] = 1;
        n->mantissa_len++;
    }
    if (l > EXP_LEN)
        return OVERF_ERROR;
    if (l == 0)
        return INP_ERROR;
    for (--l; l >= 0; l--)
    {
        n->exp += (*(*s)++ - '0') * pow(10, l) * tmp_sign;
    }
    return 0;
}


int input(struct l_arif *n)
{
    printf("                                            30\n");
    printf("              ______________________________|\n");
    printf("Введите число:");
    memset(n, 0, sizeof *n);
    char inp[MAX_STR_LEN + 2];
    int rc = scanf("%s", inp);
    if (rc != 1)
        return INP_ERROR;
    if (strlen(inp) > MAX_STR_LEN)
        return INP_ERROR;
    if (strlen(inp) < 1)
        return EMPTY_INP_ERROR;
    char *s = inp;
    while (isspace(*s))
        s++;
    rc = mantissa_inp(n, &s);
    if (rc)
        return rc;
    rc = exp_input(n, &s);
    if (rc)
        return rc;
    while (*s)
        if (!isspace(*s))
            return INP_ERROR;
    return 0;
}


void print(struct l_arif n)
{
    if (n.exp > 99999 || n.exp < -99999)
        printf("Order was overflowed while substracting\n");
    if (n.mantissa_sign == 0)
        printf("-");
    n.exp += n.mantissa_len;
    printf("0.");
    if (n.mantissa_len == 0)
        printf("0");
    for (int i = n.mantissa_len - 1; i >= 0; i--)
        printf("%d", n.mantissa[i]);
    printf("e%d\n", n.exp);
}
