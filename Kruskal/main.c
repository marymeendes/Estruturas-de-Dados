#include "kruskal.h"

int main(void){

	int tamV;
	ListaV* lstV = listaV_cria();
	lstV = recebe_vertices(lstV, &tamV); //recebe os vértices do usuário e os coloca ordenados em uma lista auxiliar

	Vertice vetor_v[tamV];
	incializa_vetor_vertice(lstV, vetor_v); //essa lista é utilizada para preencher um vetor de vertices (pois o vetor é mais fácil acessar)

	//imprime_vetor_vertice(tamV, vetor_v);

	int matriz_adj[tamV][tamV];
	monta_matriz_adj(tamV, matriz_adj, vetor_v); //recebe os vizinhos de cada vértice e o peso das arestas e monta a matriz de adjacência de G

	int tamE;
	ListaE* lstE = listaE_cria();
	lstE = monta_lista_arestas(tamV, matriz_adj, &tamE); //a partir da matriz, monta-se uma lista com as arestas ordenadas por peso

	//listaE_imprime(lstE);
	
	Aresta vetor_e[tamE];
	incializa_vetor_aresta(lstE, vetor_e); //essa lista é utilizada para preencher um vetor de arestas (pelo mesmo motivo que foi feito com os vértices)
	
	Vertice corte[tamV]; //um vetor auxiliar para o corte de vértices é criado, ele ajudará a verificar quais arestas selecionar na função kruskal

	//imprime_vetor_aresta(tamE, vetor_e);

	int matriz_adj_tree[tamV][tamV]; //matriz de adjacência para a MST é criada
	int custo = kruskal(tamV, tamE, matriz_adj_tree, corte, vetor_e); //função kruskal para construir a matriz retorna o custo total desta

	printf("\nMatriz de adjacência da MST de G:\n");
	imprime_matriz_adj(tamV, matriz_adj_tree);//a MST é impressa

	printf("\nC(MST) = %d \n", custo);//seu custo tbm

	listaV_libera(lstV);
	listaE_libera(lstE);

	return 0;
}
