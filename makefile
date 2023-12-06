compiler: scanner parser 
	gcc -o tiny src/main.c src/tiny.tab.c src/ast.c  -g


scanner: src/tiny.l
	flex -o src/lex.yy.c src/tiny.l 

parser: src/tiny.y
	bison -d -o src/tiny.tab.c src/tiny.y

clear:
	rm *.c


