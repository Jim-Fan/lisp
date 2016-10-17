all:	main

lex:	lisp.lex
	flex -s lisp.lex

y:	lisp.y
	bison -d lisp.y

main:	y lex
	gcc -lfl -lm lex.yy.c lisp.tab.c -o main

clean:
	rm -f *~ ./main lex.yy.c lisp.tab.*
