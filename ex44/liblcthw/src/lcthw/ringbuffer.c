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
Exercise 44 : Ring Buffers
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lcthw/dbg.h>
#include <lcthw/ringbuffer.h>

RingBuffer *RingBuffer_create(int length)
{
  RingBuffer *buffer = calloc(1, sizeof(RingBuffer));
  buffer->length = length + 1;
  buffer->start = 0;
  buffer->end = 0;
  buffer->buffer = calloc(buffer->length, 1);

  return buffer;
}

void RingBuffer_destroy(RingBuffer *buffer)
{
  if(buffer) {
    free(buffer->buffer);
    free(buffer);
  }
}

int RingBuffer_write(RingBuffer *buffer, char *data, int length)
{
  if(RingBuffer_available_data(buffer) == 0) {
    buffer->start = buffer->end = 0;
  }

  check(length <= RingBuffer_available_space(buffer),
	"Not enough space: %d request, %d available",
	RingBuffer_available_data(buffer), length);

  void *result = memcpy(RingBuffer_ends_at(buffer), data, length);
  check(result != NULL, "Failed to write data into buffer.");

  RingBuffer_commit_write(buffer, length);

  return length;

 error:
  return -1;
}

int RingBuffer_read(RingBuffer *buffer, char *target, int amount)
{
  check_debug(amount <= RingBuffer_available_data(buffer),
	      "Not enough in the buffer: has %d, needs %d",
	      RingBuffer_available_data(buffer), amount);

  void *result = memcpy(target, RingBuffer_starts_at(buffer), amount);
  check(result != NULL, "Failed to write buffer into target.");

  RingBuffer_commit_read(buffer, amount);

  if(buffer->end == buffer->start) {
    buffer->start = buffer->end = 0;
  }

  return amount;

 error:
  return -1;
}

bstring RingBuffer_gets(RingBuffer *buffer, int amount)
{
  check(amount > 0, "Need more than 0 for gets, you have: %d", amount);
  check_debug(amount <= RingBuffer_available_data(buffer),
	      "Not enough in the buffer");

  bstring result = blk2bstr(RingBuffer_starts_at(buffer), amount);
  check(result != NULL, "Failed to create gets result.");
  check(blength(result) == amount, "Wrong result length.");

  RingBuffer_commit_read(buffer, amount);
  assert(RingBuffer_available_data(buffer) >= 0 && "Error in read commit");

  return result;

 error:
  return NULL;
}
