#ifndef _SEQSTK_H_
#define _SEQSTK_H_

#include "seqstk_stack.h"

#define NUM_PORTS 8
#define RAM_SIZE 1 << 16
#define NUM_INTERRUPTS NUM_PORTS 

typedef struct SeqStkVm
{
    int8_t   ram[RAM_SIZE];
    int      pc;
    VM_Stack call_stack;
    VM_Stack data_stack;
    VM_Stack ports[NUM_PORTS];
    int      interrupts[NUM_INTERRUPTS];
} SeqStkVm;

#endif