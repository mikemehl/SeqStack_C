#include <string.h>
#include "seqstk.h"
#include "seqstk_opcodes.h"

const uint8_t OP_GROUP_MASK = 0b11100000;
const uint8_t OP_MASK       = 0b00011100;
const uint8_t ADDR_MASK     = 0b00000011;
const uint8_t PORT_MASK     = 0b00000111;

static bool seqstk_cycle_stack_op(SeqStkVm * const vm, const uint8_t next_inst);
static bool seqstk_push_imm(SeqStkVm * const vm);
static bool seqstk_push_index_stack(SeqStkVm * const vm);
static bool seqstk_push_index_imm(SeqStkVm * const vm);
static bool seqstk_push_stack(SeqStkVm * const vm);

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

bool seqstk_cycle(SeqStkVm * const vm)
{
    if(!vm)
        return false;
    if(vm->pc < RAM_SIZE)
    {
        // Grab the next instruction.
        const uint8_t next_inst = vm->ram[vm->pc];
        vm->pc += 1;

        // Figure out which group it belongs to, and call it's function.
        const uint8_t inst_group = (next_inst & OP_GROUP_MASK);
        if(inst_group == OP_GROUP_STACK)
            return seqstk_cycle_stack_op(vm, next_inst);
    }
    return false;
}


static bool seqstk_cycle_stack_op(SeqStkVm * const vm, const uint8_t next_inst)
{
    // Extract the specific op and addressing mode;
    const uint8_t op = next_inst & OP_MASK;
    const uint8_t addr_mode = next_inst & ADDR_MASK;
    if(op == (PUSH_IMM & OP_MASK))
    {
        if(addr_mode == ADDR_IMM)
            return seqstk_push_imm(vm);
        else if(addr_mode == ADDR_INDEX_STACK)
            return seqstk_push_index_stack(vm);
        else if (addr_mode == ADDR_INDEX_IMM)
            return seqstk_push_index_imm(vm);
        else if (addr_mode == ADDR_STACK)
            return seqstk_push_stack(vm);
    } 
    return false;
}

static bool seqstk_push_imm(SeqStkVm * const vm)
{
    if(vm->pc + 4 < RAM_SIZE)
    {
        bool success = seqstk_stk_push(&vm->data_stack, *((int32_t * const)&vm->ram[vm->pc]));
        vm->pc += sizeof(int32_t);
        return success;
    }
    return false;
}

static bool seqstk_push_index_stack(SeqStkVm * const vm)
{
    if(vm->pc + 4 < RAM_SIZE)
    {
        int32_t * const offset = seqstk_stk_pop(&vm->data_stack);
        if(!offset)
            return false;
        *offset >>= 16;
        const int16_t addr = *((int16_t * const)&vm->ram[vm->pc]) + *offset;
        bool success = seqstk_stk_push(&vm->data_stack, *((int32_t * const)&vm->ram[addr]));
        vm->pc += sizeof(int16_t);
        return success;
    }
    return false;

}

static bool seqstk_push_index_imm(SeqStkVm * const vm)
{
    if(vm->pc + 2 < RAM_SIZE)
    {
        int16_t const * const offset = (int16_t * const)&vm->ram[vm->pc];
        int32_t * const addr = seqstk_stk_pop(&vm->data_stack);
        if(!addr)
            return false;
        *addr >>= 16;
        *addr += *offset;
        bool success = seqstk_stk_push(&vm->data_stack, *((int32_t * const)&vm->ram[*addr]));
        vm->pc += sizeof(int16_t);
        return success;
    }
    return false;

}

static bool seqstk_push_stack(SeqStkVm * const vm)
{
    int32_t * const addr = seqstk_stk_pop(&vm->data_stack);
    if(addr)
    {
        *addr >>= 16;
        return seqstk_stk_push(&vm->data_stack, *((int32_t * const)&vm->ram[*addr]));
    }
    return false;
}