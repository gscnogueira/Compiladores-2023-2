#include <stdio.h>
#include "tiny.tab.h"
#include "ast.h"
#include "parser.h"
#include "symtab.h"
#include "analyze.h"
#include "globals.h"
#include "codegen.h"
#include "utils.h"

extern int EchoSource;
extern int TraceScan;
extern int TraceParse;
extern int TraceAnalyze;
extern int TraceCode;
extern int Error;


extern FILE* yyin;

FILE * listing;
FILE * output_file;
int TraceAnalyze = 1;
int Error = 0;

int main(int argc, char** argv) {

#ifdef YYDEBUG
  yydebug = 0;
#endif

  if (argc != 2){
    fprintf(stderr, "Número inválido de argumentos\n");
    return 1;
  }

  char* input_file_name = argv[1];

  yyin = fopen(input_file_name, "r");

  if (yyin == NULL){
    fprintf(stderr,
	    "Arquivo %s não foi encontrado no sistema.\n",
	    input_file_name);
    return 1;
  }

  /* --------------------------------------------- */

  /* Parsing (Gabriel) */

  /* realiza parsing do arquivo */

  TreeNode* ast = parse(yyin);

  fclose(yyin);

  if (ast == NULL)
    return 1;

  /* print_AST(ast, 0); */

  /* --------------------------------------------- */

  /* Analise Semântica (Davi) */
  listing = stdout;
  buildSymtab(ast);

  typeCheck(ast);

  /* --------------------------------------------- */

  /* Geração de Código (João) */

  const char* output_file_name = get_output_file_name(input_file_name);

  output_file = fopen(output_file_name, "w");

  generateCode(ast);

  fclose(output_file);

  /* --------------------------------------------- */

  /* apagar espaço alocado para a AST depois de usar */

  delete_AST(ast);
  
  return 0;
}
