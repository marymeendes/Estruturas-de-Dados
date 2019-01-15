#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "listaV.h"
#include "listaE.h"

typedef struct vertice
{
	int v;
}Vertice;

typedef struct aresta
{
	int extremo1;
	int extremo2;
	int peso;
}Aresta;

void incializa_vetor_vertice(ListaV* lst, Vertice* vetor);
void incializa_vetor_aresta(ListaE* lst, Aresta* vetor);
void monta_matriz_adj(int tam, int matriz[tam][tam], Vertice* vetor);
void imprime_matriz_adj(int tam, int matriz[tam][tam]);
ListaE* monta_lista_arestas(int tam, int matriz[tam][tam], int* size);
void imprime_vetor_aresta(int size, Aresta* vetor);
void imprime_vetor_vertice(int tam, Vertice* vetor);
int pertence(Aresta a, Vertice* corte, int tam);
int kruskal(int tam, int size, int novo_grafo[tam][tam], Vertice* corte, Aresta* arestas);

#endif