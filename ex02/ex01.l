%{
#include <stdio.h>
%}

%%
[ \t]   { /* Ignorar espaços e tabs */ }
"if"|"then"|"else"|"end"|"repeat"|"until"|"read"|"write" { printf("Token reserved w: %s\n", yytext); }
[+\-*/] { printf("Token OP: %s\n", yytext); }
[=<();]|:= { printf("Token OP: %s\n", yytext); }
[0-9]+  { printf("Token NUM: %s\n", yytext); }
[a-zA-Z][a-zA-Z0-9]* { printf("Token ID: %s\n", yytext); }
.       { printf("Caracter inválido: %s\n", yytext); }
\n      { /* Ignorar quebras de linha */ }

%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}
