#ifndef _SEQSTK_VAL_H_
#define _SEQSTK_VAL_H_

#include <stdint.h>

extern const float SEQSTK_FRAC_LSB;

typedef union Val_t
{
    int32_t full;
    struct 
    {
        int16_t whole;
        uint16_t frac;
    } fp;
    char bytes[4];
} Val_t;

Val_t seqstk_val_add(const Val_t a, const Val_t b);
Val_t seqstk_val_sub(const Val_t a, const Val_t b);
#endif