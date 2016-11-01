#ifndef _LIST_UTIL_
#define _LIST_UTIL_

int cell_count(cell* c)
{
  int n = 0;
  while (c != NULL) {
    n++;
    c = c->cdr;
  }
  return n;
}

#endif
