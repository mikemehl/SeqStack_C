#ifndef _STACK_H_
#define _STACK_H_

#include <stdint.h>
#include <stdbool.h>

#define STACK_SIZE ((1 << 16) -1)
#define SEQSTK_STACK_EMPTY -1

// The stack data structure.
typedef struct
{
   int32_t data[STACK_SIZE]; 
   int top;
} VM_Stack;


// Initialize the stack (set top to empty.)
void seqstk_stk_init(VM_Stack * const stk);

// Push a value on to the stack. Returns true on success, false otherwise.
bool seqstk_stk_push(VM_Stack * const stk, int32_t val);

// Peek at the value on top of the stack. Returns a pointer to the value on success, NULL otherwise.
int32_t * seqstk_stk_peek(VM_Stack * const stk);

// Check if the stack is empty.
bool seqstk_stk_empty(VM_Stack const * const stk);

#endif
