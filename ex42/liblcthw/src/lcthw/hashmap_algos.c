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
Exercise 38 : Hashmap algorithms
*/

#include <lcthw/hashmap_algos.h>
#include <lcthw/bstrlib.h>

// settings taken from
// http://www.isthe.com/chongo/tech/comp/fnv/index.html#FNV-param
const uint32_t FNV_PRIME = 16777619;
const uint32_t FNV_OFFSET_BASIS = 2166136261LL;
// If you don't put LL at the end of the decimal, you get the following gcc warning :
// warning: this decimal constant is unsigned only in ISO C90
// See this URL about the LL trick :
// http://stackoverflow.com/questions/9941261/warning-this-decimal-constant-is-unsigned-only-in-iso-c90

uint32_t Hashmap_fnv1a_hash(void *data)
{
  bstring s = (bstring)data;
  uint32_t hash = FNV_OFFSET_BASIS;
  int i = 0;

  for(i = 0; i < blength(s); i++) {
    hash ^= bchare(s, i, 0);
    hash *= FNV_PRIME;
  }

  return hash;
}

const int MOD_ADLER = 65521;

uint32_t Hashmap_adler32_hash(void *data)
{
  bstring s = (bstring)data;
  uint32_t a = 1, b = 0;
  int i = 0;

  for(i = 0; i < blength(s); i++) {
    a = (a + bchare(s, i, 0)) % MOD_ADLER;
    b = (b + a) % MOD_ADLER;
  }

  return (b << 16) | a;
}

uint32_t Hashmap_djb_hash(void *data)
{
  bstring s = (bstring)data;
  uint32_t hash = 5381;
  int i = 0;

  for(i = 0; i < blength(s); i++) {
    hash = ((hash << 5) + hash) + bchare(s, i, 0); /* hash * 33 + c */
  }

  return hash;
}


