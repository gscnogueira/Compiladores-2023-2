#include <stdio.h>
#include "ast.h"
#include "emit.h"

void genCode(TreeNode * node){
    if (node != NULL) {
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
    sendCmmt("Fim da execução");
    sendRO("HALT",0,0,0,"");
}