#include <stdio.h>
#include "ast.h"
#include "send.h"
#include "globals.h"


void genCode(TreeNode * node){
/*     if (node != NULL) { */
/*         if (node -> nodekind == StmtK) { */
/*             genStatement(node); */
/*         } else if (node -> nodekind == ExpK){ */
/*             genExpression(node); */
/*         } */
/*         genCode(node->sibling); */
/*     } */
}

void generateCode(TreeNode * tree){
    // Início do arquivo

    fprintf(output_file, "ASSEMBLY LEGAL\n");

    /* genCode(tree); */
    /* sendRO("HALT",0,0,0,""); */
}
