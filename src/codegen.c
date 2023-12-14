#include <stdio.h>
#include "ast.h"
#include "emit.h"

void genCode(TreeNode * node){
    if (node != NULL) {
        int i = 0;
        genCode(node->child[i])
        if (node -> nodekind == StmtK) {
            genStatement(node);
        } else if (node -> nodekind == ExpK){
            genExpression(node);
        }
        genCode(node->sibling);
    }
}

void generateCode(FILE * intCode, TreeNode * tree){
    // Início do arquivo
    genCode(tree);
    emitCmmt("Fim da execução");
    emitRO("HALT",0,0,0,"");
}