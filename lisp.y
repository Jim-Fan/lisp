%{
#include <stdio.h>
#include "src/atom.h"
#include "src/cell.h"

int LISP_COUNT = 1;

void lisp_prompt()
{
  printf("\n[%d] ", LISP_COUNT);
}

void yyerror(char* s)
{
  printf("yyerror: %s\n", s);
}

extern int yylex();
%}

	/* So that RHS for $$ assignment */
%union {
  int num;
  char* sym;
  struct atom* a;
  struct cell* c;
}

	/* So that $n will work */
	/* What about exp ? */
%type <num> T_NUM
%type <sym> T_SYM
%type <a> atom
%type <c> exp
%type <c> exp_list

%token T_NUM T_SYM T_LBRACKET T_RBRACKET T_OP

%%

repl:
	/* nothing */
	|
	exp { LISP_COUNT++; lisp_prompt(); } repl
;

	/* LISP expression is either atom or list */
atom:
	T_NUM	{ $$=new_num_atom($1); }
	|
	T_SYM	{ $$=new_sym_atom($1); }
;

	/* A list is L/Rbrackets with series 
	   of expression (possibly empty) in it */
exp_list:
	/* nothing */	{ $$=0; }
	|
	exp exp_list	{ $$=new_cell($1, $2); }
;

exp:
	atom
	|
	T_LBRACKET exp_list T_RBRACKET
;

%%

#include <stdio.h>

extern void yyerror(char*);

int main(void)
{
  lisp_prompt();
  return yyparse();
}
