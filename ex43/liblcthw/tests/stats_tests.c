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
Exercise 43 : A simple statistics engine

R session :

> s <- runif(n=10, max=10)
> s
 [1] 6.7891378 3.6256222 9.3556922 5.8161826 0.9628356 8.0894781 3.3153268
 [8] 3.1307407 2.9453734 4.5354535
> summary(s)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max. 
 0.9628  3.1770  4.0810  4.8570  6.5460  9.3560 
> sd(s)
[1] 2.606308
> sum(s)
[1] 48.56584
> sum(s*s)
[1] 296.9997
> sum(s) * mean(s)
[1] 235.8641
> sum(s*s) - sum(s) * mean(s)
[1] 61.13558
> (sum(s*s) - sum(s) * mean(s)) / (length(s) - 1)
[1] 6.792842
> sqrt((sum(s*s) - sum(s) * mean(s)) / (length(s) - 1))
[1] 2.606308

*/

#include "minunit.h"
#include <lcthw/stats.h>
#include <math.h>

const int NUM_SAMPLES = 10;
double samples[] = { 6.7891378, 3.6256222, 9.3556922, 5.8161826, 0.9628356,
		     8.0894781, 3.3153268, 3.1307407, 2.9453734, 4.5354535 };

Stats expect = {
  .sumsq = 296.9997,
  .sum = 48.56584,
  .min = 0.9628,
  .max = 9.3560,
  .n = 10
};

double expect_mean = 4.8570;
double expect_stddev = 2.606308;

#define EQ(X,Y,N) (round((X) * pow(10,N)) == round((Y) * pow(10,N)))
