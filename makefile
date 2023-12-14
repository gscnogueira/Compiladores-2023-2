compiler: scanner parser 
	gcc -o tiny src/main.c src/tiny.tab.c src/ast.c src/symtab.c src/analyze.c src/codegen.c src/send.c src/utils.c -g

scanner: src/tiny.l
	flex -o src/lex.yy.c src/tiny.l 

parser: src/tiny.y
	bison -d -o src/tiny.tab.c src/tiny.y --debug

clear:
	rm *.c


