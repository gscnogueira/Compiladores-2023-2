#include <stdio.h>
#include "ast.h"
#include "emit.h"
#include "globals.h"
#include "symtab.h"
#include "tiny.tab.h"
#include "codegen.h"

static int tempOffset = 0;


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

    if (node == NULL) return;

    switch (node->kind.stmt){
    case ReadK:
        gen_read_stmt(node);
        break;
    case WriteK:
        gen_write_stmt(node);
        break;
    case AssignK:
        gen_assign_stmt(node);
        break;
    case IfK:
        gen_if_stmt(node);
        break;
    case RepeatK:
        gen_repeat_stmt(node);
        break;
    default:
        break;
    }
}

void genExpression(TreeNode * node){

    if (node == NULL) return;

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
    emitRM("ST",ac,tempOffset--,mp_reg);  // mem[0] = child[0]
    genExpression(node->child[1]);              // ac = child[1]
    emitRM("LD", ac1,++tempOffset,mp_reg);// ac1 = mem[0]
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

    int id_loc = symtab_lookup(node->attr.name);

    emitRM("LD", ac,id_loc,gp_reg);
}

void gen_write_stmt(TreeNode *node) {
        genExpression(node->child[0]);
        emitRO("OUT", ac, 0, 0);
}


void gen_assign_stmt(TreeNode *node) {

    char * id = node->attr.name;
    int id_loc = symtab_lookup(id);

    genExpression(node->child[0]);

    emitRM("ST", ac, id_loc, gp_reg);
}

void gen_read_stmt(TreeNode *node) {

    char * id = node->attr.name;
    int id_loc = symtab_lookup(id);

    emitRO("IN", ac, 0, 0);

    emitRM("ST", ac, id_loc, gp_reg);

}

void gen_if_stmt(TreeNode *node) {
    
    TreeNode *condicao, *if_part, *else_part;
    int start_if,end_if, start_else, end_else;

    condicao = node->child[0];
    if_part = node->child[1];
    else_part = node->child[2];

    // armazena valor da condição em ac;
    genExpression(condicao);

    start_if = emitSkip(1);

    genCode(if_part);

    end_if = emitSkip(else_part? 1 : 0);

    genCode(else_part);

    end_else = emitSkip(0);

    emitBack(start_if);

    if(else_part == NULL) {
        emitRM("JEQ",ac, end_if - (start_if+1), pc_reg);
    }
    else {
        emitRM("JEQ",ac, end_if - (start_if), pc_reg);
        emitBack(end_if);
        emitRM("LDC",pc_reg, end_else, 0);
    }

    emitRestore();

}

void gen_repeat_stmt(TreeNode *node) {
    
    TreeNode *condicao, *stmts;

    stmts = node->child[0];
    condicao = node->child[1];

    int start_repeat = emitSkip(0);

    genCode(stmts);

    genExpression(condicao);

    int end_repeat = emitSkip(0);

    emitRM("JEQ",ac, start_repeat - (end_repeat + 1), pc_reg);

}

