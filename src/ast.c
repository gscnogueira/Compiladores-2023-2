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

    node->nodekind = StmtK;
    node->attr.name = var_name;
    node->kind.stmt = AssignK;

    return node;
}

TreeNode* create_const_node(int const_val){
    TreeNode* node = create_node();

    node->nodekind = ExpK;
    node->kind.exp = ConstK;
    node->attr.val = const_val;
    node->type = Integer;

    return node;
}

void delete_node(TreeNode* node){
    free(node);
}

void print_stmt_node(TreeNode* node){
  printf("STATEMENT\n");
}

void print_AST(TreeNode* node){
  if (node->nodekind == ExpK)
    print_stmt_node(node);
  else 
    print_stmt_node(node);
}

