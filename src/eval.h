#ifndef _LISP_EVAL_
#define _LISP_EVAL_

#include <stdio.h>
#include <string.h>
#include "symlist.h"
#include "fexp.h"

cell* eval(cell* c, cell* env)
{
  // (eval NIL) => NIL
  if (c == NULL) return NULL;

  cell* fexp = NULL;
  cell* result = NULL;

  switch (c->type)
  {
    // An int is an int
    // e.g. (eval 99) => 99
    //      (eval (eval (eval 100 ))) => 100
    case 'I':
      return c;

    // Look up symbol table
    // e.g. (eval s) => fetch symlist of name s
    // Problem: (eval undefined) => NIL
    case 'S':
      //printf("eval: symbol '%s' not found\n", (char*)c->car);
      result = fexp_get(c->car);
      if (result != NULL) return result;
      return symlist_get(c->car);
      break;

    // (eval (quote (2 4 6)))
    case 'L':
      /*
      printf("apply( eval( car(%x)=%x, cdr(%x)=%x )\n",
        c,
        c->car,
        c,
        c->cdr);
      */

      // 1st node is atom, get function pointer from it
      if (c->car->type = 'S') {
        fexp = fexp_get((char*)c->car->car);
        if (fexp != NULL) {
          cell* (*f)(cell*,cell*) = fexp->cdr;
          return (*f)(c->cdr, env);
        }
      }
      printf("eval: no matching callable found\n");
      return NULL;
  }

  printf("eval: warning, should not reach end of switch\n");
  return NULL;
}

#endif
