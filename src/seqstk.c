#include <string.h>
#include "seqstk.h"

bool seqstk_init(SeqStkVm * const vm)
{
    if(!vm)
        return false;
    vm->pc = 0;
    seqstk_stk_init(&vm->call_stack);
    seqstk_stk_init(&vm->data_stack);
    for(int i=0; i<NUM_PORTS; i++)
        seqstk_stk_init(&vm->ports[i]);
    for(int i=0; i<NUM_INTERRUPTS; i++)
        vm->interrupts[i] = INVALID_INTERRUPT;
    return true;;
}

bool seqstk_load_program(SeqStkVm * const vm, char const * const prog, const int32_t size)
{
    if(!vm || !prog || size > RAM_SIZE || size <= 0)
        return false;
    memcpy(vm->ram, prog, size);
    return true;
}