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

    fprintf(output_file, "ASSEMBLY LEGAL\n");

    /* genCode(tree); */
    emitRO("IN", 1,0,0,"read input");
    emitRO("OUT", 2,0,0,"std output");
    emitRO("ADD", 0,1,2,"add regs");
    emitRO("SUB", 0,1,2,"sub regs");
    emitRO("MUL", 0,1,2,"mul regs");
    emitRO("DIV", 0,1,2,"div regs");

    emitRM("LD",0,1,2,"load value");
    emitRM("LDA",0,1,2,"load address");
    emitRM("LDC",0,1,2,"load constant");
    emitRM("ST",0,1,2,"store value");
    emitRM("JLT",0,1,2,"jump lower than");
    emitRM("JLE",0,1,2,"jump lower equal");
    emitRM("JGE",0,1,2,"jump greater equal");
    emitRM("JGT",0,1,2,"jump greather than");
    emitRM("JEQ",0,1,2,"jump if equal");
    emitRM("JNE",0,1,2,"jump if not equal");

    emitRO("HALT",0,0,0,"");

}
