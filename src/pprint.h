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
  put_space(level);

  if (c == NULL) {
    put_space(level);
    printf("NIL");
    return;
  }

  cell* next;

  switch (c->type) {

    case 'I':
      printf("%d ", (int)c->car);
      break;

    case 'S':
      printf("%s ", (char*)c->car);
      break;

    case 'F':
      printf("#<callable@%X> ", (void*)c->car);
      break;

    case 'L':

      // Iterate through linked list, print
      // only it's element (c->car)
      next = c;
      printf("(");
      while (next != NULL) {
        pprint(next->car, level+1);
        putchar(' ');
        next = next->cdr;
      }
      printf(")");
      break;

    default:
      printf("pprint: should not reach here\n");
  }
}

#endif
