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
Exercise 26 - devpkg
*/

#include <unistd.h>
#include <apr_errno.h>
#include <apr_file_io.h>

#include "db.h"
#include "bstrlib.h"
#include "dbg.h"

static FILE *DB_open(const char *path, const char *mode)
{
  return fopen(path, mode);
}

static void DB_close(FILE *db)
{
  fclose(db);
}

static bstring DB_load()
{
  FILE *db = NULL;
  bstring data = NULL;

  db = DB_open(DB_FILE, "r");
  check(db, "Failed to open database: %s", DB_FILE);

  data = bread((bNread) fread, db);
  check(data, "Failed to read from db file: %s", DB_FILE);

  DB_close(db);
  return data;

 error:
  if(db) DB_close(db);
  if(data) bdestroy(data);
  return NULL;
}

int DB_update(const char *url)
{
  if(DB_find(url)) {
    log_info("Already recorded as installed: %s", url);
  }

  FILE *db = DB_open(DB_FILE, "a+");
  check(db, "Failed to open DB file: %s", DB_FILE);

  bstring line = bfromcstr(url);
  bconchar(line, '\n');
  int rc = fwrite(line->data, blength(line), 1, db);
  check(rc == 1, "Failed to append to the db.");

  return 0;

 error:
  if(db) DB_close(db);
  return -1;
}

int DB_find(const char *url)
{
  bstring data = NULL;
  bstring line = bfromcstr(url);
  int res = -1;

  data = DB_load();
  check(data, "Failed to load: %s", DB_FILE);

  if(binstr(data, 0, line) == BSTR_ERR) {
    res = 0;
  } else {
    res = 1;
  }

 error: // fallthrough
  if(data) bdestroy(data);
  if(line) bdestroy(data);

  return res;
}

int DB_init()
{
  apr_pool_t *p = NULL;
  apr_pool_initialize();
  apr_pool_create(&p, NULL);

  if(access(DB_DIR, W_OK | X_OK) == -1) {
    apr_status_t rc = apr_dir_make_recursive(DB_DIR,
					     APR_UREAD | APR_UWRITE | APR_UEXECUTE |
					     APR_GREAD | APR_GWRITE | APR_GEXECUTE, p);
    check(rc == APR_SUCCESS, "Failed to make database dir: %s", DB_DIR);
  }

  if(access(DB_FILE, W_OK) == -1) {
    FILE *db = DB_open(DB_FILE, "w");
    check(db, "Cannot open database: %s", DB_FILE);
    DB_close(db);
  }

  apr_pool_destroy(p);
  return 0;

 error:
  apr_pool_destroy(p);
  return -1;
}

int DB_list()
{
  bstring data = DB_load();
  check(data, "Failed to read load: %s", DB_FILE);

  printf("%s", bdata(data));
  bdestroy(data);
  return 0;

 error:
  return -1;
}
