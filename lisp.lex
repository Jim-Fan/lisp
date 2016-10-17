%{
	#include <math.h>
	#include "./lisp.tab.h"
%}

%x lisp_comment

%%

";"	BEGIN(lisp_comment);
<lisp_comment>[^\n]+	{ /* printf("; %s\n", yytext); */ }
<lisp_comment>\n	{ BEGIN(INITIAL); }

"("	{ return T_LBRACKET; }
")"	{ return T_RBRACKET; }

[a-zA-Z][a-zA-Z0-9]*	{ return T_SYM; }

[0-9]	{ return T_NUM; }
"-"?[1-9][0-9]*		{ return T_NUM; }

"+"|"-"|"*"|"/"		{ return T_OP; }

[ \t\r\n]	{ /* ignored */ }

.	{
	printf("unknown char: %s\n",yytext);
	}

%%
