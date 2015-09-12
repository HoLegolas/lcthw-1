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
Exercise 34 - Dynamic Array
*/

#ifndef __DARRAY_H
#define __DARRAY_H

#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

typedef struct DArray {
  int end;
  int max;
  size_t element_size;
  size_t expand_rate;
  void **contents;
} DArray;

DArray *DArray_create(size_t element_size, size_t initial_max);

void DArray_destroy(DArray *array);

void DArray_clear(DArray *array);

int DArray_expand(DArray *array);

int DArray_contract(DArray *array);

int DArray_push(DArray *array, void *el);

void *DArray_pop(DArray *array);

void DArray_clear_destroy(DArray *array);

#define DArray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 300

static inline void DArray_set(DArray *array, int i, void *el)
{
  check(i < array->max, "darray attempt to set past max");
  if(i > array->end) array->end = i;
  array->contents[i] = el;
 error:
  return;
}

static inline void *DArray_get(DArray *array, int i)
{
  check(i < array->max, "darray attempt to get past max");
  return array->contents[i];
 error:
  return NULL;
}

static inline void *DArray_remove(DArray *array, int i)
{
  check(array, "darray is NULL");
  check(i <= array->end, "darray attempt to remove past max");
  void *el = array->contents[i];
  array->contents[i] = NULL;
  return el;
 error:
  return NULL;
}

static inline void *DArray_new(DArray *array)
{
  check(array->element_size > 0, "Can't use DArray_new on 0 size darrays.");
  return calloc(1, array->element_size);
 error:
  return NULL;
}

#define DArray_free(E) free((E))

#endif /* __DARRAY_H */
