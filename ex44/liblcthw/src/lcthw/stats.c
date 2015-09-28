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
Exercise 43 : a simple statistics engine
*/

#include <math.h>
#include <lcthw/stats.h>
#include <stdlib.h>
#include <lcthw/dbg.h>

Stats *Stats_recreate(double sum,
		      double sumsq,
		      unsigned long n,
		      double min,
		      double max)
{
  Stats *st = malloc(sizeof(Stats));
  check_mem(st);

  st->sum = sum;
  st->sumsq = sumsq;
  st->n = n;
  st->min = min;
  st->max = max;

  return st;

 error:
  return NULL;
}

Stats *Stats_create()
{
  return Stats_recreate(0.0, 0.0, 0L, 0.0, 0.0);
}

void Stats_destroy(Stats *st)
{
  if(st) {
    free(st);
  }
}

double Stats_mean(Stats *st)
{
  return st->sum / st->n;
}

double Stats_stddev(Stats *st)
{
  return sqrt((st->sumsq - (st->sum * st->sum / st->n)) / (st->n - 1));
}

void Stats_sample(Stats *st, double s)
{
  st->sum += s;
  st->sumsq += s * s;

  if(st->n == 0) {
    st->min = s;
    st->max = s;
  } else {
    if(st->min > s) st->min = s;
    if(st->max < s) st->max = s;
  }

  st->n += 1;
}

void Stats_dump(Stats *st)
{
  fprintf(stderr, "sum: %f, sumsq: %f, n: %ld, min: %f, max: %f, mean: %f, stddev: %f",
	  st->sum, st->sumsq, st->n, st->min, st->max,
	  Stats_mean(st), Stats_stddev(st));
}
