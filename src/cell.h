#ifndef _LISP_LIST_
#define _LISP_LIST_

//typedef struct llist;
//typedef cell;

typedef struct _cell
{
  char type;
  struct _cell* car;
  struct _cell* cdr;
} cell;

cell* new_cell(char type, void* car, cell* cdr)
{
  cell* c = (cell*)malloc(sizeof(cell));
  c->type = type;
  c->car = (cell*) car;
  c->cdr = cdr;
  return c;
}

#endif
