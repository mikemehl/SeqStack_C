#include <stddef.h>
#include "seqstk_stack.h"


// Initialize the passed in stack.
bool seqstk_stk_init(VM_Stack * const stk)
{
   if(!stk)
      return false;
   stk->top = SEQSTK_STACK_EMPTY;
   return true;
}

// Push a value to the passed in stack.
bool seqstk_stk_push(VM_Stack * const stk, int32_t val)
{
   if(!stk)
      return false;
   if(stk->top == SEQSTK_STACK_EMPTY)
   {
      stk->top = 0;
      stk->data[stk->top] = val;
      return true;
   }
   else if (stk->top < STACK_SIZE - 1)
   {
      stk->top += 1;
      stk->data[stk->top] = val;
      return true;
   }
   return false;
}

int32_t *seqstk_stk_peek(VM_Stack * const stk)
{
   if(!stk)
      return NULL;
   if(stk->top > SEQSTK_STACK_EMPTY)
      return &(stk->data[stk->top]);
   return NULL;
}

int32_t *seqstk_stk_pop(VM_Stack * const stk)
{
   if(!stk)
      return NULL;
   int32_t * const top = seqstk_stk_peek(stk);
   if(top)
      stk->top -= 1;
   return top;
}

bool seqstk_stk_empty(VM_Stack const * const stk)
{
   return stk ? (stk->top == SEQSTK_STACK_EMPTY) : true;
}
