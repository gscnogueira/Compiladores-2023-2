#include <stdio.h>
#include "tiny.tab.h"
#include "ast.h"
#include "parser.h"

extern FILE* yyin;

int main(int argc, char** argv) {

#ifdef YYDEBUG
  yydebug = 0;
#endif

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

  /* --------------------------------------------- */

  /* Parsing (Gabriel) */

  /* realiza parsing do arquivo */

  TreeNode* ast = parse(yyin);

  fclose(yyin);

  if (ast == NULL)
    return 1;

  print_AST(ast, 0);

  /* --------------------------------------------- */

  /* Analise Semântica (Davi) */

  /* --------------------------------------------- */

  /* Geração de Código (João) */

  /* --------------------------------------------- */

  /* apagar espaço alocado para a AST depois de usar */

  delete_AST(ast);
  
  return 0;
}
