#ifndef _LISP_ATOM_
#define _LISP_ATOM_


typedef struct atom {
  char type;
  union {
    int num;
    char* sym;
  } val;
} atom;

atom* new_num_atom(int k)
{
  atom* a = malloc(sizeof(atom));
  a->val.num = k;
  return a;
}

atom* new_sym_atom(char* s)
{
  atom* a = malloc(sizeof(atom));
  a->val.sym = s;
  return a;
}

#endif
