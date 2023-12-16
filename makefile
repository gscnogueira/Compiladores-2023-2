compiler: scanner parser tiny_machine
	gcc -o tiny src/main.c src/tiny.tab.c src/ast.c src/symtab.c src/analyze.c src/codegen.c src/emit.c src/utils.c -g

scanner: src/tiny.l
	flex -o src/lex.yy.c src/tiny.l 

parser: src/tiny.y
	bison -d -o src/tiny.tab.c src/tiny.y --debug

tiny_machine: tiny_machine.c
	gcc -o tiny_machine tiny_machine.c

clear:
	rm *.tm tiny_machine tiny


