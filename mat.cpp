#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef struct lista
{
    int tamInfo;  //sizeof(reg)
    int tamLista; //rows x columns
    int rowAtual; //saber onde esta
    int colAtual; //saber onde esta
    row *rowMovel; //vai pra linha
}lista;

typedef struct row
{   

    row *prox; //row anterior
    row *ant; //row seguinte
    col *colMovel; //vai pra coluna
}row;

typedef struct column
{
    col *ant; //col anterior
    col *prox; //col seguinte
    void *valor; //valor: ... -2 -1 0 1 2 ...
}col;

typedef struct reg
{
    int dados;
}reg;

bool cria(lista **l, int tamInfo);
bool insereNaLista(lista *l, void *novo);
int tamanhoLista(lista *l);
void destruir(lista **l);
bool buscaNaPos(lista *l, void *reg, int posicao);

int main()
{
    return 0;
}