#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"
#include "globals.h"
#include "analyze.h"

static int location = 0;

static void traverse(TreeNode * node, void (* preProc) (TreeNode *), void (* postProc) (TreeNode *) )
{ if (node != NULL) {
    preProc(node);
    for (int i=0; i < MAXCHILDREN; i++) {
        traverse(node->child[i], preProc, postProc);
    }
    postProc(node);
    traverse(node->sibling, preProc, postProc);
  }
}

static void emptyFunc(TreeNode * node)
{}

static void insertNode(TreeNode * node)
{
    if ((node->nodekind == StmtK) && (node->kind.stmt == AssignK || node->kind.stmt == ReadK))
        symtab_insert(node->attr.name, node->lineno);
    
    else if ((node->nodekind == ExpK) && (node->kind.exp == IdK && symtab_lookup(node->attr.name) != -1)) 
        symtab_insert(node->attr.name, node->lineno);
}


void buildSymtab(TreeNode * syntaxTree)
{ traverse(syntaxTree, insertNode, emptyFunc);
  if (ShowSymTab)
  { printf("\nTabela de símbolos:\n\n");
    printSymTab();
  }
}

static void checkNode(TreeNode *node)
{
    if (node->nodekind == ExpK)
    {
        if (node->kind.exp == OpK)
        {
            if ((node->child[0]->type != Integer) ||
                (node->child[1]->type != Integer)){
                printf("Erro na linha %d: Op aplicada a nao inteiro\n", node->lineno);
                Error = 1;
            }

            if ((node->attr.op == Eq) || (node->attr.op == Lt))
                node->type = Boolean;
            else
                node->type = Integer;
        }
        else if (node->kind.exp == IdK && symtab_lookup(node->attr.name) == -1)
        {
            printf("Erro na linha %d: Variavel %s utilizada porem nao declarada\n", node->lineno, node->attr.name);
            node->type = Integer;
            Error = 1;
        }
    }
    else if (node->nodekind == StmtK)
    {
        if (node->kind.stmt == IfK && node->child[0]->type == Integer){
            printf("Erro na linha %d: Teste if nao booleano\n", node->child[0]->lineno);
            Error = 1;
        }
        else if (node->kind.stmt == AssignK && node->child[0]->type != Integer){
            printf("Erro na linha %d: Assignment de valor nao inteiro\n", node->child[0]->lineno);
            Error = 1;
        }

        else if (node->kind.stmt == WriteK && node->child[0]->type != Integer){
            printf("Erro na linha %d: Write de valor nao inteiro\n", node->child[0]->lineno);
            Error = 1;
        }

        else if (node->kind.stmt == RepeatK && node->child[1]->type == Integer){
            printf("Erro na linha %d: Repeat test nao booleano\n", node->child[1]->lineno);
            Error = 1;
        }

    }
}





void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree, emptyFunc, checkNode);
}
