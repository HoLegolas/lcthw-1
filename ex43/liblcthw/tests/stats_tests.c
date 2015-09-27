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

char *test_operations()
{
  int i = 0;
  Stats *st = Stats_create();
  mu_assert(st != NULL, "Failed to create stats.");

  for (i = 0; i < NUM_SAMPLES; i++) {
    Stats_sample(st, samples[i]);
  }

  Stats_dump(st);

  mu_assert(EQ(st->sumsq, expect.sumsq, 3), "sumsq not valid");
  mu_assert(EQ(st->sum, expect.sum, 3), "sum not valid");
  mu_assert(EQ(st->min, expect.min, 3), "min not valid");
  mu_assert(EQ(st->max, expect.max, 3), "max not valid");
  mu_assert(EQ(st->n, expect.n, 3), "n not valid");
  mu_assert(EQ(expect_mean, Stats_mean(st), 3), "mean not valid");
  mu_assert(EQ(expect_stddev, Stats_stddev(st), 3), "stddev not valid");

  Stats_destroy(st);

  return NULL;
}

char *test_recreate()
{
  Stats *st = Stats_recreate(expect.sum, expect.sumsq, expect.n, expect.min, expect.max);

  mu_assert(st->sum == expect.sum, "sum not equal");
  mu_assert(st->sumsq == expect.sumsq, "sumsq not equal");
  mu_assert(st->n == expect.n, "n not equal");
  mu_assert(st->min == expect.min, "min not equal");
  mu_assert(st->max == expect.max, "max not equal");
  mu_assert(EQ(expect_mean, Stats_mean(st), 3), "mean not equal");
  mu_assert(EQ(expect_stddev, Stats_stddev(st), 3), "stddev not equal");

  Stats_destroy(st);

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_operations);
  mu_run_test(test_recreate);

  return NULL;

}

RUN_TESTS(all_tests);
