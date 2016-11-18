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

cell* NIL = (cell*) NULL;

///////////////////////////////////////////////////////////

void cell_init()
{
  NIL = (cell*)malloc(sizeof(cell));
  NIL->type = '0';
  NIL->car = NULL;
  NIL->cdr = NULL;

  printf("cell_init: sizeof(cell*) = %d\n", sizeof(cell*));
  printf("cell_init: sizeof(cell) = %d\n", sizeof(cell));
  printf("cell_init: NIL @ %08x\n", NIL);
}

void cell_cleanup()
{
  if (NIL != NULL) free(NIL);
}

///////////////////////////////////////////////////////////

cell* new_cell(char type, cell* car, cell* cdr)
{
  /*
  if (type=='L' && car==NULL && cdr ==NULL)
    return NULL;
  */

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

  switch (c->type)
  {
    //case '0':

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
