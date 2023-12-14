#include <stdio.h>
#include "ast.h"
#include "emit.h"
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

    emitRM("LD",mp_reg,0,ac);
    emitRM("ST",ac,0,ac);

    /* genCode(tree); */

    emitRO("HALT",0,0,0);
}
