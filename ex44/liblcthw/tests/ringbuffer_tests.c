/*-*- coding: utf-8 -*-

 Copyright (c) 2015 Jérôme Radix <jerome.radix@gmail.com>

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
Exercise 44 : Ring Buffers
*/

#include "minunit.h"
#include <lcthw/ringbuffer.h>

static RingBuffer *buffer = NULL;
char *tests[] = {"XXXX", "ABCD", "0123"};
#define NUM_TESTS 3
#define TEST_LEN 12

char *test_create()
{
  buffer = RingBuffer_create(TEST_LEN);
  mu_assert(buffer != NULL, "Failed to create buffer");

  return NULL;
}

char *test_destroy()
{
  mu_assert(buffer != NULL, "Failed to make ring buffer #2");
  RingBuffer_destroy(buffer);

  return NULL;
}

char *test_read_write()
{
  int i = 0;
  char target[TEST_LEN] = { '\0' };
  bstring bstr_a = NULL;
  bstring bstr_b = NULL;
  int length = -1;

  for (i = 0; i < NUM_TESTS; i++) {
    length = RingBuffer_write(buffer, tests[i], 4);
    check(length == 4, "Length should be 4, it is: %d", length);
  }

  for (i = 0; i < NUM_TESTS; i++) {
    RingBuffer_read(buffer, target, 4);
    bstr_a = blk2bstr(tests[i], 4);
    bstr_b = blk2bstr(target, 4);
    mu_assert(biseq(bstr_a, bstr_b) == 1, "Bstrings should be equal.");
    bdestroy(bstr_a);
    bdestroy(bstr_b);
  }

 error:
  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_read_write);
  mu_run_test(test_destroy);

  return NULL;
}

RUN_TESTS(all_tests);
