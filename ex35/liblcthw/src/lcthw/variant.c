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
Exercise 35 - Sorting and Searching
*/

#include <stdio.h>

typedef enum {
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_STRING,
} VariantType;

struct Variant {
  VariantType type;
  union {
    int as_integer;
    float as_float;
    char *as_string;
  } data;
};

typedef struct Variant Variant;

void Variant_print(Variant *var)
{
  switch(var->type) {
  case TYPE_INT:
    printf("INT: %d\n", var->data.as_integer);
    break;
  case TYPE_FLOAT:
    printf("FLOAT: %f\n", var->data.as_float);
    break;
  case TYPE_STRING:
    printf("STRING: %s\n", var->data.as_string);
    break;
  default:
    printf("UNKNOW TYPE: %d\n", var->type);
  }
}

int main(int argc, char *argv[])
{
  Variant a_int = { .type = TYPE_INT, .data.as_integer = 100 };
  Variant a_float = { .type = TYPE_FLOAT, .data.as_float = 100.34 };
  Variant a_string = { .type = TYPE_STRING, .data.as_string = "YO DUDE!" };

  Variant_print(&a_int);
  Variant_print(&a_float);
  Variant_print(&a_string);

  // here's how you access them
  a_int.data.as_integer = 200;
  a_float.data.as_float = 2.345;
  a_string.data.as_string = "Hi there.";

  Variant_print(&a_int);
  Variant_print(&a_float);
  Variant_print(&a_string);

  return 0;
}
