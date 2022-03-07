#include "LArif.h"

void rounding(struct l_arif *n)
{
    int carry = 0;
    if (n->mantissa[0] >= 5)
    {
        n->mantissa[1]++;
        n->mantissa[1] %= 10;
    }
    for (int i = 0; i < MANTISSA_LEN - 1; i++)
    {
        n->mantissa[i] = carry + n->mantissa[i + 1];
        carry = n->mantissa[i] / 10;
        n->mantissa[i] %= 10;
    }
    n->mantissa[MANTISSA_LEN - 1] = 0;
    n->mantissa_len--;
    n->exp++;
}

void del_nulls(struct l_arif *n)
{
    while (n->mantissa[n->mantissa_len - 1] == 0)
        n->mantissa_len--;
}

struct l_arif sub(struct l_arif *l, struct l_arif *r) //TODO exp over check
{
    struct l_arif res;
    memset(&res, 0, sizeof res);
    if (l->mantissa_sign && r->mantissa_sign || !l->mantissa_sign && !r->mantissa_sign)
        res.mantissa_sign = 1;
    res.exp = l->exp + r->exp;
    int rnd = 0;
    for (int i = 0; i < l->mantissa_len; i++)
    {
        int carry = 0, counter, j;
        for (j = 0; j < r->mantissa_len; j++)
        {
            if (i + j > MANTISSA_LEN - 1 + rnd)
            {
                rnd++;
                rounding(&res);
            }
            counter = i + j - rnd;
            res.mantissa[counter] += carry + l->mantissa[i] * r->mantissa[j];
            carry = res.mantissa[counter] / 10;
            res.mantissa[counter] %= 10;
        }
        if (carry != 0)
        {
            if (i + j > MANTISSA_LEN - 1 + rnd)
            {
                rnd++;
                rounding(&res);
            }
            counter = i + j - rnd;
            res.mantissa[counter] = carry;
        }
        res.mantissa_len = i + j - rnd + 1;
    }
    del_nulls(&res);
    return res;
}




