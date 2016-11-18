#ifndef _LISP_OBLIST_
#define _LISP_OBLIST_

#include <string.h>
#include "cell.h"


cell* OBLIST = (cell*) NULL;

///////////////////////////////////////////////////////////

void oblist_init()
{
  OBLIST = (cell*)malloc(sizeof(cell));

  cell* c = OBLIST;
  c->type = 'B';
  c->car = NIL;

  c->cdr = (cell*)malloc(sizeof(cell));
  c = c->cdr;
  c->type = 'B';
  c->car = T;

  // Terminate OBLIST with NULL:
  // OBLIST is merely a linked list and not s-expression
  c->cdr = NULL;
}

void oblist_cleanup()
{
  int count = 0;
  cell* head = OBLIST;
  while (head != NULL)
  {
    OBLIST = head->cdr;
    free(head);
    ++count;
    head = OBLIST;
  }

  printf("oblist_cleanup: cleared %d nodes\n", count);
}

///////////////////////////////////////////////////////////

cell* oblist_lookup(char* name)
{
  cell* head = OBLIST;
  while (head != NULL)
  {
    if (strcmp((char*)head->car->car, name) == 0) {
      return head->car;
    }
    head = head->cdr;
  }

  // lookup failed
  return NULL;
}


#endif
