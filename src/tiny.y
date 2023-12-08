/* Verificando a sintaxe de programas segundo nossa GLC-exemplo */
/* considerando notacao polonesa para expressoes */

%{
#include <stdio.h> 
#include "ast.h"

static TreeNode* ast_final;
extern int yylineno;

int yylex();
int yyerror(FILE* fp, const char* s);

%}

%union {
    int number;
    char *string;
    struct treeNode* node;
}

%token<number> NUM
%token<string> ID
%token<string> IF THEN ELSE END REPEAT UNTIL READ WRITE
%token<string> MINUS MUL DIV PLUS EQUAL LT OP CP SC ASSIGN

%type<node> program statement stmt-sequence assign-stmt repeat-stmt if-stmt write-stmt read-stmt
%type<node> exp simple-exp comparison-op term factor addop mulop

%locations
%parse-param { FILE* fp }

%%

/* Regras definindo a GLC "TINY" (Louden) e acoes correspondentes */

program: stmt-sequence { ast_final = $1;};

stmt-sequence: stmt-sequence SC statement {
    TreeNode* current_stmt = $1;
    current_stmt = $1;
    while (current_stmt->sibling != NULL){
        current_stmt = current_stmt->sibling;
    }
    current_stmt->sibling = $3;
    $$ = $1;
 }
| statement
;

statement: if-stmt 
| repeat-stmt 
| assign-stmt 
| read-stmt 
| write-stmt 
;

if-stmt: IF exp THEN stmt-sequence END {
    $$ = create_if_node();
    $$->child[0] = $2;
    $$->child[1] = $4;}
| IF exp THEN stmt-sequence ELSE stmt-sequence END {
    $$ = create_if_node();
    $$->child[0] = $2;
    $$->child[1] = $4;
    $$->child[2] = $6;}
;

repeat-stmt: REPEAT stmt-sequence UNTIL exp {
    $$ = create_repeat_node();
    $$->child[0] = $2; 
    $$->child[1] = $4; 
} ;

assign-stmt: ID ASSIGN exp {
    $$ = create_assign_node($1);
    $$->child[0] = $3;
};

read-stmt: READ ID { $$ = create_read_node($2);};

write-stmt:	WRITE exp {
    $$ = create_write_node();
    $$->child[0] = $2;
};

exp: simple-exp comparison-op simple-exp {
    $$ = $2;
    $$->child[0] = $1;
    $$->child[1] = $3;
}
| simple-exp
;

comparison-op: LT {$$ = create_op_node(Lt);}
| EQUAL {$$ = create_op_node(Eq);}
;

simple-exp: simple-exp addop term {
    $$ = $2;
    $$->child[0] = $1;
    $$->child[1] = $3;
}
| term
;

addop: PLUS { $$ = create_op_node(Plus);}
| MINUS {$$ = create_op_node(Minus);}
;

term: term mulop factor {
    $$ = $2;
    $$->child[0] = $1;
    $$->child[1] = $3;
}
| factor 
;

mulop: MUL {$$ = create_op_node(Mul);}
| DIV {$$ = create_op_node(Div);}
;

factor: OP exp CP {$$ = $2;}
| NUM {
    $$ = create_const_node($1);}
| ID {$$ = create_id_node($1);}
;

%%


int yyerror (FILE* fp, const char* s) /* Called by yyparse on error */
{
	printf ("line %d:%s\n", yylineno, s);

    return 0;
}

TreeNode* parse(FILE * src_file){
    yyparse(src_file);
    return ast_final;
}

#include "lex.yy.c" 
