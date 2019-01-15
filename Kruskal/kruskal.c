#include "kruskal.h"

void incializa_vetor_vertice(ListaV* lst, Vertice* vetor){
	ListaV* p; //auxiliar para percorrer a lista
	int i = 0;

	for(p = lst; p != NULL; p = p->prox){
		vetor[i].v = p->vertice;	
		i++;
	}
}

void monta_matriz_adj(int tam, int matriz[tam][tam], Vertice* vetor){
	int i, j, vizinho, peso;

	//zerando matriz
	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			matriz[i][j] = 0;
		}
	}

	//preenchendo matriz com as adjacências
	for(i = 0; i < tam; i++){
		printf("Entre com os vizinhos do vértice %d e o peso das arestas (entre com -1 e 0 para encerrar):\n", vetor[i].v);
		do{
			scanf("%d", &vizinho);
			scanf("%d", &peso);
			if(vizinho != -1 && peso != 0){
				matriz[i][vizinho] = peso;
			}
		}while(vizinho != -1 && peso != -1);
	}

	printf("\nMatriz de adjacência de G:\n");
	imprime_matriz_adj(tam, matriz);
}

void imprime_matriz_adj(int tam, int matriz[tam][tam]){
	int i, j;

	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
}

ListaE* monta_lista_arestas(int tam, int matriz[tam][tam], int* size){
	int i, j, qtde = 0;
	ListaE* lst = listaE_cria();

	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			if(i < j && matriz[i][j] != 0){
				lst = listaE_insere_ordenado(lst, i, j, matriz[i][j]);
				qtde++;
			}
		}
	}

	*size = qtde;

	return lst;
}

void incializa_vetor_aresta(ListaE* lst, Aresta* vetor){
	ListaE* p; //auxiliar para percorrer a lista
	int i = 0;

	for(p = lst; p != NULL; p = p->prox){
		vetor[i].extremo1 = p->extremo1;
		vetor[i].extremo2 = p->extremo2;
		vetor[i].peso = p->peso;
		i++;
	}
}

void imprime_vetor_aresta(int size, Aresta* vetor){
	int i;
	for(i = 0; i < size; i++){
		printf("Aresta (%d, %d), peso %d.\n", vetor[i].extremo1, vetor[i].extremo2, vetor[i].peso);
	}
}
void imprime_vetor_vertice(int tam, Vertice* vetor){
	int i;
	for(i = 0; i < tam; i++){
		printf("%d\n", vetor[i].v);
	}
}

int pertence(Aresta a, Vertice* corte, int tam){
	int i, busca1 = 0, busca2 = 0;

	for(i = 0; i < tam; i++){
		if(corte[i].v == a.extremo1){
			busca1 = 1;
		}

		if(corte[i].v == a.extremo2){
			busca2 = 1;
		}
	}

	if(busca1 && busca2)
		return 3;
	else if(busca1 == 0 && busca2 == 0)
		return 0;
	else if(busca1)
		return 1;
	else if(busca2)
		return 2;
}

int kruskal(int tam, int size, int novo_grafo[tam][tam], Vertice* corte, Aresta* arestas){
	int i, j, pos, busca, custo = 0; //pos = posição de inserção no conjunto de vertices
	//zerando matriz, pois está sem nenhuma aresta
	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			novo_grafo[i][j] = 0;
		}
	}
	
	//preenchendo corte sem vértices
	for(i = 0; i < tam; i++){
		corte[i].v = -1;
	}

	pos = 0;

	for(i = 0; i < size; i++){
		busca = pertence(arestas[i], corte, tam);
		if(busca < 3){
			novo_grafo[arestas[i].extremo1][arestas[i].extremo2] = arestas[i].peso;
			novo_grafo[arestas[i].extremo2][arestas[i].extremo1] = arestas[i].peso;
			custo += arestas[i].peso;
			if(busca == 0){
				corte[pos].v = arestas[i].extremo1;
				corte[pos+1].v = arestas[i].extremo2;
				pos += 2;
			}else if(busca == 1){
				corte[pos].v = arestas[i].extremo2;
				pos += 1;
			}else if(busca == 2){
				corte[pos].v = arestas[i].extremo1;
				pos += 1;
			}
		}
	}

	return custo;
}