compiler: scanner parser 
	gcc -o tiny src/scanner.c src/parser.c -g

scanner: src/scanner.l
	flex -o src/scanner.c src/scanner.l 

parser: src/parser.y
	bison -d -o src/parser.c src/parser.y

clear:
	rm *.c


