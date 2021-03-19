#ifndef _SEQSTK_VAL_H_
#define _SEQSTK_VAL_H_

#include <stdint.h>

extern const int32_t SEQSTK_ONE;
extern const float SEQSTK_FRAC_LSB;

int32_t seqstk_float_to_fixed(const float a);
float seqstk_fixed_to_float(const int32_t a);
int32_t seqstk_fixed_mul(const int32_t a, const int32_t b);
int32_t seqstk_fixed_div(const int32_t a, const int32_t b);
#endif