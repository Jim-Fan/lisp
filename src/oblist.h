#ifndef _LISP_OBLIST_
#define _LISP_OBLIST_

#include <string.h>
#include "cell.h"

/*
  Reference: http://jeffshrager.org/llisp/27.html

  All literal atoms, including the built-in atoms (T, NIL, and the built-in
  functions), are organized into a single list within the workspace, called
  the OBLIST. Literal atoms are always unique; for some atom A, there can
  be only one instance of A in the workspace. All references to this atom 
  are pointers to the single location where A resides. Numeric atoms, 
  however, are not unique; there can be any number of instances of a given
  numeric value.
*/

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

  for (c = OBLIST; c != NULL; c=c->cdr) {
    printf("oblist_init: %s @ 0x%08x\n",
      (char*)c->car->car,
      c->car);
  }
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
