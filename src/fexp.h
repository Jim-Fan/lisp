#ifndef _LIST_FEXP_
#define _LIST_FEXP_

#include <stdio.h>
#include "cell.h"
#include "eval.h"
#include "util.h"


// interface:
// cell* func(cell* args, cell* env)

/*

'f'
         -----------         -----------
        |     |     |------>|     |     |
         -----------         -----------
           /
'F':      /
         /
    -----------
   |     |     |
    -----------
     /       \
   "cons"    *func

*/

cell* FEXP = NULL;

// (quote a) => a
// (quote (haha)) => (haha)
// (quote quote) => quote
cell* quote(cell* args, cell* env)
{
  return args;
}

cell* cons(cell* args, cell* env)
{
  if (args == NULL
      ||
      args->car == NULL
      ||
      args->cdr == NULL
      ||
      args->cdr->car == NULL
  ) {
    puts("cons: Too few argument");
  }

  cell* result = new_cell(
                   'L',
                   args->car,
                   args->cdr->car);
  return result;
}


void fexp_init()
{
  cell* quote_fexp = new_cell('F', "quote", &quote);
  cell* cons_fexp  = new_cell('F', "cons", &cons);
  //cell* list_fexp  = new_cell('f', "quote", &list);

  FEXP = new_cell('f',
                  quote_fexp,
                  new_cell('f',
                           cons_fexp,
                           NULL)
                 );

  printf("fexp_init: %d nodes created\n", cell_count(FEXP));
}


cell* fexp_cleanup()
{
  int n = 0;
  cell* head = FEXP;
  cell* next = NULL;
  while (head != NULL)
  {
    next = head->cdr;
    free(head);
    n++;
    head = next;
  }

  printf("fexp_cleanup: %d nodes freed\n", n);
}


cell* fexp_get(char* name) {
  cell* fexp = FEXP;
  while (fexp != NULL)
  {
    if (strcmp((char*) fexp->car->car, name) == 0) {
      return fexp->car;
    }
    fexp = fexp->cdr;
  }
  return NULL;
}

#endif
