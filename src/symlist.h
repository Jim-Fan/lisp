#ifndef _LISP_SYMLIST_
#define _LISP_SYMLIST_

#include <stdio.h>
#include "cell.h"

cell* ENV = NULL;

void symlist_init();
void symlist_cleanup();
cell* symlist_get(char*);
//cell* symlist_put(char*, cell*);

////////////////////////////////////////////////////////////


cell* symlist_get(char* sym)
{
  if (ENV == NULL) return NULL;

  cell* get = ENV;
  while (get != NULL)
  {
    if (strcmp(sym, (char*)get->car->car) == 0) {
      return get->car->cdr;
    }
    get = get->cdr;
  }

  // not found
  return NULL;
}

void symlist_cleanup()
{
  if (ENV == NULL) return;

  cell* del = ENV;
  int d = 0;
  while (del != NULL)
  {
    ENV = del->cdr;

    // del->car is symbol name-val entry

    // name
    free((char*) del->car->car);

    // val
    free_cell((cell*) del->car->cdr);

    free(del);
    ++d;
    del = ENV;
  }

  if (ENV != NULL) {
    printf("symlist_cleanup: ENV is not null\n");
  }
  printf("symlist_cleanup: %d backbone nodes deleted\n", d);
}

void symlist_init()
{
  char c[] = "a";
  int i = 1;

  cell* backbone = NULL;
  cell* child = NULL;

  // everything is null

  backbone = new_cell('Z', NULL, NULL);
  child = new_cell('z', strdup(c), new_cell('I', i++, NULL));

  backbone->car = child;

  // backbone has one child node

  ENV = backbone;

  // now ENV and backbone is the head

  c[0] += 1;

  // symbol name becomes "b";

  while (c[0] <= 'z')
  {
    // ENV and backbone point to 1st node

    backbone->cdr = new_cell('Z', NULL, NULL);

    child = new_cell('z', strdup(c), new_cell('I', i++, NULL));

    // child at new symbol entry

    backbone->cdr->car = child;

    // 2nd node has symbol entry fixed

    backbone = backbone->cdr;

    // backbone at 2nd node now

    c[0] += 1;

    // goto next symbol name
  }
}

#endif
