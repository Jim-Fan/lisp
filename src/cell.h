#ifndef _LISP_LIST_
#define _LISP_LIST_

#include <stdlib.h>

//typedef struct llist;
//typedef cell;

typedef struct _cell
{
  char type;
  struct _cell* car;
  struct _cell* cdr;
} cell;

cell* new_cell(char type, void* car, void* cdr)
{
  cell* c = (cell*)malloc(sizeof(cell));
  c->type = type;
  c->car = (cell*) car;
  c->cdr = (cell*) cdr;
  return c;
}

void free_cell(cell* c)
{
  if (c == NULL) return; 
  switch (c->type)
  {
    case 'I': break;

    case 'S':
      if (c->car != NULL) free((char*) c->car);
      break;

    case 'L':
      if (c->car != NULL) free_cell(c->car);
      if (c->cdr != NULL) free_cell(c->cdr);
      break;
  }
  free(c);
  return;
}

#endif
