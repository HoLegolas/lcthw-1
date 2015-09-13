/*-*- coding: utf-8 -*-

 Copyright (c) 2015 Jérôme Radix <jerome.radix@gmail.com>

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

#include <lcthw/dbg.h>
#include <lcthw/bstree.h>
#include <stdlib.h>
#include <lcthw/bstrlib.h>

static int default_compare(void *a, void *b)
{
  return bstrcmp((bstring) a, (bstring) b);
}

BSTree *BSTree_create(BSTree_compare compare)
{
  BSTree *map = calloc(1, sizeof(BSTree));
  check_mem(map);

  map->compare = compare == NULL ? default_compare : compare;

  return map;

 error:
  if(map) {
    BSTree_destroy(map);
  }
  return NULL;
}

static int BSTree_destroy_cb(BSTreeNode *node)
{
  free(node);
  return 0;
}

void BSTree_destroy(BSTree *map)
{
  if(map) {
    BSTree_traverse(map, BSTree_destroy_cb);
    free(map);
  }
}

static inline BSTreeNode *BSTreeNode_create(BSTreeNode *parent, void *key, void *data)
{
  BSTreeNode *node = calloc(1, sizeof(BSTreeNode));
  check_mem(node);

  node->key = key;
  node->data = data;
  node->parent = parent;
  return node;

 error:
  return NULL;
}

static inline void BSTree_setnode(BSTree *map, BSTreeNode *node, void *key, void *data)
{
  int cmp = map->compare(node->key, key);

  if(cmp <= 0) {
    if(node->left) {
      BSTree_setnode(map, node->left, key, data);
    } else {
      node->left = BSTreeNode_create(node, key, data);
    }
  } else {
    if(node->right) {
      BSTree_setnode(map, node->right, key, data);
    } else {
      node->right = BSTreeNode_create(node, key, data);
    }
  }
}

int BSTree_set(BSTree *map, void *key, void *data)
{
  if(map->root == NULL) {
    // first so just make it and get out
    map->root = BSTreeNode_create(NULL, key, data);
    check_mem(map->root);
  } else {
    BSTree_setnode(map, map->root, key, data);
  }

  return 0;

 error:
  return -1;
}

