all:	main

lex.yy.c: lisp.lex
	flex -s lisp.lex

lisp.tab.c: lisp.y
	bison -d lisp.y

main:	src/cell.h lex.yy.c lisp.tab.c
	gcc -g -o main lex.yy.c lisp.tab.c -lfl -lm

clean:
	rm -f *~ ./main lex.yy.c lisp.tab.*
