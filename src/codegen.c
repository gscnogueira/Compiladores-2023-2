#include <stdio.h>
#include "ast.h"
#include "emit.h"
#include "globals.h"
#include "tiny.tab.h"


void genExpression(TreeNode * node){
    switch (node->kind.exp){
    case(ConstK):
        emitRM("LDC", ac,node->attr.val,0);
    defatult:
        break;
    }
}

void genStatement(TreeNode * node){
    switch (node->kind.stmt){
    case WriteK:

        genExpression(node->child[0]);

        emitRO("OUT", ac, 0, 0);
        break;
    defatult:
        break;
    }
}


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

void generateCode(TreeNode * tree){
    // Início do arquivo

    emitRM("LD",mp_reg,0,ac);
    emitRM("ST",ac,0,ac);

    genCode(tree);

    emitRO("HALT",0,0,0);
}

