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
Exercise 8
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
  char full_name[] = {
    'Z', 'e', 'd',
    ' ', 'A', '.', ' ',
    'S', 'h', 'a', 'w', '\0'
  };
  int areas[] = { 10, 12, 13, 14, 20 };
  char name[] = "Zed";

  // Warning: on some systems you may have to change the %ld in this
  // code to a %u since it will use unsigned ints
  printf("The size of an int is %u.\n", sizeof(int));
  printf("The size of areas (int[]): %u\n", sizeof(areas));
  printf("The number of ints in areas: %u\n", sizeof(areas) / sizeof(int));
  printf("The first area is %d, the 2nd is %d.\n", areas[0], areas[1]);
  printf("The size of a char: %u\n", sizeof(char));
  printf("The size of name: %u\n", sizeof(name));
  printf("The number of chars: %u\n", sizeof(name) / sizeof(char));
  printf("The size of full_name (char[]): %u\n", sizeof(full_name));
  printf("The number of chars: %u\n", sizeof(full_name) / sizeof(char));
  printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

  return 0;
}
