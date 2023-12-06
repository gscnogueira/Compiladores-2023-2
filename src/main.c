#include <stdio.h>
#include "parser.h"  // Inclua o arquivo de cabeçalho gerado pelo Yacc

extern FILE* yyin;  // Declare a variável global yyin usada pelo Flex

int main(int argc, char** argv) {


  if (argc != 2){
    fprintf(stderr, "Número inválido de argumentos\n");
    return 1;
  }

  char* file_name = argv[1];

  yyin = fopen(file_name, "r");

  yyparse();

  fclose(yyin);

  
  return 0;
}
