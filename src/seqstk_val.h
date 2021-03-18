#ifndef _SEQSTK_NUM_H_
#define _SEQSTK_NUM_H_

#include <stdint.h>

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

#endif