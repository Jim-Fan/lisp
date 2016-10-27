all:	main

lex:	lisp.lex
	flex -s lisp.lex

y:	lisp.y
	bison -d lisp.y

main:	y lex
	gcc -g -o main lex.yy.c lisp.tab.c -lfl -lm

clean:
	rm -f *~ ./main lex.yy.c lisp.tab.*
