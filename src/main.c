#include <stdio.h>
#include "parser.h"

extern FILE* yyin;

int main(int argc, char** argv) {


  if (argc != 2){
    fprintf(stderr, "Número inválido de argumentos\n");
    return 1;
  }

  char* file_name = argv[1];

  yyin = fopen(file_name, "r");

  if (yyin == NULL){
    fprintf(stderr,
	    "Arquivo %s não foi encontrado no sistema.\n",
	    file_name);
    return 1;
  }

  yyparse(yyin);

  fclose(yyin);

  
  return 0;
}
