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
DOCUMENTATION
*/

#include "dbg.h"
#include <stdlib.h>
#include <stdio.h>

void test_debug()
{
  // notice you don't need the \n
  debug("I have brown hair.");

  // passing in arguments like printf
  debug("I'm %d years old.", 41);
}

void test_log_err()
{
  log_err("I believe everything is broken.");
  log_err("There are %d problems in %s.", 0, "space");
}

void test_log_warn()
{
  log_warn("You can safely ignore this.");
  log_warn("Maybe consider looking at: %s.", "/etc/passwd");
}

void test_log_info()
{
  log_info("Well I did something mundane.");
  log_info("It happened %f times today.", 1.3f);
}

int test_check(char *filename)
{
  FILE *input = NULL;
  char *block = NULL;

  block = malloc(100);
  check_mem(block); // should work

  input = fopen(filename, "r");
  check(input, "Failed to open %s", filename);

  free(block);
  fclose(input);
  return 0;

 error:
  if(block) free(block);
  if(input) fclose(input);
  return -1;
}

int test_sentinel(int code)
{
  char *temp = malloc(100);
  check_mem(temp);

  switch(code) {
  case 1:
    log_info("It worked.");
    break;
  default:
    sentinel("I shouldn't run.");
  }

  free(temp);
  return 0;

 error:
  if(temp) free(temp);
  return -1;
}

int test_check_mem()
{
  char *test = NULL;
  check_mem(test);

  free(test);
  return 1;

 error:
  return -1;
}

int test_check_debug()
{
  int i = 0;
  check_debug(i != 0, "Ooops, I was 0.");

  return 0;

 error:
  return -1;
}

int main(int argc, char *argv[])
{
  check(argc == 2, "Need an argument");

  test_debug();
  test_log_err();
  test_log_warn();
  test_log_info();

  check(test_check("ex20.c") == 0, "failed with ex20.c");
  check(test_check(argv[1]) == -1, "failed with argv");
  check(test_sentinel(1) == 0, "test_sentinel failed.");
  check(test_sentinel(100) == -1, "test_sentinel failed.");
  check(test_check_mem() == -1, "test_check_mem failed.");
  check(test_check_debug() == -1, "test_check_debug failed.");

  return 0;

 error:
  return 1;
}
