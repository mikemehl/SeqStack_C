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

   int32_t const * const empty_ret = seqstk_stk_peek(&stk);
   test_assert((empty_ret == NULL), "PEEK RETURNED A VALUE FROM EMPTY STACK!");

   test_assert(seqstk_stk_push(&stk, 4), "PUSH FAILED!");
   test_assert(seqstk_stk_push(&stk, 5), "PUSH FAILED!");
   test_assert(seqstk_stk_push(&stk, 6), "PUSH FAILED!");
   test_assert((stk.data[stk.top] == 6), "STACK PUSH FAILED! TOP ITEM INCORRECT!");
   test_assert((stk.data[stk.top - 1] == 5), "STACK PUSH FAILED! SECOND ITEM INCORRECT!");
   
   is_empty = seqstk_stk_empty(&stk);
   test_assert(!is_empty, "EMPTY FAILED! STACK HAS VALUES BUT REPORTED EMPTY!");

   int32_t *pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret != NULL, "POP RETURNED NULL!");
   test_assert(*pop_ret == 6, "POPPED WRONG VALUE, NOT 6!!!");
   pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret != NULL, "POP RETURNED NULL!");
   test_assert(*pop_ret == 5, "POPPED WRONG VALUE, NOT 5!!!");
   pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret != NULL, "POP RETURNED NULL!");
   test_assert(*pop_ret == 4, "POPPED WRONG VALUE, NOT 4!!!");
   pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret == NULL, "POP RETURNED NONNULL ON EMPTY STACK!");

   // Test for trying to push to a full stack (should fail).
   stk.top = STACK_SIZE;
   test_assert(!seqstk_stk_push(&stk, 666), "STACK OVERFLOW NOT CHECKED!");

   // Reinitialize.
   seqstk_stk_init(&stk);

   return_test_success;
}
