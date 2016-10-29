#ifndef _LISP_SYMLIST_
#define _LISP_SYMLIST_

#include "cell.h"

cell* ENV = NULL;

void symlist_init();
//void symlist_cleanup();
//cell* symlist_get(char*);
//cell* symlist_put(char*, cell*);

////////////////////////////////////////////////////////////


void symlist_init()
{
  char* c = "a";
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

  while (c[0] < 'z')
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
