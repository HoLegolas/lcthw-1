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
Exercise 40: Binary Search Trees
*/

#include "minunit.h"
#include <lcthw/bstree.h>
#include <assert.h>
#include <lcthw/bstrlib.h>
#include <stdlib.h>
#include <time.h>

BSTree *map = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("xest data 3");
struct tagbstring expect1 = bsStatic("THE VALUE 1");
struct tagbstring expect2 = bsStatic("THE VALUE 2");
struct tagbstring expect3 = bsStatic("THE VALUE 3");

static int traverse_good_cb(BSTreeNode *node) {
  debug("KEY: %s", bdata((bstring)node->key));
  traverse_called++;
  return 0;
}

static int traverse_fail_cb(BSTreeNode *node)
{
  debug("KEY: %s", bdata((bstring)node->key));
  traverse_called++;

  if(traverse_called == 2) {
    return 1;
  } else {
    return 0;
  }
}

char *test_create()
{
  map = BSTree_create(NULL);
  mu_assert(map != NULL, "Failed to create map.");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);

  return NULL;
}

RUN_TESTS(all_tests);

