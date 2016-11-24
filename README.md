# lisp
Current status:

A LISP REPL without "E" - accept LISP expression and then pretty printed it. Below is a sample session:

```{r, engine='bash'}
24-11-2016 19:35:10 ~/lisp
$  ./main
cell_init: sizeof(cell*) = 8
cell_init: sizeof(cell)  = 24
cell_init: T   @ 00010410
cell_init: NIL @ 000103f0

[1] 13
13

[2] abc
abc

[3] DEF
DEF

[4] (this is a list)
(this is a list )
```

When syntax error is encountered, yyerror is fired and RPL quits:

```{r, engine='bash'}
[7] ( lambda (x) x ) 999 )
(lambda  (x  )x )

[8] 999

[9] yyerror: syntax error
```

The 7th prompt accepted lambda expresion and integer 999, then fails with un-balanced ")".
