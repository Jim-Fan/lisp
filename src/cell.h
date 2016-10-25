#ifndef _LISP_LIST_
#define _LISP_LIST_

//typedef struct llist;

typedef struct cell
{
  struct cell* car;
  struct cell* cdr;
} cell;

cell* new_cell(cell* car, cell* cdr)
{
  cell* c = (cell*)malloc(sizeof(cell));
  c->car = car;
  c->cdr = cdr;
  return c;
}

#endif
