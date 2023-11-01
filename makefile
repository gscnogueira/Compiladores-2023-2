compiler: scanner
	gcc -Wall lex.yy.c -o tiny

scanner: scanner.l
	flex scanner.l


