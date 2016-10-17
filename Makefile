all:	main

lex:	lisp.lex
	flex -s lisp.lex

main:	lex
	gcc -lfl lex.yy.c -o main

clean:
	rm -f *~ ./main lex.yy.c
