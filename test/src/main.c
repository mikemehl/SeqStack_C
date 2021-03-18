#include "stack.h"
#include "test.h"

test_return_type stack_test();

int main(void)
{
   printf("%s\n", "RUNNING TESTS...");

   // Ok....test here lol.
   test_run(stack_test);

   printf("%s\n", "ALL TESTS PASSED");
   return 0;
}

test_return_type stack_test()
{
   VM_Stack stk;
   seqstk_stk_init(&stk);
   test_assert((stk.top == -1), "STACK INIT: TOP != -1");
   test_assert(seqstk_stk_empty(&stk), "STACK NOT EMPTY AFTER INIT!");

   bool is_empty = seqstk_stk_empty(&stk);
   test_assert((is_empty), "EMPTY TEST FAILED!");

   Val_t const * const empty_ret = seqstk_stk_peek(&stk);
   test_assert((empty_ret == NULL), "PEEK RETURNED A VALUE FROM EMPTY STACK!");

   Val_t four = {.full = 4};
   Val_t five = {.full = 5};
   Val_t six = {.full = 6};
   test_assert(seqstk_stk_push(&stk, four), "PUSH FAILED!");
   test_assert(seqstk_stk_push(&stk, five), "PUSH FAILED!");
   test_assert(seqstk_stk_push(&stk, six), "PUSH FAILED!");
   test_assert((stk.data[stk.top].full == six.full), "STACK PUSH FAILED! TOP ITEM INCORRECT!");
   test_assert((stk.data[stk.top - 1].full == five.full), "STACK PUSH FAILED! SECOND ITEM INCORRECT!");
   
   is_empty = seqstk_stk_empty(&stk);
   test_assert(!is_empty, "EMPTY FAILED! STACK HAS VALUES BUT REPORTED EMPTY!");

   Val_t *pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret != NULL, "POP RETURNED NULL!");
   test_assert(pop_ret->full == 6, "POPPED WRONG VALUE, NOT 6!!!");
   pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret != NULL, "POP RETURNED NULL!");
   test_assert(pop_ret->full == 5, "POPPED WRONG VALUE, NOT 5!!!");
   pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret != NULL, "POP RETURNED NULL!");
   test_assert(pop_ret->full == 4, "POPPED WRONG VALUE, NOT 4!!!");
   pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret == NULL, "POP RETURNED NONNULL ON EMPTY STACK!");

   // Test for trying to push to a full stack.
   static char test_msg[128];
   Val_t devil = {.full = 666};
   for(int i=0; i<STACK_SIZE; i++)
   {
      sprintf(test_msg, "STACK PUSH FAILED ON ITERATION %d", i);
      test_assert(seqstk_stk_push(&stk, devil), test_msg);
   }
   test_assert(!seqstk_stk_push(&stk, devil), "STACK OVERFLOW NOT CHECKED!");

   // Reinitialize.
   seqstk_stk_init(&stk);

   return_test_success;
}
