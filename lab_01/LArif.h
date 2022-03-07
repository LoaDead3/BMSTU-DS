#ifndef LARIF_H
#define LARIF_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MANTISSA_LEN 30
#define MAX_STR_LEN 39
#define EXP_LEN 5

#define INP_ERROR 1
#define OVERF_ERROR 2
#define EMPTY_INP_ERROR 3


struct l_arif
{
    int mantissa_sign;
    int mantissa[MANTISSA_LEN];
    int mantissa_len;
    int exp;
};

struct l_arif sub(struct l_arif *, struct l_arif *);

#endif
