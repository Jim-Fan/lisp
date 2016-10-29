#ifndef _LISP_EVAL_
#define _LISP_EVAL_

#include <stdio.h>
#include <string.h>
#include "symlist.h"

cell* eval(cell* c, cell* env)
{
  // (eval NIL) => NIL
  if (c == NULL) return NULL;

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
      return symlist_get(c->car);
      break;

    // (eval (quote 10))
    case 'L':
      printf("apply( eval( car(%x)=%x, cdr(%x)=%x )\n",
        c,
        c->car,
        c,
        c->cdr);
      return NULL;
  }

  printf("eval: warning, should not reach end of switch\n");
  return NULL;
}

#endif
