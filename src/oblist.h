#ifndef _LISP_OBLIST_
#define _LISP_OBLIST_

#include <string.h>
#include "cell.h"
#include "op.h"

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
  cell* c = (cell*)malloc(sizeof(cell));
  OBLIST = c;

  c->type = 'B';
  c->car = new_cell('S', strdup("NIL"), NIL); // leave (name-value pair)
  c->cdr = (cell*)malloc(sizeof(cell));  // stem
  c = c->cdr;

  c->type = 'B';
  c->car = new_cell('S', strdup("T"), T); // leave (name-value pair)
  c->cdr = (cell*)malloc(sizeof(cell));  // stem
  c = c->cdr;

  c->type = 'B';
  c->car = new_cell('S', strdup("CONS"), &cons);
  c->cdr = (cell*)malloc(sizeof(cell));  // stem
  c = c->cdr;

  c->type = 'B';
  c->car = new_cell('S', strdup("CAR"), &car);
  c->cdr = (cell*)malloc(sizeof(cell));  // stem
  c = c->cdr;

  c->type = 'B';
  c->car = new_cell('S', strdup("CDR"), &cdr);
  c->cdr = (cell*)malloc(sizeof(cell));  // stem
  c = c->cdr;

  c->type = 'B';
  c->car = new_cell('S', strdup("PLUS"), &plus);

  // Terminate OBLIST with NULL:
  // OBLIST is merely a linked list and not s-expression
  c->cdr = NULL;

  oblist_dump();
}

void oblist_dump()
{
  cell*c, *pair;
  for (c = OBLIST; c != NULL; c=c->cdr)
  {
    pair = c;
    printf("oblist_init: %s @ 0x%08x\n",
	   (char*)pair->car->car,
	   c->car);
  }
}

///////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////

cell* oblist_put(char* name, cell* c)
{
  cell* head = (cell*)malloc(sizeof(cell));
  head->type = 'B';
  head->car = new_cell('L', name, c);
  head->cdr = OBLIST;

  OBLIST = head;

  return c;
}

#endif
