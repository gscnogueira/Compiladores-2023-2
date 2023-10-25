%{

#include <stdio.h>

%}

id	[a-zA-Z][a-zA-Z0-9]*\n
constNum	[+|-]?[0-9]+(\.|\.[0-9]+)?\n
outro	.*\n

%%

{id}		{printf("Identificador\n");}
{constNum}	{printf("Constante Numerica\n");}
{outro}		{printf("Token nao reconhecido. :(\n");}

%%

/* recomendavel declarar sempre

   funcao yywrap() */

int yywrap ();



/* programa principal */

main() {

  yylex(); /* scanner gerado por Flex */

}



int yywrap() {

 return 1;

}
