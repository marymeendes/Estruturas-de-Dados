#ifndef LISTAE_H
#define LISTAE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct listaE{
	int extremo1;
	int extremo2;
	int peso;
	struct listaE* prox;
}ListaE;

ListaE* listaE_cria();
ListaE* listaE_insere(ListaE* lst, int v, int u, int p);
int listaE_vazia(ListaE* lst);
void listaE_imprime(ListaE* lst);
ListaE* listaE_busca(ListaE* lst, int v, int u);
ListaE* listaE_retira(ListaE* lst, int v, int u);
void listaE_libera(ListaE* lst);
ListaE* listaE_insere_ordenado(ListaE* lst, int v, int u, int peso);

#endif