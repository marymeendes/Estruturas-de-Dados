#include "listaE.h"

ListaE* listaE_cria(){ //cria lista vazia
	return NULL;
}

ListaE* listaE_insere(ListaE* lst, int v, int u, int p){ //insere no ínicio da lista e retorna a lista atualizada
	
	ListaE* novo = (ListaE*)malloc(sizeof(ListaE));
	novo->extremo1 = v;
	novo->extremo2 = u;
	novo->peso = p;
	novo->prox = lst;

	return novo;
}

int listaE_vazia(ListaE* lst){ //verifica se o ponteiro que representa a lista aponta pra null, se sim, lista vazia, senão lista ocupada

	return (lst == NULL);
}

void listaE_imprime(ListaE* lst){
	ListaE* p; //auxiliar para percorrer a lista
	for(p = lst; p != NULL; p = p->prox){
		printf("Aresta (%d, %d), peso %d.\n", p->extremo1, p->extremo2, p->peso);
	} 
}

ListaE* listaE_busca(ListaE* lst, int v, int u){ //varre a lista procurando pelo elemento com o valor desejado, se encontrar, o retorna, senão, retorna null
	ListaE* p;
	for(p = lst; p!= NULL; p = p->prox){
		if((p->extremo1 == v || p->extremo2 == v) && (p->extremo1 == u || p->extremo2 == u)){
			return p;
		}
	}

	return NULL;
}

ListaE* listaE_retira(ListaE* lst, int v, int u){
	ListaE* anterior = NULL; //ponteiro para guardar o elemento anterior ao que se quer excluir
	ListaE* p = lst; //variável auxiliar para percorrer a lista

	while(p != NULL && (p->extremo1 != v || p->extremo2 != v) && (p->extremo1 != u || p->extremo2 != u)){
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

void listaE_libera(ListaE* lst){
	ListaE* p = lst; //auxiliar para percorrer a lista
	while(p != NULL){
		ListaE* t = p->prox; //auxiliar pra salvar o ponteiro para o próximo elemento
		free(p);
		p = t; //atualiza o p
	}
}

ListaE* listaE_insere_ordenado(ListaE* lst, int v, int u, int peso){
	ListaE* novo;
	ListaE* anterior = NULL;
	ListaE* p = lst;
	while(p != NULL && p->peso < peso){ //busco a posição adequada de inserção, ou seja, entre quais elementos o novo será inserido
		anterior = p;
		p = p->prox;
	}
	//criação do novo elemento
	novo = (ListaE*)malloc(sizeof(ListaE));
	novo->extremo1 = v;
	novo->extremo2 = u;
	novo->peso = peso;
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