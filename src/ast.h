#ifndef _AST_H_
#define _AST_H_

#include <stdlib.h>

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
typedef enum {OpK,ConstK,IdK} ExpKind;
typedef enum {Plus,Minus,Mul,Div,Lt,Eq}TokenType;


typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode {
    struct treeNode * child[MAXCHILDREN];
    struct treeNode * sibling;
    int lineno;
    NodeKind nodekind;
    union { StmtKind stmt; ExpKind exp;} kind;
    union { TokenType op; int val; char * name; } attr;
    ExpType type;
} TreeNode;



TreeNode* create_node();

void delete_AST(TreeNode* node);

/* statement nodes */

TreeNode* create_repeat_node();

TreeNode* create_assign_node(char* var_name);

TreeNode* create_if_node();

TreeNode* create_read_node(char* var_name);

TreeNode* create_write_node();



/* expression nodes */

TreeNode* create_const_node(int const_val);

TreeNode* create_op_node(TokenType operator);

TreeNode* create_id_node(char* var_name);


/* Função utilitária para mostrar AST*/

void print_AST(TreeNode* node, int level);

#endif 
