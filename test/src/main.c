#include <math.h>
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
   const float epsilon = SEQSTK_FRAC_LSB;
   const float zero = 0.0;
   const float one = 1.0;
   const float a = 5.67;
   const int32_t fixed_a = 371589;
   const float b = 3.29;
   const int32_t fixed_b = 215613;
   const float c = -4.25;
   const int32_t fixed_c = -278528;
   float fout = 0.0;
   int32_t iout = 0;

   iout = seqstk_float_to_fixed(zero);
   test_assert(iout == 0, "Float -> Fixed failed on zero!");
   fout = seqstk_fixed_to_float(iout);
   test_assert(fout == 0.0, "Fixed -> Float failed on zero!");
   iout = seqstk_float_to_fixed(one);
   test_assert(iout == 1 << 16, "Float -> Fixed failed on one!");
   fout = seqstk_fixed_to_float(iout);
   test_assert(fout == 1.0, "Fixed -> Float failed on one!");
   iout = seqstk_float_to_fixed(a);
   test_assert(iout == fixed_a, "Float -> Fixed failed on 5.67!");
   fout = seqstk_fixed_to_float(iout);
   test_assert(fabs(fout - a) <= epsilon, "Fixed -> Float failed on 5.67!");
   iout = seqstk_float_to_fixed(b);
   test_assert(iout == fixed_b, "Float -> Fixed failed on 3.29!");
   fout = seqstk_fixed_to_float(iout);
   test_assert(fabs(fout - b) <= epsilon, "Fixed -> Float failed on 3.29!");
   iout = seqstk_float_to_fixed(c);
   test_assert(iout == fixed_c, "Float -> Fixed failed on -4.25!");
   fout = seqstk_fixed_to_float(iout);
   test_assert(fabs(fout - c) <= epsilon, "Fixed -> Float failed on -4.25!");


   return_test_success;
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

   const int32_t four = 4;
   const int32_t five = 5;
   const int32_t six  = 6;
   test_assert(seqstk_stk_push(&stk, four), "PUSH FAILED!");
   test_assert(seqstk_stk_push(&stk, five), "PUSH FAILED!");
   test_assert(seqstk_stk_push(&stk, six), "PUSH FAILED!");
   test_assert((stk.data[stk.top] == six), "STACK PUSH FAILED! TOP ITEM INCORRECT!");
   test_assert((stk.data[stk.top - 1] == five), "STACK PUSH FAILED! SECOND ITEM INCORRECT!");
   test_assert((stk.data[stk.top - 2] == four), "STACK PUSH FAILED! SECOND ITEM INCORRECT!");
   
   is_empty = seqstk_stk_empty(&stk);
   test_assert(!is_empty, "EMPTY FAILED! STACK HAS VALUES BUT REPORTED EMPTY!");

   int32_t *pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret != NULL, "POP RETURNED NULL!");
   test_assert(*pop_ret == six, "POPPED WRONG VALUE, NOT 6!!!");
   pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret != NULL, "POP RETURNED NULL!");
   test_assert(*pop_ret == five, "POPPED WRONG VALUE, NOT 5!!!");
   pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret != NULL, "POP RETURNED NULL!");
   test_assert(*pop_ret == four, "POPPED WRONG VALUE, NOT 4!!!");
   pop_ret = seqstk_stk_pop(&stk);
   test_assert(pop_ret == NULL, "POP RETURNED NONNULL ON EMPTY STACK!");

   // Test for trying to push to a full stack.
   static char test_msg[128];
   int32_t devil = 666;
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
