/* Verificando a sintaxe de programas segundo nossa GLC-exemplo */
/* considerando notacao polonesa para expressoes */

%{
#include <stdio.h> 
#include "ast.h"

static TreeNode* ast_final;

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
%type<node> exp simple-exp comparison-op term factor

%locations
%parse-param { FILE* fp }

%%

/* Regras definindo a GLC "TINY" (Louden) e acoes correspondentes */

program: stmt-sequence { ast_final = $1;};

stmt-sequence: stmt-sequence SC statement
             | statement 

statement: if-stmt 
| repeat-stmt 
| assign-stmt 
| read-stmt 
| write-stmt 
;

if-stmt: IF exp THEN stmt-sequence END {$$ = create_node();}
| IF exp THEN stmt-sequence ELSE stmt-sequence END {$$ = create_node();}
;

repeat-stmt: REPEAT stmt-sequence UNTIL exp {$$ = create_node();} ;

assign-stmt: ID ASSIGN exp {
  printf("%s\n", $1);
  $$ = create_assign_node($1);
  $$ -> child[0] = $3;
};

read-stmt: READ ID { $$ = create_node();};

write-stmt:	WRITE exp {$$ = create_node();};

exp: simple-exp comparison-op simple-exp
| simple-exp
;

comparison-op: LT {$$ = create_node();}
| EQUAL {$$ = create_node();}
;

simple-exp: simple-exp addop term {$$ = create_node();}
| term
;

addop: PLUS | MINUS ;

term: term mulop factor | factor ;

mulop: MUL | DIV ;

factor: OP exp CP {$$ = create_node();}
| NUM {$$ = create_const_node($1);}
| ID {$$ = create_node();}
;

%%

extern int yylineno;

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
