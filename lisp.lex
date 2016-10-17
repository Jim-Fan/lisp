
%x lisp_comment

%%

";"	BEGIN(lisp_comment);
<lisp_comment>[^\n]+	{ printf("; %s\n", yytext); }
<lisp_comment>\n	{ BEGIN(INITIAL); }

"("	{ puts(yytext); }
")"	{ puts(yytext); }

[a-zA-Z][a-zA-Z0-9]*	{ puts(yytext); }

[0-9]	{ puts(yytext); }
"-"?[1-9][0-9]*		{ puts(yytext); }

"+"|"-"|"*"|"/"		{ puts(yytext); }

[ \t\r\n]	{ /* ignored */ }

.	{
	printf("unknown char: %s\n",yytext);
	}

%%

#include <stdio.h>

int yywrap(void) { return 1; }

int main(void)
{
  return yylex();
}
