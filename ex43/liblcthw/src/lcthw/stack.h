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
Exercise 42 : Stacks and Queues
*/

#ifndef __STACK_H
#define __STACK_H

#include <lcthw/list.h>

#define Stack List
#define Stack_create() List_create()
#define Stack_destroy(S) List_destroy(S)
#define Stack_push(S,V) List_push(S,V)
#define Stack_pop(S) List_pop(S)
#define Stack_peek(S) List_last(S)
#define Stack_count(S) List_count(S)
#define STACK_FOREACH(S, V) LIST_FOREACH(S, last, prev, V)


#endif /* __STACK_H */
