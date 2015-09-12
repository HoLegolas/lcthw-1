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
Exercise 30 - Automated testing
*/

#include "minunit.h"
#include <dlfcn.h>

typedef int (*lib_function)(const char *data);
char *lib_file = "build/libex29.so";
void *lib = NULL;

int check_function(const char *func_to_run, const char *data, int expected)
{
  lib_function func = dlsym(lib, func_to_run);
  check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

  int rc = func(data);
  check(rc == expected, "Function %s return %d for data: %s", func_to_run, rc, data);

  return 1;

 error:
  return 0;
}

char *test_dlopen()
{
  lib = dlopen(lib_file, RTLD_NOW);
  mu_assert(lib != NULL, "Failed to open the library to test.");

  return NULL;
}

char *test_functions()
{
  mu_assert(check_function("print_a_message", "Hello", 0), "print_a_message failed.");
  mu_assert(check_function("uppercase", "Hello", 0), "uppercase failed.");
  mu_assert(check_function("lowercase", "Hello", 0), "lowercase failed.");
  
  return NULL;
}

char *test_failures()
{
  mu_assert(check_function("fail_on_purpose", "Hello", 1), "fail_on_purpose should fail.");
  
  return NULL;
}

char *test_dlclose()
{
  int rc = dlclose(lib);
  mu_assert(rc == 0, "Failed to close lib.");
  
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_dlopen);
  mu_run_test(test_functions);
  mu_run_test(test_failures);
  mu_run_test(test_dlclose);

  return NULL;
}

RUN_TESTS(all_tests);
