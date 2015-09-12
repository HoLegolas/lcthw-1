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
Exercise 23 - Meet Duff's device
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dbg.h"

int normal_copy(char *from, char *to, int count)
{
  int i = 0;

  for(i = 0; i < count; i++) {
    to[i] = from[i];
  }

  return i;
}

int duffs_device(char *from, char *to, int count)
{
  {
    int n = (count + 7) / 8;

    switch(count % 8) {
    case 0: do { *to++ = *from++;
      case 7: *to++ = *from++;
      case 6: *to++ = *from++;
      case 5: *to++ = *from++;
      case 4: *to++ = *from++;
      case 3: *to++ = *from++;
      case 2: *to++ = *from++;
      case 1: *to++ = *from++;
      } while(--n > 0);
    }

  }
  return count;
}

int zeds_device(char *from, char *to, int count)
{
  {
    int n = (count + 7) / 8;

    switch(count % 8) {
    case 0:
    again: *to++ = *from++;

    case 7: *to++ = *from++;
    case 6: *to++ = *from++;
    case 5: *to++ = *from++;
    case 4: *to++ = *from++;
    case 3: *to++ = *from++;
    case 2: *to++ = *from++;
    case 1: *to++ = *from++;
      if(--n > 0) goto again;
    }
  }
  return count;
}

int valid_copy(char *data, int count, char expects)
{
  int i = 0;
  for(i = 0; i < count; i++) {
    if(data[i] != expects) {
      log_err("[%d] %c != %c", i, data[i], expects);
      return 0;
    }
  }
  return 1;
}

int main(int argc, char *argv[])
{
  char from[1000] = {'a'};
  char to[1000] = {'c'};
  int rc = 0;

  // setup the from to have some stuff
  memset(from, 'x', 1000);
  // set it to a failure
  memset(to, 'y', 1000);
  check(valid_copy(to, 1000, 'y'), "Not initialized right.");

  clock_t start, finish;

  // use normal copy to
  start = clock();
  rc = normal_copy(from, to, 1000);
  finish = clock();
  check(rc == 1000, "Normal copy failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Normal copy failed.");
  printf("normal copy took %f seconds to execute.\n",
	 ((double) (finish - start)) / CLOCKS_PER_SEC );
  
  // reset
  memset(to, 'y', 1000);

  // duffs version
  start = clock();
  rc = duffs_device(from, to, 1000);
  finish = clock();
  check(rc == 1000, "Duff's device failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Duff's device failed.");
  printf("duff copy took %f seconds to execute.\n",
	 ((double) (finish - start)) / CLOCKS_PER_SEC );

  // reset
  memset(to, 'y', 1000);

  // my version
  start = clock();
  rc = zeds_device(from, to, 1000);
  finish = clock();
  check(rc == 1000, "Zed's device failed: %d", rc);
  check(valid_copy(to, 1000, 'x'), "Zed's device failed.");
  printf("zeds copy took %f seconds to execute.\n",
	 ((double) (finish - start)) / CLOCKS_PER_SEC );

  return 0;

 error:
  return 1;
}
