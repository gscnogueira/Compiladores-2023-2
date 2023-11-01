/* Verificando a sintaxe de programas segundo nossa GLC-exemplo */
/* considerando notacao polonesa para expressoes */
%{
#include <stdio.h> 
%}
%token NUM
%token ID
%%
/* Regras definindo a GLC "TINY" (Louden) e acoes correspondentes */
program:	stmt-sequence
;
stmt-sequence:	  stmt-sequence ';' statement 
				| statement
;
statement:	  if-stmt
			| repeat-stmt
			| assign-stmt
			| read-stmt
			| write-stmt
;
if-stmt:	  "if" exp "then" stmt-sequence "end"
			| "if" exp "then" stmt-sequence "else" stmt-sequence "end"
;
repeat-stmt:  "repeat" stmt-sequence "until" exp
;
assign-stmt:  ID ":=" exp
;
read-stmt:	"read " ID
;
write-stmt:	"write" exp
;
exp:	  simple-exp comparison-op simple-exp
		| simple-exp
;
comparison-op:	  '<' 
				| '='
;
simple-exp:	  simple-exp addop term
			| term
;
addop:	  '+'
		| '-'
;
term:	  term mulop factor
		| factor
;
mulop:    '*' 
		| '/'
;
factor:   '(' exp ')'
		| NUM
		| ID
;
%%
main () 
{
	yyparse ();
}
yyerror (s) /* Called by yyparse on error */
	char *s;
{
	printf ("Problema com a analise sintatica!\n", s);
}


