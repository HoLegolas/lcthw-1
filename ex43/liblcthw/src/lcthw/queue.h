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

#ifndef __QUEUE_H
#define __QUEUE_H

#include <lcthw/list.h>

#define Queue List
#define Queue_create() List_create()
#define Queue_destroy(Q) List_destroy(Q)
#define Queue_send(Q,V) List_push(Q,V)
#define Queue_recv(Q) List_shift(Q)
#define Queue_peek(Q) List_first(Q)
#define Queue_count(Q) List_count(Q)
#define QUEUE_FOREACH(Q, V) LIST_FOREACH(Q, first, next, V)


#endif /* __QUEUE_H */
