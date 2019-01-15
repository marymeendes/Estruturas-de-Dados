#include "dijkstra.h"

void incializa_vetor_auxiliar(Lista* lst, Vertice* vetor){
	Lista* p; //auxiliar para percorrer a lista
	int i = 0;

	for(p = lst; p != NULL; p = p->prox){
		vetor[i].v = p->vertice;
		vetor[i].distancia = -1;
		vetor[i].predecessor = -1;
		vetor[i].explorado = 0;	
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
		printf("Entre com os vizinhos de saída do vértice %d e o peso das arestas (-1 nos dois campos para encerrar):\n", vetor[i].v);
		do{
			scanf("%d", &vizinho);
			scanf("%d", &peso);
			if(vizinho != -1 && peso != -1){
				matriz[i][vizinho] = peso;
			}
		}while(vizinho != -1 && peso != -1);
	}

	imprime_matriz_adj(tam, matriz);
}

void imprime_matriz_adj(int tam, int matriz[tam][tam]){
	int i, j;

	printf("Matriz de Adjacências:\n");
	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
}

void imprime_vetor_vertices(int tam, Vertice* vetor){
	int i;

	printf("Vertice|Distancia|Predecessor|Explorado:\n");
	for(i = 0; i < tam; i++){
		printf("%d | ", vetor[i].v);
		printf("%d | ", vetor[i].distancia);
		printf("%d | ", vetor[i].predecessor);
		printf("%d\n", vetor[i].explorado);
	}
}

int calcula_infinito(int tam, int matriz[tam][tam]){ //somas todos os pesos das arestas + 1
	int i, j, soma = 0;

	for(i = 0; i < tam; i++){
		for(j = 0; j < tam; j++){
			if(matriz[i][j] != 0){
				soma += matriz[i][j];
			}
		}
	}

	return soma + 1;
}

void incializa(Vertice* vetor, int tam, int inf, Vertice* s){ //função do algoritmo da aula
	int i;

	for(i = 0; i < tam; i++){
		vetor[i].distancia = inf;
		vetor[i].predecessor = -1;
	}

	s->distancia = 0;
}

void relaxa(Vertice* u, Vertice* v, int tam, int matriz[tam][tam]){ //função do algoritmo da aula
	int dist = matriz[u->v][v->v];

	if(u->distancia + dist < v->distancia){
		v->distancia = u->distancia + dist;
		v->predecessor = u->v;
	}
}

void insere_heap(int tam, Vertice* H[tam+1], Vertice* v){
	int ult, i;

	for(i = 1; i < tam+1; i++){ //calculando últimpa posição preenchida antes da inserção
		if(H[i] == NULL){
			ult = i - 1; // essa aqui!
			break;
		}
	}

	ult = ult + 1;
	int k = ult;

	while((k/2) && (v->distancia < H[k/2]->distancia)){
		H[k] = H[k/2];
		k = k/2;
	}

	H[k] = v;
}

Vertice* remove_heap(int tam, Vertice* H[tam+1]){
	Vertice *x, *y;
	int ult, i;

	for(i = 1; i < tam+1; i++){ //calculando última posição preenchida antes da remoção
		if(H[i] == NULL){
			ult = i - 1; // essa aqui!
			break;
		}else if(i + 1 == tam+1){ //cheguei no último e ele não tava vazio
			ult = i;
		}
	}

	y = H[1];
	x = H[ult];

	//apago a ultima posicao
	H[ult] = NULL;

	ult = ult - 1;
	int k = 1;

	while((2*k <= ult) && (((H[2*k] != NULL) && (x->distancia >= H[2*k]->distancia)) || ((H[2*k + 1] != NULL) && (x->distancia >= H[2*k + 1]->distancia)))){
		if(H[2*k] != NULL && H[2*k + 1] != NULL){
			if(H[2*k]->distancia < H[2*k + 1]->distancia){
				H[k] = H[2*k];
				k = 2*k;
			}else{
				H[k] = H[2*k + 1];
				k = 2*k+1;
			}
		}else if(H[2*k] != NULL){
			H[k] = H[2*k];
			k = 2*k;
		}else if(H[2*k + 1] != NULL){
			H[k] = H[2*k + 1];
			k = 2*k+1;
		}	
	}

	if(ult != 0){ //pq se for igual não há necessidade de recolocar o elemento na fila, ela esvaziou!
		H[k] = x;
	}

	return y;
}

void zera_heap(int tam, Vertice* H[tam+1]){
	int i;
	for(i = 0; i < tam+1; i++){
		H[i] = NULL;
	}
}

int heap_vazia(int tam, Vertice* H[tam+1]){
	int i, vazia = 1; //começo considerando que ela está vazia

	for(i = 0; i < tam+1; i++){
		if(H[i] != NULL){
			vazia = 0;
		}
	}

	return vazia;
}

void imprime_heap(int tam, Vertice* H[tam+1]){
	int i;

	printf("------------------\n");
	for(i = 1; i < tam+1; i++){
		if(H[i] != NULL){
			printf("%d\n", H[i]->v);
		}
	}

	printf("------------------\n");
}

void dijkstra(int tam, int matriz[tam][tam], Vertice* vetor, Vertice* s){
	int infinito = calcula_infinito(tam, matriz);

	incializa(vetor, tam, infinito, s);

	int i, j;
	Vertice* Heap[tam+1];
	zera_heap(tam, Heap);

	insere_heap(tam, Heap, &vetor[0]); //insere-se na heap o s somente

	//imprime_heap(tam, Heap);////teste

	Vertice* u;

	while(!heap_vazia(tam, Heap)){
		u = remove_heap(tam, Heap);

		//imprime_heap(tam, Heap); ////teste

		i = u->v;
		for(j = 0; j < tam; j++){
			if(matriz[i][j] != 0 && vetor[j].explorado == 0){
				relaxa(u, &vetor[j], tam, matriz);
			}
		}
		u->explorado = 1;

		//atualização da heap
		zera_heap(tam, Heap); 
		for(i = 0; i < tam; i++){ //a cada passada insere-se na heap somente os vértices não explorados
			if(vetor[i].explorado == 0){ //pois não faz sentido retornar a esses vértices
				insere_heap(tam, Heap, &vetor[i]);
			}
		}
	}
}

