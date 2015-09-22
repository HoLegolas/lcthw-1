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
#include <lcthw/queue.h>
#include <assert.h>

static Queue *queue = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};
#define NUM_TESTS 3

char *test_create()
{
  queue = Queue_create();
  mu_assert(queue != NULL, "Failed to create queue");

  return NULL;
}

char *test_destroy()
{
  mu_assert(queue != NULL, "Failed to make queue #2");
  Queue_destroy(queue);

  return NULL;
}

char *test_send_recv()
{
  int i = 0;
  for (i = 0; i < NUM_TESTS; i++) {
    Queue_send(queue, tests[i]);
    mu_assert(Queue_peek(queue) == tests[0], "Wrong next value");
  }

  mu_assert(Queue_count(queue) == NUM_TESTS, "Wrong count on send");
  QUEUE_FOREACH(queue, cur) {
    debug("VAL: %s", (char *)cur->value);
  }

  for (i = 0; i < NUM_TESTS; i++) {
    char *val = Queue_recv(queue);
    mu_assert(val == tests[i], "Wrong value on recv");
  }

  mu_assert(Queue_count(queue) == 0, "Wrong count after recv");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_send_recv);
  mu_run_test(test_destroy);

  return NULL;
}

RUN_TESTS(all_tests);
