#include "seqstk_val.h"

const float SEQSTK_FRAC_LSB = (1 / (1 << 16));

// TODO: Fixed to float and vice versa, etc.

Val_t seqstk_val_add(const Val_t a, const Val_t b)
{
    Val_t out;
    out.fp.whole = a.fp.whole + b.fp.whole;
    // TODO: What if one of the values is negative? 
    //       Then you gotta handle the fraction differently, wehhhhhhhh.
    out.fp.frac = a.fp.frac + b.fp.frac;
    return out;
}

Val_t seqstk_val_sub(const Val_t a, const Val_t b)
{
    Val_t out;
    out.fp.whole = a.fp.whole - b.fp.whole;
    out.fp.frac = a.fp.frac - b.fp.frac;
    return out;
}