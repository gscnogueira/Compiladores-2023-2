%{
#include <stdio.h>
%}

%option noyywrap
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
.       {char msg[100];
        sprintf(msg, "Token inválido (%s)", yytext);
       	yyerror(msg);}
%%


