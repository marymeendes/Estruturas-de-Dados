#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "lista.h"

typedef struct vertice{
	int v;
	int distancia;
	int predecessor;
	int explorado;
}Vertice;

void incializa_vetor_auxiliar(Lista* lst, Vertice* vetor);
void monta_matriz_adj(int tam, int matriz[tam][tam], Vertice* vetor);
void imprime_matriz_adj(int tam, int matriz[tam][tam]);
void imprime_vetor_vertices(int tam, Vertice* vetor);
int calcula_infinito(int tam, int matriz[tam][tam]);
void incializa(Vertice* vetor, int tam, int inf, Vertice* s);
void relaxa(Vertice* u, Vertice* v, int tam, int matriz[tam][tam]);
void insere_heap(int tam, Vertice* H[tam+1], Vertice* v);
Vertice* remove_heap(int tam, Vertice* H[tam+1]);
void zera_heap(int tam, Vertice* H[tam+1]);
int heap_vazia(int tam, Vertice* H[tam+1]);
void imprime_heap(int tam, Vertice* H[tam+1]);
void dijkstra(int tam, int matriz[tam][tam], Vertice* vetor, Vertice* s);

#endif