#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
	int vertice;
	struct lista* prox;
}Lista;

Lista* lista_cria();
Lista* lista_insere(Lista* lst, int v);
int lista_vazia(Lista* lst);
void lista_imprime(Lista* lst);
Lista* lista_busca(Lista* lst, int v);
Lista* lista_retira(Lista* lst, int v);
void lista_libera(Lista* lst);
Lista* lista_insere_ordenado(Lista* lst, int v);
Lista* recebe_vertices(Lista* lst, int* tam);

#endif