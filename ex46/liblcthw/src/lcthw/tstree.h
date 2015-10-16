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
Exercise 45 : Ternary Search Tree
*/

#ifndef __TSTREE_H
#define __TSTREE_H

#include <stdlib.h>
#include <lcthw/darray.h>

typedef struct TSTree {
  char splitchar;
  struct TSTree *low;
  struct TSTree *equal;
  struct TSTree *high;
  void *value;
} TSTree;

void *TSTree_search(TSTree *root, const char *key, size_t len);

void *TSTree_search_prefix(TSTree *root, const char *key, size_t len);

typedef void (*TSTree_traverse_cb)(void *value, void *data);

TSTree *TSTree_insert(TSTree *node, const char *key, size_t len, void *value);

void TSTree_traverse(TSTree *node, TSTree_traverse_cb cb, void *data);

void TSTree_destroy(TSTree *root);

#endif /* __TSTREE_H */
