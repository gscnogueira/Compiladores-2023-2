#include <stdio.h>
#include "ast.h"
#include "emit.h"
#include "globals.h"
#include "symtab.h"
#include "tiny.tab.h"
#include "codegen.h"

static int deslocamentoTemp = 0;


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
    case ReadK:
        gen_read_stmt(node);
        break;
    case WriteK:
        gen_write_stmt(node);
        break;
    case AssignK:
        gen_assign_stmt(node);
    default:
        break;
    }
}

void genExpression(TreeNode * node){
    switch (node->kind.exp){
    case(ConstK):
        gen_const_exp(node);
        break;
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

void gen_op_exp(TreeNode *node) {
    genExpression(node->child[0]);              // ac = child[0]
    emitRM("ST",ac,deslocamentoTemp--,mp_reg);  // mem[0] = child[0]
    genExpression(node->child[1]);              // ac = child[1]
    emitRM("LD", ac1,++deslocamentoTemp,mp_reg);// ac1 = mem[0]
    // ac = child[1], ac1 = child[0] 
    switch(node->attr.op){
        case(Plus):
            emitRO("ADD",ac,ac1,ac);
            break;
        case(Minus):
            emitRO("SUB",ac,ac1,ac);
            break;
        case(Mul):
            emitRO("MUL",ac,ac1,ac);
            break;
        case(Div):
            emitRO("DIV",ac,ac1,ac);
            break;
        case(Lt):
            emitRO("SUB",ac,ac1,ac);
            emitRM("JLT",ac,2,pc_reg);
            emitRM("LDC",ac,0,0);
            emitRM("LDA",pc_reg,1,pc_reg);
            emitRM("LDC",ac,1,0);
            break;
        case(Eq):
            emitRO("SUB",ac,ac1,ac);
            emitRM("JEQ",ac,2,pc_reg);
            emitRM("LDC",ac,0,0);
            emitRM("LDA",pc_reg,1,pc_reg);
            emitRM("LDC",ac,1,0);
            break;
    }
}


void gen_id_exp(TreeNode *node) {

    int id_loc = st_lookup(node->attr.name);

    emitRM("LD", ac,id_loc,gp_reg);
}

void gen_write_stmt(TreeNode *node) {
        genExpression(node->child[0]);
        emitRO("OUT", ac, 0, 0);
}


void gen_assign_stmt(TreeNode *node) {

    char * id = node->attr.name;
    int id_loc = st_lookup(id);

    genExpression(node->child[0]);

    emitRM("ST", ac, id_loc, gp_reg);
}

void gen_read_stmt(TreeNode *node) {

    char * id = node->attr.name;
    int id_loc = st_lookup(id);

    emitRO("IN", ac, 0, 0);

    emitRM("ST", ac, id_loc, gp_reg);

}
