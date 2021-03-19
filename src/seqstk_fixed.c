#include "seqstk_fixed.h"
const int32_t SEQSTK_ONE = (1 << 16);
const float SEQSTK_FRAC_LSB = (1.0 / (1 << 16));

// TODO: Fixed to float and vice versa, etc.

int32_t seqstk_float_to_fixed(const float a)
{
    return  a / SEQSTK_FRAC_LSB;
}

float seqstk_fixed_to_float(const int32_t a)
{
    return a * SEQSTK_FRAC_LSB; 
}

int32_t seqstk_fixed_mul(const int32_t a, const int32_t b)
{
    int64_t prod = (int64_t)a * (int64_t)b;
    prod /= SEQSTK_ONE;
    return prod;
}

int32_t seqstk_fixed_div(const int32_t a, const int32_t b)
{
    if(b == 0)
        return 0;
    return ((int64_t)a*SEQSTK_ONE) / ((int64_t)b);
}