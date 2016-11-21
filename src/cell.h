#ifndef _LISP_LIST_
#define _LISP_LIST_

#include <stdio.h>
#include <stdlib.h>

//typedef struct llist;
//typedef cell;

typedef struct _cell
{
  char type;
  struct _cell* car;
  struct _cell* cdr;
} cell;

cell* T = (cell*) NULL;
cell* NIL = (cell*) NULL;

///////////////////////////////////////////////////////////

cell* new_cell(char,cell*,cell*);

void cell_init()
{
  NIL = (cell*)malloc(sizeof(cell));
  NIL->type = '0';
  NIL->car = "NIL";
  NIL->cdr = NULL;

  T = (cell*)malloc(sizeof(cell));
  T->type = '0';
  T->car = "T";
  T->cdr = NULL;

  printf("cell_init: sizeof(cell*) = %d\n", sizeof(cell*));
  printf("cell_init: sizeof(cell)  = %d\n", sizeof(cell));
  printf("cell_init: T   @ 0x%08x\n", T);
  printf("cell_init: NIL @ 0x%08x\n", NIL);
}

void cell_cleanup()
{
  if (NIL != NULL)
  {
    free(NIL);
    NIL = NULL;
  }
  if (T != NULL)
  {
    free(T);
    T = NULL;
  }
}

///////////////////////////////////////////////////////////

// Can't include oblist.h, otherwise recursion
cell* oblist_lookup(char*);

cell* new_cell(char type, cell* car, cell* cdr)
{
  // For symbol, lookup from OBLIST, create if not exist
  if (type == 'S')
  {
    char* name = (char*)car;
    cell* ob = oblist_lookup(name);
    if (ob != NULL) return ob;
  }

  cell* c = (cell*)malloc(sizeof(cell));
  c->type = type;
  c->car = car;
  c->cdr = cdr;
  return c;
}

void free_cell(cell* c)
{
  if (c == NULL) return;

  if (c == NIL) return;

  // free by cell_cleanup, ignored
  if (c->type == '0') return;

  // free by fexp, ignored
  if (c->type == 'F') return;

  switch (c->type)
  {
    case 'I':
      break;

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
