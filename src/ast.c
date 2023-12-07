#include "ast.h"
#include <stdio.h>

extern int yylineno;

extern char* yytext;

TreeNode* create_node(){
    TreeNode * t = (TreeNode*) malloc(sizeof(TreeNode));
    t->lineno = yylineno;

    return t;
}

TreeNode* create_assign_node(char* var_name){
    TreeNode* node = create_node();

    printf("%s", yytext);
    node->nodekind = StmtK;
    node->attr.name = var_name;

    return node;
}

void delete_node(TreeNode* node){
    free(node);
}
