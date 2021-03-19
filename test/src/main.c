#include <math.h>
#include "seqstk_stack.h"
#include "seqstk_fixed.h"
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
   const float muldiv_epsilon = 3.30 * epsilon; // TODO: Can we get this more precise?
   const float zero = 0.0;
   const float one = 1.0;
   const int32_t fixed_one = (1 << 16);
   const float a = 5.67;
   const int32_t fixed_a = 371589;
   const float b = 3.29;
   const int32_t fixed_b = 215613;
   const float c = -4.25;
   const int32_t fixed_c = -278528;
   const float a_times_b = a*b;
   const float a_times_c = a*c;
   const float c_times_c = c*c;
   const float a_div_b = a/b;
   const float a_div_c = a/c;
   const float c_div_c = c/c;
   float fout = 0.0;
   int32_t iout = 0;
//   int32_t iprod_out = 0;

   // Conversions
   iout = seqstk_float_to_fixed(zero);
   test_assert(iout == 0, "Float -> Fixed failed on zero!");
   fout = seqstk_fixed_to_float(iout);
   test_assert(fout == 0.0, "Fixed -> Float failed on zero!");
   iout = seqstk_float_to_fixed(one);
   test_assert(iout == fixed_one, "Float -> Fixed failed on one!");
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

   // Multiplication
   int32_t x = 0;
   int32_t y = 0;
   x = seqstk_float_to_fixed(zero);
   y = seqstk_float_to_fixed(zero);
   iout = seqstk_fixed_mul(x, y);
   test_assert(iout == 0, "Fixed mul failed: 0*0 != 0");
   x = seqstk_float_to_fixed(one);
   iout = seqstk_fixed_mul(x, y);
   test_assert(iout == 0, "Fixed mul failed: 1*0 != 0");
   y = seqstk_float_to_fixed(one);
   iout = seqstk_fixed_mul(x, y);
   test_assert(iout == fixed_one, "Fixed mul failed: 1*1 != 1");
   x = seqstk_float_to_fixed(a);
   y = seqstk_float_to_fixed(b);
   iout = seqstk_fixed_mul(x, y);
   fout = seqstk_fixed_to_float(iout);
   test_assert(fabs(fout - a_times_b) < muldiv_epsilon, "Fixed mul failed: 5.67*3.29");
   x = seqstk_float_to_fixed(a);
   y = seqstk_float_to_fixed(c);
   iout = seqstk_fixed_mul(x, y);
   fout = seqstk_fixed_to_float(iout);
   test_assert(fabs(fout - a_times_c) < muldiv_epsilon, "Fixed mul failed: 5.67*-4.25");
   x = seqstk_float_to_fixed(c);
   y = seqstk_float_to_fixed(c);
   iout = seqstk_fixed_mul(x, y);
   fout = seqstk_fixed_to_float(iout);
   test_assert(fabs(fout - c_times_c) < muldiv_epsilon, "Fixed mul failed: -4.25*-4.25");

   // Division
   x = seqstk_float_to_fixed(zero);
   y = seqstk_float_to_fixed(zero);
   iout = seqstk_fixed_div(x, y);
   test_assert(iout == 0, "Fixed div failed: 0/0 != 0");
   x = seqstk_float_to_fixed(one);
   iout = seqstk_fixed_div(y, x);
   test_assert(iout == 0, "Fixed div failed: 0/1 != 0");
   y = seqstk_float_to_fixed(one);
   iout = seqstk_fixed_div(x, y);
   test_assert(iout == fixed_one, "Fixed div failed: 1/1 != 1");
   x = seqstk_float_to_fixed(a);
   y = seqstk_float_to_fixed(b);
   iout = seqstk_fixed_div(x, y);
   fout = seqstk_fixed_to_float(iout);
   test_assert(fabs(fout - a_div_b) < muldiv_epsilon, "Fixed div failed: 5.67/3.29");
   x = seqstk_float_to_fixed(a);
   y = seqstk_float_to_fixed(c);
   iout = seqstk_fixed_div(x, y);
   fout = seqstk_fixed_to_float(iout);
   test_assert(fabs(fout - a_div_c) < muldiv_epsilon, "Fixed div failed: 5.67/-4.25");
   x = seqstk_float_to_fixed(c);
   y = seqstk_float_to_fixed(c);
   iout = seqstk_fixed_div(x, y);
   fout = seqstk_fixed_to_float(iout);
   test_assert(fabs(fout - c_div_c) < muldiv_epsilon, "Fixed mul failed: -4.25/-4.25");

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
