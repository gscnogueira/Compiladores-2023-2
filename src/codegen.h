#ifndef _CODEGEN_H_
#define _CODEGEN_H_

void genCode(TreeNode * node);
void generateCode(TreeNode * node);

void genExpression(TreeNode * node);
void genStatement(TreeNode * node);

/* EXPS */

void gen_const_exp(TreeNode * node);
void gen_op_exp(TreeNode * node);
void gen_id_exp(TreeNode * node);

/* STMTS */
void gen_write_stmt(TreeNode * node);
void gen_assign_stmt(TreeNode * node);
void gen_read_stmt(TreeNode * node);
void gen_if_stmt(TreeNode * node);
void gen_repeat_stmt(TreeNode * node);

#endif
