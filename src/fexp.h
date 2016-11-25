#ifndef _LIST_FEXP_
#define _LISP_FEXP_

#include <stdarg.h>
#include <stdio.h>
#include "cell.h"
#include "oblist.h"

cell* eval(cell*, void*);
cell* apply(cell*, cell*);
cell* quote(cell*);
cell* setq(cell*);

////////////////////////////////////////////////////////////////

cell* eval(cell* c, void* env)
{
  if (c == NULL) return NULL;

  cell *value, *first, *butfirst, *f;
  char* name = NULL;

  switch (c->type)
  {
      // OBLIST item
    case '0':
      value = c;
      break;

      // others
    case 'I':
      value = c;
      break;

    case 'S':
      name = (char*) c->car;
      value = NULL;
      if (value == NULL) {
        value = oblist_lookup(name);
      }
      if (value == NULL) {
        fprintf(stderr, "eval: unbound symbol '%s'\n", name);
        return NIL;
      }
      else {
	return value;
      }
      break;

    case 'L':
      //printf("eval_cell: type L cell, return dummy NIL\n");
      //value = NIL;

      /* To eval an expression is more subtle and deserves some
	 elaboration:

	 Below snippet is faulty. Consider expression to be
	 eval:

	    ( eval 3 )
	 => apply[ eval, (3) ]
	 => apply[ eval, apply[ 3, [] ] ]

	 which causes atom 3 being eval as applicable. The
	 correct way should instead be:

	    ( eval 3 )
	 => apply[ eval, apply[ eval, 3 ] ]
	 => apply[ eval, eval[3] ]
	 => apply[ eval, 3 ]
	 => eval[3]
	 => 3

	 The prime difference lies in how to handle arg list:

	   ( f x y z )
	 => apply [
              f,
              eval[x],
              eval[y],
              eval[z]
	    ]

         instead of:

         => apply[
              f,
              eval[ ( x y z) ]
            ]
         => apply[
              f,
              apply[ x, eval[ ( y z ) ] ]
            ]
       */

      // Refer above, this is the wrong way
      //first = eval(c->car, env);
      //butfirst = eval(c->cdr, env);
      //value = apply(first, butfirst, env);

      // As part of eval, according to to LISP 1.5 manual, it should
      // handle some "function" internally:
      //
      //     QUOTE
      //     FUNCTION
      //     COND
      //     PROG

      // And how about eval itself, and apply?

      // Case 1 - First 'thing' in list is atom
      //
      // i)  FEXP (quote, eval, apply...etc)
      // ii) Symbol bound to function
      if (c->car->type == 'S')
      {
	name = (char*)c->car->car;

	// "FEXPS" (non-evaluating functions)
	if (strcmp(name, "QUOTE") == 0) return quote(c);
	if (strcmp(name, "EVAL") == 0) return eval(c->cdr, env);
	if (strcmp(name, "SETQ") == 0) return setq(c->cdr);

	f = eval(c->car, env);
      }

      // Basic protection
      if (f->type != 'F')
      {
	fprintf(stderr,
		"eval: symbol '%s' is not applicable\n",
		(char*)c->car->car);
	return NIL;
      }

      // Eval each parameter in place
      butfirst = c->cdr;
      for (first = butfirst; first != NIL && first != NULL; first=first->cdr)
      {
	first->car = eval(first->car, env);
      }
	
      // The same issue will happen:
      //value = apply(first, butfirst, env);
	
      // Results in:
      //     apply[ eval, (12) ] => apply[ eval, apply[12] ] ...

      // It appears there's need to re-write apply as:
      //     apply(cell* f, void* env, va_list args)
      // and so as all built-in functions.
      return apply(f, butfirst);

      fprintf(stderr, "eval: unable to eval expression\n");
      return NIL;
      break;

    case 'F':
      value = c;
      break;

    default:
      fprintf(stderr, "eval: reach default branch, cell type: %c\n", c->type);
      value = NIL;
  }

  return value;
}

//////////////////////////////////////////////////////////////////////


cell* apply(cell* f, cell* args)
{
  if (f->type == 'F') {
    cell* (*f_ptr) (cell*);
    f_ptr = f->cdr;

    return f_ptr(args); // wrong, should be f_ptr(args[0], args[1] ... args[n])
  }
  else {
    fprintf(stderr, "apply: error, cell type '%c' not applicable", f->type);
  }

  fprintf(stderr, "apply: return last-resort NIL\n");
  return NIL;
}

//////////////////////////////////////////////////////////////////////


/*
  Example: (quote 13)
        => quote[13]
        => 13

  If (quote 13) is treated a list, the action is to take out the 2nd
  element from this list and return it.
*/
cell* quote(cell* c)
{
  // Exactly one argument
  if (c->cdr != NULL && c->cdr != NIL && c->cdr->car != NULL) {
    return c->cdr->car;
  }
  else {
    fprintf(stderr, "quote: require one argument\n");
  }
}

//////////////////////////////////////////////////////////////////////

// (setq x 10) => setq[x, 10] => 10
cell* setq(cell* c)
{
  if (c == NULL) {
    fprintf(stderr, "setq: expect two argument\n");
    return NIL;
  }

  if (c->car->type != 'S') {
    fprintf(stderr, "setq: first argument is not literal atom\n");
    return NIL;
  }

  if (c->cdr == NULL || c->cdr == NIL || c->cdr->car == NULL) {
    fprintf(stderr, "setq: expect two argument\n");
    return NIL;
  }

  char* name = c->car->car;
  return oblist_put(name, c->cdr->car);
}

#endif
