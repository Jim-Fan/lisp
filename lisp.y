%{
#include <stdio.h>
#include "src/cell.h"
#include "src/oblist.h"
#include "src/pprint.h"

int LISP_COUNT = 1;
cell* LISP_ROOT = NULL;

void lisp_init()
{
  cell_init();
  oblist_init();
}

void lisp_cleanup()
{
  oblist_cleanup();
  cell_cleanup();
}

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
  int i;
  char* s;
  struct _cell* c;
}

%type <i> T_NUM
%type <c> T_SYM
%type <c> atom
%type <c> exp
%type <c> exp_list

%token T_NUM T_SYM T_LBRACKET T_RBRACKET T_OP

%%

repl:
	/* nothing */
	|
	exp {
	  pprint($1, 0);
	  printf("\n");
	  free_cell($1);
	  LISP_COUNT++;
	  lisp_prompt(); } repl
;

	/* LISP expression is either atom or list */
atom:
	T_NUM	{ $$ = new_cell('I', $1, NIL); }
	|
	T_SYM	{ $$ = new_cell('S', $1, NIL); }
;

	/* A list is L/R brackets with series 
	   of expression (possibly empty) in it */
exp_list:
	/* nothing */ { $$ = NIL; }
	|
	exp exp_list { $$=new_cell('L',$1,$2); }
;

exp:
	atom { $$=$1; }
	|
	T_LBRACKET exp_list T_RBRACKET { $$=$2; }
;

%%

#include <stdio.h>

extern void yyerror(char*);

int main(void)
{
  lisp_init();
  lisp_prompt();
  int i = yyparse();
  lisp_cleanup();

  return i;
}
