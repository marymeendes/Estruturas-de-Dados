#include "lista.h"

Lista* lista_cria(){ //cria lista vazia
	return NULL;
}

Lista* lista_insere(Lista* lst, int v){ //insere no ínicio da lista e retorna a lista atualizada
	
	Lista* novo = (Lista*)malloc(sizeof(Lista));
	novo->vertice = v;
	novo->prox = lst;

	return novo;
}

int lista_vazia(Lista* lst){ //verifica se o ponteiro que representa a lista aponta pra null, se sim, lista vazia, senão lista ocupada

	return (lst == NULL);
}

void lista_imprime(Lista* lst){
	Lista* p; //auxiliar para percorrer a lista
	for(p = lst; p != NULL; p = p->prox){
		printf("Vértice %d\n", p->vertice);
	} 
}

Lista* lista_busca(Lista* lst, int v){ //varre a lista procurando pelo elemento com o valor desejado, se encontrar, o retorna, senão, retorna null
	Lista* p;
	for(p = lst; p!= NULL; p = p->prox){
		if(p->vertice == v){
			return p;
		}
	}

	return NULL;
}

Lista* lista_retira(Lista* lst, int v){
	Lista* anterior = NULL; //ponteiro para guardar o elemento anterior ao que se quer excluir
	Lista* p = lst; //variável auxiliar para percorrer a lista

	while(p != NULL && p->vertice != v){
		anterior = p;
		p = p->prox;
	}

	if(p == NULL){
		return lst; //elemento a ser excluído não foi encontrado e portanto, retorna lista original
	}

	if(anterior == NULL){
		lst = p->prox;
	}else{
		anterior->prox = p->prox;
	}

	free(p);

	return lst;
}

void lista_libera(Lista* lst){
	Lista* p = lst; //auxiliar para percorrer a lista
	while(p != NULL){
		Lista* t = p->prox; //auxiliar pra salvar o ponteiro para o próximo elemento
		free(p);
		p = t; //atualiza o p
	}
}

Lista* lista_insere_ordenado(Lista* lst, int v){
	Lista* novo;
	Lista* anterior = NULL;
	Lista* p = lst;

	while(p != NULL && p->vertice < v){ //busco a posição adequada de inserção, ou seja, entre quais elementos o novo será inserido
		anterior = p;
		p = p->prox;
	}
	//criação do novo elemento
	novo = (Lista*)malloc(sizeof(Lista));
	novo->vertice = v;

	//inserindo o elemento e mantendo o encadeamento
	if(anterior == NULL){
		novo->prox = lst;
		lst = novo;
	}else{
		novo->prox = anterior->prox;
		anterior->prox = novo;
	}

	return lst; //retorno a lista atualizada
}

Lista* recebe_vertices(Lista* lst, int* tam){
	int v;
	int qtde = 0;

	printf("Entre com os vértices do grafo (digite -1 para encerrar):\n");
	do{
		scanf("%d", &v);
		getchar();
		if(v != -1){
			lst = lista_insere_ordenado(lst, v);
			qtde++;
		}
	}while(v != -1);

	//lista_imprime(lst);

	*tam = qtde;

	return lst;
}