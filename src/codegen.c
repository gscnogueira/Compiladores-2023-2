#include <stdio.h>
#include "ast.h"
#include "emit.h"
#include "globals.h"
#include "tiny.tab.h"
#include "codegen.h"


void generateCode(TreeNode * tree){
    // Início do arquivo

    emitRM("LD",mp_reg,0,ac);
    emitRM("ST",ac,0,ac);

    genCode(tree);

    emitRO("HALT",0,0,0);
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

void genStatement(TreeNode * node){
    switch (node->kind.stmt){
    case WriteK:
        gen_write_stmt(node);
        break;
    default:
        break;
    }
}

void genExpression(TreeNode * node){
    switch (node->kind.exp){
    case(ConstK):
        gen_const_exp(node);
    case(IdK):
        gen_id_exp(node);
        break;
    case(OpK):
        gen_op_exp(node);
        break;
    default:
        break;
    }
}


void gen_const_exp(TreeNode *node) {
    emitRM("LDC", ac,node->attr.val,0);
}


void gen_write_stmt(TreeNode *node) {
        genExpression(node->child[0]);
        emitRO("OUT", ac, 0, 0);
}
