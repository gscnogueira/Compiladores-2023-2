%{
#include <stdio.h>
#include "parser.h"
int yyerror(const char* s);
%}

%option yylineno

digit [0-9]
number {digit}+
identifier [a-zA-Z_][a-zA-Z0-9_]*
special_symbol [-*/+=<();]|":="
white_space [\n\t ]

%%

"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"end" {return END;}
"repeat" {return REPEAT;}
"until" {return UNTIL;}
"read" {return READ;}
"write" {return WRITE;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"=" {return EQUAL;}
"<" {return LT;}
"(" {return OP;}
")" {return CP;}
";" {return SC;}
":=" {return ASSIGN;}
{identifier} {return ID;}
{number} {return NUM;}
{white_space} {}
.       {yyerror("Token inválido!"); }

%%

;; int yywrap() {
;;     return 1;
;; }

int yyerror (const char* s) /* Called by yyparse on error */
{
	printf ("line %d:%s\n", yylineno, s);

    return 0;
}
