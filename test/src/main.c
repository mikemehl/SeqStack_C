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

   return NULL;
}