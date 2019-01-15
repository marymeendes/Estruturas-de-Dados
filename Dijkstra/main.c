#include "dijkstra.h"

int main(void){

	int tam;
	Lista* lst = lista_cria();
	lst = recebe_vertices(lst, &tam);

	Vertice vetor_aux[tam]; //representa o struct Vertice que comtém as informações de distancia, predecessor e exploração dos vértices

	incializa_vetor_auxiliar(lst, vetor_aux);

	int matriz_adj[tam][tam]; //matriz de adjacência: representação de grafos utilizada, aqui podemos ver as arestas e seus pesos

	monta_matriz_adj(tam, matriz_adj, vetor_aux);

	dijkstra(tam, matriz_adj, vetor_aux, &vetor_aux[0]);

	imprime_vetor_vertices(tam, vetor_aux); //resultado

	lista_libera(lst);

	return 0;
}
