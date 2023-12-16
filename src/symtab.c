#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

typedef struct ListaLinhasStruct
{
    int numeroLinha;
    struct ListaLinhasStruct *proximo;
} *ListaLinhas;

typedef struct LinhaTabelaStruct
{
    char *nome;
    ListaLinhas linhas;
    int localMem;
} *LinhaTabela;


static LinhaTabela Tabela[200];
int location = 0;

void symtab_insert(char *nome, int numeroLinha)
{
    int i = 0;
    while (Tabela[i] != NULL && strcmp(nome, Tabela[i]->nome) != 0)
        i++;
    LinhaTabela linha = Tabela[i];
    if (linha == NULL)
    {
        linha = (LinhaTabela)malloc(sizeof(struct LinhaTabelaStruct));
        linha->nome = nome;
        linha->linhas = (ListaLinhas)malloc(sizeof(struct ListaLinhasStruct));
        linha->linhas->numeroLinha = numeroLinha;
        linha->localMem = location;
        location++;
        linha->linhas->proximo = NULL;
        Tabela[i] = linha;
    }
    else
    {
        ListaLinhas linhasVariavel = linha->linhas;
        while (linhasVariavel->proximo != NULL)
            linhasVariavel = linhasVariavel->proximo;

        linhasVariavel->proximo = (ListaLinhas)malloc(sizeof(struct ListaLinhasStruct));
        linhasVariavel->proximo->numeroLinha = numeroLinha;
        linhasVariavel->proximo->proximo = NULL;
    }

}

int symtab_lookup(char *nome)
{
    int i = 0;
    while (Tabela[i] != NULL && strcmp(nome, Tabela[i]->nome) != 0)
        i++;
    LinhaTabela linha = Tabela[i];
    if (linha == NULL)
        return -1;
    else
        return linha->localMem;
}

void printSymTab()
{
    int i = 0;
    printf("Nome da Variável  Local   Número das linhas\n");
    printf("----------------  -----   -----------------\n");
    while (Tabela[i] != NULL) {
        LinhaTabela linha = Tabela[i];
        ListaLinhas linhasVariavel = linha->linhas;
        printf("%-17s ", linha->nome);
        printf("%-4d  ", linha->localMem);
        while (linhasVariavel != NULL)
        {
            printf("%4d ", linhasVariavel->numeroLinha);
            linhasVariavel = linhasVariavel->proximo;
        }
        printf("\n");
        i++;
    }
    
}
