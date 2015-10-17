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
Exercise 46 : Ternary Search Tree
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <lcthw/dbg.h>
#include <lcthw/tstree.h>

static inline TSTree *TSTree_insert_base(TSTree *root, TSTree *node,
					 const char *key,
					 size_t len,
					 void *value)
{
  if(node == NULL) {
    node = (TSTree *) calloc(1, sizeof(TSTree));

    if(root == NULL) {
      root = node;
    }

    node->splitchar = *key;
  }

  if(*key < node->splitchar) {
    node->low = TSTree_insert_base(root, node->low, key, len, value);
  } else if(*key == node->splitchar) {
    if(len > 1) {
      node->equal = TSTree_insert_base(root, node->equal, key+1, len-1, value);
    } else {
      assert(node->value == NULL && "Duplicate insert into tst.");
      node->value = value;
    }
  } else {
    node->high = TSTree_insert_base(root, node->high, key, len, value);
  }

  return node;
}

TSTree *TSTree_insert(TSTree *node, const char *key, size_t len, void *value)
{
  return TSTree_insert_base(node, node, key, len, value);
}
