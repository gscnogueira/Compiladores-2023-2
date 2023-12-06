/* Verificando a sintaxe de programas segundo nossa GLC-exemplo */
/* considerando notacao polonesa para expressoes */

%{
#include <stdio.h> 
#include "ast.h"

#define YYSTYPE ASTNode *

static ASTNode* ast_final;

int yylex();
int yyerror(FILE* fp, const char* s);


%}

%locations
%parse-param { FILE* fp }

%token NUM
%token ID
%token IF THEN ELSE END REPEAT UNTIL READ WRITE
%token MINUS MUL DIV PLUS EQUAL LT OP CP SC ASSIGN

%%

/* Regras definindo a GLC "TINY" (Louden) e acoes correspondentes */

program: stmt-sequence { YYSTYPE blau = create_node() ;
                        ast_final = blau;};

stmt-sequence: stmt-sequence SC statement
             | statement ;

statement: if-stmt
         | repeat-stmt
         | assign-stmt
         | read-stmt
         | write-stmt
         ;

if-stmt: IF exp THEN stmt-sequence END
	   | IF exp THEN stmt-sequence ELSE stmt-sequence END
       ;

repeat-stmt: REPEAT stmt-sequence UNTIL exp ;

assign-stmt: ID ASSIGN exp;

read-stmt: READ ID ;

write-stmt:	WRITE exp ;

exp: simple-exp comparison-op simple-exp | simple-exp ;

comparison-op: LT | EQUAL ;

simple-exp: simple-exp addop term | term ;

addop: PLUS | MINUS ;

term: term mulop factor | factor ;

mulop: MUL | DIV ;

factor: OP exp CP | NUM | ID ;

%%

extern int yylineno;

int yyerror (FILE* fp, const char* s) /* Called by yyparse on error */
{
	printf ("line %d:%s\n", yylineno, s);

    return 0;
}

ASTNode* parse(FILE * src_file){
    yyparse(src_file);
    return ast_final;
}

#include "lex.yy.c" 
