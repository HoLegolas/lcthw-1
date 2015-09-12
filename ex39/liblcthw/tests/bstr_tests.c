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
Exercise 36 : Safer strings
*/

#include "minunit.h"
#include <lcthw/bstrlib.h>

static char *test_bfromcstr()
{
  char *msg = "Le message";
  bstring bstr = NULL;

  bstr = bfromcstr(msg);
  mu_assert(bstr != NULL, "Problem creating a bstring from a C string (out of memory ?)");
  mu_assert(bdestroy(bstr) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_blk2bstr()
{
  char *msg = "Le message";
  bstring bstr = NULL;

  bstr = blk2bstr(msg, 4);
  mu_assert(bstr != NULL, "Problem creating a bstring from a C string (out of memory ?).");
  mu_assert(blength(bstr) == 4, "Bstring is not 4 characters long as msg C string.");
  mu_assert(bdestroy(bstr) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_bstrcpy()
{
  bstring bstr_src = bfromcstr("string1");
  bstring bstr_dest = NULL;
  bstr_dest = bstrcpy(bstr_src);
  mu_assert(bstr_dest != NULL, "Problem creating a bstring from a C string (out of memory ?).");
  mu_assert(bstrcmp(bstr_src, bstr_dest) == 0, "Bstrings should be equal.");
  mu_assert(bdestroy(bstr_src) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_dest) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_bassign()
{
  bstring bstr_a = bfromcstr("string1");
  bstring bstr_b = bfromcstr("very long string, at least longer than a.");
  mu_assert(bassign(bstr_a, bstr_b) != BSTR_ERR, "An error occurs when calling bassign.");
  mu_assert(bstrcmp(bstr_a, bstr_b) == 0, "Bstrings should be equal.");
  mu_assert(bdestroy(bstr_a) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_b) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_bassigncstr()
{
  bstring bstr_a = bfromcstr("string1");
  char *cstr_b = "very long C string, at least longer than a.";
  bstring bstr_b = bfromcstr(cstr_b);
  mu_assert(bassigncstr(bstr_a, cstr_b) != BSTR_ERR, "An error occurs when calling bassigncstr.");
  mu_assert(bstrcmp(bstr_a, bstr_b) == 0, "Bstrings and CStr should be equal.");
  mu_assert(bdestroy(bstr_a) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_b) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_bassignblk()
{
  bstring bstr_a = bfromcstr("string1");
  char *cstr_b = "very long string, at least longer than a.";
  bstring bstr_b = bfromcstr("very");
  mu_assert(bassignblk(bstr_a, cstr_b, 4) != BSTR_ERR, "An error occurs when calling bassignblk.");
  /* printf("bstr_a = %s\n", bstr_a->data); */
  mu_assert(bstrcmp(bstr_a, bstr_b) == 0, "Bstrings should be equal.");
  mu_assert(bdestroy(bstr_a) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_b) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_bdestroy()
{
  bstring bstr_a = bfromcstr("string1");
  mu_assert(bdestroy(bstr_a) != BSTR_ERR, "An error occurs when calling bstring.");

  return NULL;
}

static char *test_bconcat()
{
  bstring bstr_a = bfromcstr("first");
  bstring bstr_b = bfromcstr("second");
  bstring bstr_c = bfromcstr("firstsecond");
  mu_assert(bconcat(bstr_a, bstr_b) == BSTR_OK, "An error occurs when calling bconcat.");
  mu_assert(bstrcmp(bstr_a, bstr_c) == 0, "Bstrings should be equal.");
  mu_assert(bdestroy(bstr_a) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_b) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_c) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_bstricmp()
{
  bstring bstr_a = bfromcstr("First");
  bstring bstr_b = bfromcstr("firST");
  mu_assert(bstricmp(bstr_a, bstr_b) == 0, "Bstrings should be equal ignoring case.");
  mu_assert(bdestroy(bstr_a) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_b) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}


static char *test_biseq()
{
  bstring bstr_a = bfromcstr("First");
  bstring bstr_b = bfromcstr("firST");
  mu_assert(!biseq(bstr_a, bstr_b), "Bstrings should not be equal using biseq.");
  mu_assert(bdestroy(bstr_a) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_b) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_binstr()
{
  const_bstring bstr_a = bfromcstr("This is the long string to test.");
  const_bstring bstr_b = bfromcstr("long string");
  mu_assert(binstr(bstr_a, 0, bstr_b) == 12, "binstr should succeed to find bstr_b into bstr_a.");
  mu_assert(binstr(bstr_a, 12, bstr_b) == 12, "binstr should succeed to find bstr_b into bstr_a from pos == 12.");
  mu_assert(binstr(bstr_a, 13, bstr_b) == BSTR_ERR, "binstr should fail when not succeeding to find bstr_b into bstr_a.");
  mu_assert(bdestroy((bstring) bstr_a) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy((bstring) bstr_b) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_bfindreplace()
{
  bstring bstr_b = bfromcstr("one two three two");
  bstring bstr_find = bfromcstr("two");
  bstring bstr_replace = bfromcstr("four");
  bstring bstr_a = bfromcstr("one four three four");
  mu_assert(bfindreplace(bstr_b, bstr_find, bstr_replace, 0) == BSTR_OK, "bfindreplace should succeed to replace bstr_find by bstr_replace into bstr_b.");
  mu_assert(bstrcmp(bstr_b, bstr_a) == 0, "bfindreplace has incorrectly replaced bstr_find by bstr_replace into bstr_b.");
  mu_assert(bdestroy(bstr_b) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_find) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_replace) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_a) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_bsplit()
{
  bstring bstr_a = bfromcstr("one two three four");
  unsigned char splitChar = ' ';
  struct bstrList *bstr_list;
  bstring bstr_one = bfromcstr("one");
  bstring bstr_two = bfromcstr("two");

  mu_assert(bstr_list = bsplit(bstr_a, splitChar), "Call to bsplit should not return NULL.");
  mu_assert(bstrcmp(bstr_list->entry[0], bstr_one) == 0, "The first entry of the bstr_list should by 'one'.");
  mu_assert(bstrcmp(bstr_list->entry[1], bstr_two) == 0, "The second entry of the bstr_list should by 'two'.");

  bstrListDestroy(bstr_list);

  mu_assert(bdestroy(bstr_a) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_one) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_two) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_bformat()
{
  bstring bstr_a = bfromcstr("one two three four");
  bstring bstr_b = NULL;
  bstring bstr_c = bfromcstr("zero one two three four");
  mu_assert(bstr_b = bformat("zero %s", bstr_a->data), "Call to bformat should not return NULL.");
  mu_assert(bstrcmp(bstr_b, bstr_c) == 0, "bstring should be equal after bformat.");
  mu_assert(bdestroy(bstr_a) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_b) == BSTR_OK, "Problem destroying bstring.");
  mu_assert(bdestroy(bstr_c) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

static char *test_blength()
{
  bstring bstr_a = bfromcstr("one two three four");
  mu_assert(blength(bstr_a) == 18, "blength should return length of bstring.");
  mu_assert(bdestroy(bstr_a) == BSTR_OK, "Problem destroying bstring.");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_bfromcstr);
  mu_run_test(test_blk2bstr);
  mu_run_test(test_bstrcpy);
  mu_run_test(test_bassign);
  mu_run_test(test_bassigncstr);
  mu_run_test(test_bassignblk);
  mu_run_test(test_bdestroy);
  mu_run_test(test_bconcat);
  mu_run_test(test_bstricmp);
  mu_run_test(test_biseq);
  mu_run_test(test_binstr);
  mu_run_test(test_bfindreplace);
  mu_run_test(test_bsplit);
  mu_run_test(test_bformat);
  mu_run_test(test_blength);

  return NULL;
}

RUN_TESTS(all_tests);
