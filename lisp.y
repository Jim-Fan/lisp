%{
#include <stdio.h>

void yyerror(char* s)
{
  printf("yyerror: %s\n", s);
}

extern int yylex();
%}

%token T_NUM T_SYM T_LBRACKET T_RBRACKET T_OP

%%

prog:
	/* nothing */
	|
	mini_prog
	|
	prog mini_prog
;


mini_prog:
	exp
;


exp_list:
	exp
	|
	exp_list exp
;


exp:
	T_NUM 
	|
	T_SYM
	|
	T_LBRACKET exp_list T_RBRACKET
;

%%

#include <stdio.h>

extern void yyerror(char*);

int main(void)
{
  return yyparse();
}
