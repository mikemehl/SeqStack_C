#include "seqstk_val.h"

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