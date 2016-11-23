#ifndef _LIST_FEXP_
#define _LISP_FEXP_

#include <stdarg.h>
#include <stdio.h>
#include "cell.h"

cell* fexp_lookup(char*);
cell* apply(cell*,cell*);

////////////////////////////////////////////////////////////////

cell* eval(cell* c, void* env)
{
  if (c == NULL) return NULL;

  cell *value, *first, *butfirst;
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
	value = fexp_lookup(name);
      }
      if (value == NULL) {
        fprintf(stderr, "eval: unbound symbol '%s'\n", name);
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

      // First param is atom
      if (c->car->type == 'S')
      {
	first = c->car;
	name = (char*)c->car;

	// "Built-in" funtors
	if (strcmp(name, "quote") == 0) return c->cdr;
	if (strcmp(name, "eval") == 0) return eval(c->cdr, env);

	// Otherwise (try to) eval first arg as applicable

	// Eval each parameter in place
	butfirst = c->cdr;
	for (first = butfirst; first != NIL && first != NULL; first=first->cdr)
	{
	  first->car = eval(first->car, env);
	}

	// Eval first arg as applicable
	first = eval(c->car, env);

	// Basic protection
	if (first == NULL)
	{
	  fprintf(stderr, "eval: first symbol eval to NULL and is not applicable\n");
	  return NIL;
	}
	else if (first->type != 'F')
	{
	  fprintf(stderr, "eval: symbol eval to non-applicable type\n");
	  return NIL;
	}
	else
	{
	  // The same issue will happen:
	  //value = apply(first, butfirst, env);

	  // Results in:
	  //     apply[ eval, (12) ] => apply[ eval, apply[12] ] ...

	  // It appears there's need to re-write apply as:
	  //     apply(cell* f, void* env, va_list args)
	  // and so as all built-in functions.
	  return apply(first, butfirst);
	}
      }
      fprintf(stderr, "eval: unable to eval compound applicable exp\n");
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


cell* car(cell* args)
{
  if (args == NULL || args->car == NULL) {
    fprintf(stderr, "car: args is NULL\n");
    return NIL;
  }
  return args->car->car;
}

cell* cdr(cell* args)
{
  if (args == NULL || args->car == NULL) {
    fprintf(stderr, "cdr: args is NULL\n");
    return NIL;
  }
  return args->car->cdr;
}

cell* cons(cell* args)
{
  // assert there are exactly two params
  cell* car = NULL;
  cell* cdr = NULL;

  if (args != NULL) {
    if (args->car != NULL) {
      car = args->car;
    }

    if (args->cdr != NULL) {
      if (args->cdr == NIL) { // list has one element only
	cdr = NULL;
      }
      else {
	cdr = args->cdr->car;
      }
    }
  }


  if (car == NULL || cdr == NULL) {
    fprintf(stderr, "cons: expect two parameters\n");
    return NIL;
  }

  return new_cell('L', car, cdr);
}

cell* plus(cell* args)
{
  int val = 0;
  cell* c = args;
  while (c != NIL)
  {
    val += (int)c->car->car;
    c = c->cdr;
  }
  return new_cell('I', (cell*) val, NIL);
}

//////////////////////////////////////////////////////////////////////


cell* FEXP_LIST = NULL;

void fexp_init()
{
  FEXP_LIST = new_cell('B', NULL, NULL);
  cell* next= FEXP_LIST;

  next->car = new_cell('F', "cons", &cons);

  next->cdr = new_cell('B', NULL, NULL);
  next = next->cdr;

  next->car = new_cell('F', "car", &car);

  next->cdr = new_cell('B', NULL, NULL);
  next = next->cdr;

  next->car = new_cell('F', "cdr", &cdr);

  next->cdr = new_cell('B', NULL, NULL);
  next = next->cdr;

  next->car = new_cell('F', "plus", &plus);
}

void fexp_cleanup()
{
  int count=0;
  cell* cur = FEXP_LIST, *next;
  while (cur != NULL)
  {
    free(cur->car);
    next = cur->cdr;
    free(cur);

    ++count;
    cur = next;
  }

  printf("fexp_cleanup: removed %d node\n", count);
}

cell* fexp_lookup(char* name)
{
  cell* cur = FEXP_LIST;
  while (cur != NULL)
  {
    if (strcmp((char*)cur->car->car, name) == 0) return cur->car;
    cur = cur->cdr;
  }
  return NULL;
}

#endif
