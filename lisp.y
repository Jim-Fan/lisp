%{
#include <stdio.h>

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

%token T_NUM T_SYM T_LBRACKET T_RBRACKET T_OP

%%

repl:
	/* nothing */
	|
	exp { LISP_COUNT++; lisp_prompt(); } repl
;

	/* LISP expression is either atom or list */
atom:
	T_NUM | T_SYM
;

	/* A list is L/Rbrackets with series 
	   of expression (possibly empty) in it */
exp_list:
	/* nothing */
	|
	exp exp_list
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
