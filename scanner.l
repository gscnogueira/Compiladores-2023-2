%{
#include <stdio.h>
%}


digit [0-9]
number {digit}+
identifier [a-zA-Z_][a-zA-Z0-9_]*
reserved_word "if"|"then"|"else"|"end"|"repeat"|"until"|"read"|"write"
special_symbol [-*/+=<();]|":="
white_space [\n\t ]

%%
{reserved_word} {printf("Palavra Reservada: %s\n", yytext);}
{special_symbol} {printf("Simbolo Especial: %s\n", yytext);}
{identifier} {printf("Identificador: %s\n", yytext);}
{number} {printf("Numero: %s\n", yytext);}
{white_space} {/*ignora espaços em branco*/}
.       { printf("Token inválido: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}
