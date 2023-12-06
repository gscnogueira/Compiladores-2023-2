#include "ast.h"

ASTNode* create_node(){
    ASTNode * t = (ASTNode*) malloc(sizeof(ASTNode));
    t->no_linha = 10;

    return t;
}

void delete_node(ASTNode* node){
    free(node);
}
