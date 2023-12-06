#ifndef _AST_H_
#define _AST_H_

#include <stdlib.h>

typedef struct ASTNode{
    int no_linha;
}ASTNode ;

ASTNode* create_node();

void delete_node(ASTNode* node);

#endif 
