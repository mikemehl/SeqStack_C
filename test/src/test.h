#ifndef _TEST_H_
#define _TEST_H_
#include <stddef.h>
#include <stdio.h>

#define test_assert(test, message) do { if (!(test)) return message; } while(0)
#define test_run(test) do { char const *message = test(); if (message) { printf("%s\n", "FAILED TEST: "); printf("%s\n", message); return -1; }} while(0)
#define test_return_type char *

#endif
