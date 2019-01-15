#ifndef LISTAV_H
#define LISTAV_H

#include <stdio.h>
#include <stdlib.h>

typedef struct listaV{
	int vertice;
	struct listaV* prox;
}ListaV;

ListaV* listaV_cria();
ListaV* listaV_insere(ListaV* lst, int v);
int listaV_vazia(ListaV* lst);
void listaV_imprime(ListaV* lst);
ListaV* listaV_busca(ListaV* lst, int v);
ListaV* listaV_retira(ListaV* lst, int v);
void listaV_libera(ListaV* lst);
ListaV* listaV_insere_ordenado(ListaV* lst, int v);
ListaV* recebe_vertices(ListaV* lst, int* tam);

#endif