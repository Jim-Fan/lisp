all:	main

lex.yy.c: lisp.lex
	flex -s lisp.lex

lisp.tab.c: lisp.y
	bison -d lisp.y

main:	lex.yy.c lisp.tab.c
	gcc lex.yy.c lisp.tab.c -lfl -lm -o main

clean:
	rm -f *~ ./main lex.yy.c lisp.tab.* *.stackdump
