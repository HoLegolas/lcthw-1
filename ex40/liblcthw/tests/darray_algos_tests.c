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
Exercise 35 - Sorting and Merging
*/

#include "minunit.h"
#include <lcthw/darray_algos.h>

int testcmp(char **a, char **b)
{
  return strcmp(*a, *b);
}

DArray *create_words()
{
  DArray *result = DArray_create(0, 5);
  char *words[] = { "asdfasfd", "werwar", "13234", "asdfasfd", "oioj" };
  int i = 0;

  for (i = 0; i < 5; i++) {
    DArray_push(result, words[i]);
  }

  return result;
}

int is_sorted(DArray *array)
{
  int i = 0;

  for (i = 0; i < DArray_count(array) - 1; i++) {
    if(strcmp(DArray_get(array, i), DArray_get(array, i+1)) > 0) {
      return 0;
    }
  }

  return 1;
}

char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name)
{
  DArray *words = create_words();
  mu_assert(!is_sorted(words), "Words should start not sorted.");

  debug("--- Testing %s sorting algorithm", name);
  int rc = func(words, (DArray_compare)testcmp);
  mu_assert(rc == 0, "sort failed");
  mu_assert(is_sorted(words), "didn't sort it");

  DArray_destroy(words);

  return NULL;
}

char *test_qsort()
{
  return run_sort_test(DArray_qsort, "qsort");
}

char *test_heapsort()
{
  return run_sort_test(DArray_heapsort, "heapsort");
}

char *test_mergesort()
{
  return run_sort_test(DArray_mergesort, "mergesort");
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_qsort);
  mu_run_test(test_heapsort);
  mu_run_test(test_mergesort);

  return NULL;
}

RUN_TESTS(all_tests);

