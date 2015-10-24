/*-*- coding: utf-8 -*-

 Copyright (c) 2015 Zed A. Shaw <zedshaw@zedshaw.com>

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
Exercise 42 : Stacks and Queues
*/

#include "minunit.h"
#include <lcthw/stack.h>
#include <assert.h>

static Stack *stack = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};
#define NUM_TESTS 3

char *test_create()
{
  stack = Stack_create();
  mu_assert(stack != NULL, "Failed to create stack");

  return NULL;
}

char *test_destroy()
{
  mu_assert(stack != NULL, "Failed to make stack #2");
  Stack_destroy(stack);

  return NULL;
}

char *test_push_pop()
{
  int i = 0;
  for (i = 0; i < NUM_TESTS; i++) {
    Stack_push(stack, tests[i]);
    mu_assert(Stack_peek(stack) == tests[i], "Wrong next value");
  }

  mu_assert(Stack_count(stack) == NUM_TESTS, "Wrong count on push");
  STACK_FOREACH(stack, cur) {
    debug("VAL: %s", (char *)cur->value);
  }

  for (i = NUM_TESTS - 1; i >= 0; i--) {
    char *val = Stack_pop(stack);
    mu_assert(val == tests[i], "Wrong value on pop");
  }

  mu_assert(Stack_count(stack) == 0, "Wrong count after pop");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_push_pop);
  mu_run_test(test_destroy);

  return NULL;
}

RUN_TESTS(all_tests);
