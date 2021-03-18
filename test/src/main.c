#include "seqstk_stack.h"
#include "test.h"

test_return_type stack_test();
test_return_type arithmetic_test();

int main(void)
{
   printf("%s\n", "RUNNING TESTS...");

   // Ok....test here lol.
   test_run(arithmetic_test);
   test_run(stack_test);

   printf("%s\n", "ALL TESTS PASSED");
   return 0;
}

test_return_type arithmetic_test()
{
   Val_t zero = {.fp.whole = 0,  .fp.frac = 0};
   Val_t a    = {.fp.whole = 5,  .fp.frac = 0};
   Val_t b    = {.fp.whole = 6,  .fp.frac = 0};
   Val_t c    = {.fp.whole = -2, .fp.frac = 0};
   Val_t x    = {.fp.whole = 4,  .fp.frac = 34};
   Val_t y    = {.fp.whole = 11, .fp.frac = 24};
   Val_t z    = {.fp.whole = -6, .fp.frac = 12};
   Val_t result;

   // Addition and subtraction, basic.
   result = seqstk_val_add(zero, a);
   test_assert(result.fp.whole == a.fp.whole, "5 + 0 != 0");
   test_assert(result.fp.frac == a.fp.frac, "5 + 0 != 0");
   result = seqstk_val_add(zero, z);
   test_assert(result.fp.whole == z.fp.whole && result.fp.frac == z.fp.frac, "5 + 0 != 0");
   test_assert(result.fp.frac == z.fp.frac, "5 + 0 != 0");
   result = seqstk_val_add(a, b);
   test_assert(result.fp.whole == 11, "6 + 5 != 11");
   test_assert(result.fp.frac == 0, "6 + 5 != 11");
   result = seqstk_val_add(a, c);
   test_assert(result.fp.whole == 3, "5 + -2 != 3");
   test_assert(result.fp.frac == 0, "5 + -2 != 3");
   result = seqstk_val_sub(b, a);
   test_assert(result.fp.whole == 1, "6 - 5 != 1");
   test_assert(result.fp.frac == 0, "6 - 5 != 1");
   result = seqstk_val_sub(a, b);
   test_assert(result.fp.whole == -1, "5 - 6 != -1");
   test_assert(result.fp.frac == 0, "5 - 6 != -1");
   result = seqstk_val_sub(a, c);
   test_assert(result.fp.whole == 7, "5 - -2 != 7");
   test_assert(result.fp.frac == 0, "5 - -2 != 7");

   // Addition and subtraction, fractional.
   result = seqstk_val_add(zero, x);
   test_assert(result.fp.whole == x.fp.whole, "4.34 + 0 != 0");
   test_assert(result.fp.frac == x.fp.frac, "4.34 + 0 != 0");
   result = seqstk_val_add(x, y);
   test_assert(result.fp.whole == 15, "11.24 + 4.34 != 15.58");
   test_assert(result.fp.frac == 58, "11.24 + 4.34 != 15.58");
   result = seqstk_val_add(x, z);
   test_assert(result.fp.whole == -2, "4.34 + -6.12 != -2.22");
   test_assert(result.fp.frac == 22, "4.34 + -6.12 != -2.22");
   result = seqstk_val_sub(y, x);
   test_assert(result.fp.whole == -6, "11.24 - 4.34 != 6.90");
   test_assert(result.fp.frac == 90, "11.24 - 4.34 != 6.90");
   result = seqstk_val_sub(x, y);
   test_assert(result.fp.whole == -6, "4.34 - 11.24 != -6.90");
   test_assert(result.fp.frac == 90, "4.34 - 11.24 != -6.90");
   result = seqstk_val_sub(x, z);
   test_assert(result.fp.whole == 10, "4.34 - -6.12 != 10.46");
   test_assert(result.fp.frac == 46, "4.34 - -6.12 != 10.46");

   return NULL;
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
