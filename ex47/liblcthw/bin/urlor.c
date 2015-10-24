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
Exercise 47 : A Fast URL Router
*/

#include <lcthw/tstree.h>
#include <lcthw/bstrlib.h>

TSTree *add_route_data(TSTree *routes, bstring line)
{
  struct bstrList *data = bsplit(line, ' ');
  check(data->qty == 2, "Line '%s' does not have two columns", bdata(line));

  routes = TSTree_insert(routes,
			 bdata(data->entry[0]),
			 blength(data->entry[0]),
			 bstrcpy(data->entry[1]));
  bstrListDestroy(data);

  return routes;

 error:
  return NULL;
}

TSTree *load_routes(const char *file)
{
  TSTree *routes = NULL;
  bstring line = NULL;
  FILE *routes_map = NULL;

  routes_map = fopen(file, "r");
  check(routes_map != NULL, "Failed to open routes: %s", file);

  while((line = bgets((bNgetc)fgetc, routes_map, '\n')) != NULL) {
    check(btrimws(line) == BSTR_OK, "Failed to trim line.");
    routes = add_route_data(routes, line);
    check(routes != NULL, "Failed to add route.");
    bdestroy(line);
  }

  fclose(routes_map);
  return routes;

 error:
  if(routes_map) fclose(routes_map);
  if(line) bdestroy(line);
  return NULL;
}

bstring match_url(TSTree *routes, bstring url)
{
  bstring route = TSTree_search(routes, bdata(url), blength(url));

  if(route == NULL) {
    printf("No exact match found, trying prefix.\n");
    route = TSTree_search_prefix(routes, bdata(url), blength(url));
  }

  return route;
}

