#include "ast.h"

TreeNode* create_node(){
    TreeNode * t = (TreeNode*) malloc(sizeof(TreeNode));
    t->lineno = 10;

    return t;
}

void delete_node(TreeNode* node){
    free(node);
}
