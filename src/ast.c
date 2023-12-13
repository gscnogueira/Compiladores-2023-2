#include "ast.h"
#include <stdio.h>

extern int line_no;
extern char* yytext;

void print_stmt_node(TreeNode* node){
  printf("STATEMENT\n");

  switch (node->kind.stmt){
  case AssignK:
      printf("ASSIGN (%s)\n", node->attr.name);
      break;
  case IfK:
      printf("IF\n");
      break;
  case WriteK:
      printf("WRITE\n");
      break;
  case ReadK:
      printf("READ (%s)\n", node->attr.name);
      break;
  case RepeatK:
      printf("REPEAT\n");
      break;
  default:
      printf("Não Implementado :(\n");
      break;
  }
}

void print_attr_op(TokenType op) {
    
  switch (op){
  case Plus:
      printf("OP (+)\n");
      break;
  case Minus:
      printf("OP (-)\n");
      break;
  case Mul:
      printf("OP (*)\n");
      break;
  case Div:
      printf("OP (/)\n");
      break;
  case Lt:
      printf("OP (<)\n");
      break;
  case Eq:
      printf("OP (=)\n");
      break;
  default:
      break;
  }
}

void print_exp_node(TreeNode* node){
  printf("EXPRESSION\n");

  switch (node->kind.exp){
  case ConstK:
      printf("CONST (%d)\n", node->attr.val);
      break;
  case OpK:
      print_attr_op(node->attr.op);
      break;
  case IdK:
      printf("ID (%s)\n", node->attr.name);
      break;
  default:
      printf("Não Implementado :(\n");
      break;
  }
}

void print_AST(TreeNode* node, int level){
    if (node == NULL)
        return;
    
    printf("------------LEVEL %d---------------\n", level);
    printf("linha: %d\n", node->lineno);
    if (node->nodekind == ExpK)
        print_exp_node(node);
    else 
        print_stmt_node(node);

    for (int i =0; i < MAXCHILDREN; i++){
        print_AST(node->child[i], level+1);
    }

    print_AST(node->sibling, level);
}

TreeNode* create_node(){
    TreeNode * t = (TreeNode*) malloc(sizeof(TreeNode));
    t->lineno = line_no;
    t->sibling = NULL;
    for (int i = 0; i < MAXCHILDREN; i++)
        t->child[i] = NULL;

    return t;
}

TreeNode* create_exp_node() {
    TreeNode* node = create_node();

    node->nodekind = ExpK;

    return node;
}

TreeNode* create_stmt_node() {
    TreeNode* node = create_node();

    node->nodekind = StmtK;

    return node;
}

TreeNode* create_assign_node(char* var_name){
    TreeNode* node = create_stmt_node();

    node->kind.stmt = AssignK;
    node->attr.name = var_name;

    return node;
}

TreeNode* create_const_node(int const_val){
    TreeNode* node = create_exp_node();

    node->kind.exp = ConstK;
    node->attr.val = const_val;
    node->type = Integer;

    return node;
}

TreeNode *create_op_node(TokenType operator) {
    TreeNode* node = create_exp_node();

    node->kind.exp = OpK;
    node->attr.op = operator;
    node->type = Integer;

    return node;
}

TreeNode* create_id_node(char* var_name) {
    TreeNode* node = create_exp_node();

    node->kind.exp = IdK;
    node->attr.name = var_name;
    node->type = Integer;

    return node;
}

TreeNode* create_if_node() {
    TreeNode* node = create_stmt_node();

    node->kind.stmt = IfK;

    return node;
}

TreeNode* create_write_node() {
    TreeNode* node = create_stmt_node();

    node->kind.stmt = WriteK;

    return node;
    
}

TreeNode* create_read_node(char *var_name) {
    TreeNode* node = create_stmt_node();

    node->kind.stmt = ReadK;
    node->attr.name = var_name;

    return node;
    
}

TreeNode* create_repeat_node() {
    TreeNode* node = create_stmt_node();

    node->kind.stmt = RepeatK;

    return node;
}


void delete_stmt_node(TreeNode *node) {
    StmtKind kind = node->kind.stmt;

    if( kind == AssignK || kind == ReadK )
        free(node->attr.name);

    free(node);
}


void delete_exp_node(TreeNode *node) {
    ExpKind kind = node->kind.exp;

    if( kind == IdK)
        free(node->attr.name);

    free(node);
}

void delete_AST(TreeNode* node){
    if (node == NULL)
        return;
    for (int i = 0; i < MAXCHILDREN; i++){
        delete_AST(node->child[i]);
  }

    delete_AST(node->sibling);

    if (node->nodekind == StmtK)
        delete_stmt_node(node);
    else
        delete_exp_node(node);
}
