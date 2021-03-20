#include <math.h>
#include "seqstk_stack.h"
#include "seqstk_fixed.h"
#include "seqstk.h"
#include "test.h"


test_return_type stack_test();
test_return_type arithmetic_test();
test_return_type vm_init_tests();
test_return_type stack_op_tests();

int main(void)
{
   printf("%s\n", "RUNNING TESTS...");

   // Ok....test here lol.
   test_run(arithmetic_test);
   test_run(stack_test);
   test_run(vm_init_tests);
   test_run(stack_op_tests);

   printf("%s\n", "ALL TESTS PASSED");
   return 0;
}

test_return_type vm_init_tests()
{
   SeqStkVm vm;
   static char msg[256];

   // Initialize the vm.
   test_assert(!seqstk_init(NULL), "VM NULL INIT FAILED");
   test_assert(seqstk_init(&vm), "VM INIT FAILED");
   test_assert(vm.pc == 0, "PC NOT INITIALIZED TO 0");
   test_assert(seqstk_stk_empty(&vm.call_stack), "CALL STACK NOT EMPTIED");
   test_assert(seqstk_stk_empty(&vm.data_stack), "CALL STACK NOT EMPTIED");
   for(int i=0; i<NUM_PORTS; i++)
   {
      sprintf(msg, "PORT %d NOT EMPTIED", i);
      test_assert(seqstk_stk_empty(&vm.ports[i]), msg);
   }
   for(int i=0; i<NUM_INTERRUPTS; i++)
   {
      sprintf(msg, "INTERRUPT %d NOT INVALID", i);
      test_assert(vm.interrupts[i] == INVALID_INTERRUPT, msg);
   }

   const char code[RAM_SIZE] = { 0 };
   *((int32_t * const)&code[0]) = seqstk_float_to_fixed(1234.5678);
   test_assert(seqstk_load_program(&vm, code, RAM_SIZE), "LOAD CODE FAILED");
   for(unsigned int i=0; i<sizeof(int32_t); i++)
      test_assert(vm.ram[i] !=0, "FAILED TO LOAD CODE");
   
   test_assert(!seqstk_load_program(&vm, NULL, RAM_SIZE), "NULL CODE INIT FAILED");
   test_assert(!seqstk_load_program(NULL, code, RAM_SIZE), "NULL VM INIT FAILED");
   test_assert(!seqstk_load_program(&vm, code, 0), "0 SIZE INIT FAILED");
   test_assert(!seqstk_load_program(&vm, code, -666), "NEGATIVE SIZE INIT FAILED");
   
   return_test_success;
}

test_return_type stack_op_tests()
{
   //static char code[RAM_SIZE];
   SeqStkVm vm;
   test_assert(seqstk_init(&vm), "Init failed????");

   // TODO: Try loading in some code with the different stack opcodes..did it work?

   return_test_success;
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
   test_assert(!seqstk_stk_init(NULL), "NULL STACK INIT FAILED");
   test_assert(seqstk_stk_init(&stk), "STACK INIT FAILED");
   test_assert((stk.top == -1), "STACK INIT: TOP != -1");
   test_assert(seqstk_stk_empty(&stk), "STACK NOT EMPTY AFTER INIT!");

   bool is_empty = seqstk_stk_empty(&stk);
   test_assert(seqstk_stk_empty(NULL), "NULL STK WAS NOT EMPTY");
   test_assert((is_empty), "EMPTY TEST FAILED!");

   int32_t const * const empty_ret = seqstk_stk_peek(&stk);
   test_assert((empty_ret == NULL), "PEEK RETURNED A VALUE FROM EMPTY STACK!");

   const int32_t four = 4;
   const int32_t five = 5;
   const int32_t six  = 6;
   test_assert(!seqstk_stk_push(NULL, four), "NULL PUSH FAILED!");
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
