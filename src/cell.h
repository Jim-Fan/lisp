#ifndef _LISP_LIST_
#define _LISP_LIST_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
  // car and cdr part of NIL is still NIL => NIL is list
  NIL = (cell*)malloc(sizeof(cell));
  NIL->type = '0';    // 0 => constant => won't be free
  NIL->car = "NIL";
  NIL->cdr = NIL;

  // on contrary T is not list
  T = (cell*)malloc(sizeof(cell));
  T->type = '0';      // 0 => constant => won't be free
  T->car = "T";
  T->cdr = NIL;

  printf("cell_init: sizeof(int) = %d\n", sizeof(int));
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


cell* new_cell(char type, cell* car, cell* cdr)
{
  // For symbol, lookup from OBLIST, create if not exist
  if (type == 'S')
  {
    char* name = (char*)car;

    while (*name != '\0') {
      *name = toupper(*name);
      ++name;
    }

    //name = (char*)car;
    //cell* ob = oblist_lookup(name);
    //if (ob != NULL) return ob;
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
