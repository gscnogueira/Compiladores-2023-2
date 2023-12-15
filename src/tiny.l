%{
#include <stdio.h>
int line_no = 1 ;
%}

%option noyywrap


digit [0-9]
number {digit}+
identifier [a-zA-Z_][a-zA-Z0-9_]*
white_space [ \t]+

%%

"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"end" {return END;}
"repeat" {return REPEAT;}
"until" {return UNTIL;}
"read" {return READ;}
"write" {return WRITE;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"=" {return EQUAL;}
"<" {return LT;}
"(" {return OP;}
")" {return CP;}
";" {return SC;}
":=" {return ASSIGN;}
{identifier} { yylval.string = strdup(yytext); return ID;}
{number} {yylval.number = atoi(yytext); return NUM;}
{white_space} {}
"\n" {line_no++;}
"{" { char c;
      do { c = input();
           if (c == EOF) break;
           if (c == '\n') line_no++;
      } while (c != '}');
    }
.       {char msg[100];
        sprintf(msg, "Token inválido (%s)", yytext);
       	yyerror(yyin, msg);}
%%


