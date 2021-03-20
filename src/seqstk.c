#include "seqstk.h"

void seqstk_init(SeqStkVm * const vm)
{
    vm->pc = 0;
    seqstk_stk_init(&vm->call_stack);
    seqstk_stk_init(&vm->data_stack);
    for(int i=0; i<NUM_PORTS; i++)
        seqstk_stk_init(&vm->ports[i]);
    for(int i=0; i<NUM_INTERRUPTS; i++)
        vm->interrupts[i] = INVALID_INTERRUPT;
    return;
}