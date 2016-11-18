#ifndef _LIST_PRINT_
#define _LIST_PRINT_

#include <stdio.h>
#include "cell.h"

void put_space(int level)
{
  while (level-- > 0) { putchar(' '); }
}

void pprint(cell* c, int level)
{
  //put_space(level);

  if (c == NULL) {
    //put_space(level);
    fprintf(stderr, "\npprint: null pointer\n");
    return;
  }

  if (c == NIL) {
      printf("NIL ");
      return;
  }

  cell* next;

  switch (c->type) {

    case 'I':
      printf("%d ", c->car);
      break;

    case 'S':
      printf("%s ", (char*)c->car);
      break;

    case 'F':
      printf("#<callable@%X> ", (void*)c->car);
      break;

    case 'L':

      // Iterate through linked list, print
      // only it's element (c->car)  <==  ????
      next = c;

      put_space(level);
      printf("(");

      while (next != NULL && next != NIL) {
        pprint(next->car, level+1);
        //putchar('\n');
        //pprint(next->cdr, level+1);
        next = next->cdr;
      }

      put_space(level);
      printf(")");

      break;

    default:
      fprintf(stderr, "\npprint: reached default branch\n");
  }
}

#endif
