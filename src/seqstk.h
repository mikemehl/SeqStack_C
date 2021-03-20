#ifndef _SEQSTK_H_
#define _SEQSTK_H_

#include "seqstk_stack.h"

#define NUM_PORTS 8
#define RAM_SIZE (1 << 15)
#define NUM_INTERRUPTS NUM_PORTS 
#define INVALID_INTERRUPT -1

typedef struct SeqStkVm
{
    int8_t   ram[RAM_SIZE];
    int      pc;
    VM_Stack call_stack;
    VM_Stack data_stack;
    VM_Stack ports[NUM_PORTS];
    int32_t      interrupts[NUM_INTERRUPTS];
} SeqStkVm;

bool seqstk_init(SeqStkVm * const vm);
bool seqstk_load_program(SeqStkVm * const vm, char const * const prog, const int32_t size);
bool seqstk_cycle(SeqStkVm * const vm);

#endif