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

#ifndef __STATS_H
#define __STATS_H

typedef struct Stats {
  double sum;
  double sumsq;
  unsigned long n;
  double min;
  double max;
} Stats;

Stats *Stats_recreate(double sum,
		      double sumsq,
		      unsigned long n,
		      double min,
		      double max);

Stats *Stats_create();

double Stats_mean(Stats *st);

double Stats_stddev(Stats *st);

void Stats_sample(Stats *st, double s);

void Stats_dump(Stats *st);

#endif /* __STATS_H */
