#ifndef _LIST_BUILTIN_
#ifndef _LIST_BUILTIN_

#include "cell.h"
#include "eval.h"

// interface:
// cell* func(cell* args, cell* env)

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
                   eval((cell*)args->car, env),
                   eval((cell*)args->cdr->car, env));
  return result;
}

// (list) => NIL
cell* list(cell* arg_list, cell* env)
{
  if (arg_list == NULL) return NULL;

  cell* result = NULL;
  cell* iter = arg_list;

  /*
  // assert iter->type == 'L'

  result = (cell*) malloc(sizeof(cell));
  memcpy(result, iter, sizeof(cell));    //when should free?

  // now result->car == iter->car
  // and result->cdr == iter->cdr
  result->car = eval(iter->car);
  ...
  */
  return result;
}

#endif
