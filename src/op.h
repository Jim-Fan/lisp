#ifndef _LIST_OP_
#define _LIST_OP_

/*
   Built-in functions, arguments should have been 
   evaluated before calling, which should be 
   performed by eval().
 */

cell* car(cell* args)
{
  if (args == NULL || args->car == NULL) {
    fprintf(stderr, "car: args is NULL\n");
    return NIL;
  }

  // By definition: (car NIL) => NIL
  if (args->car == NIL) return NIL;

  if (args->car->type != 'L') {
    fprintf(stderr, "car: args is not a list\n");
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

  // By definition: (cdr NIL) => NIL
  if (args->car == NIL) return NIL;

  if (args->car->type != 'L') {
    fprintf(stderr, "car: args is not a list\n");
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



#endif
