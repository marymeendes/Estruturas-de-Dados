#include "listaV.h"

ListaV* listaV_cria(){ //cria lista vazia
	return NULL;
}

ListaV* listaV_insere(ListaV* lst, int v){ //insere no ínicio da lista e retorna a lista atualizada
	
	ListaV* novo = (ListaV*)malloc(sizeof(ListaV));
	novo->vertice = v;
	novo->prox = lst;

	return novo;
}

int listaV_vazia(ListaV* lst){ //verifica se o ponteiro que representa a lista aponta pra null, se sim, lista vazia, senão lista ocupada

	return (lst == NULL);
}

void listaV_imprime(ListaV* lst){
	ListaV* p; //auxiliar para percorrer a lista
	for(p = lst; p != NULL; p = p->prox){
		printf("Elemento %d\n", p->vertice);
	} 
}

ListaV* listaV_busca(ListaV* lst, int v){ //varre a lista procurando pelo elemento com o valor desejado, se encontrar, o retorna, senão, retorna null
	ListaV* p;
	for(p = lst; p!= NULL; p = p->prox){
		if(p->vertice == v){
			return p;
		}
	}

	return NULL;
}

ListaV* listaV_retira(ListaV* lst, int v){
	ListaV* anterior = NULL; //ponteiro para guardar o elemento anterior ao que se quer excluir
	ListaV* p = lst; //variável auxiliar para percorrer a lista

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

void listaV_libera(ListaV* lst){
	ListaV* p = lst; //auxiliar para percorrer a lista
	while(p != NULL){
		ListaV* t = p->prox; //auxiliar pra salvar o ponteiro para o próximo elemento
		free(p);
		p = t; //atualiza o p
	}
}

ListaV* listaV_insere_ordenado(ListaV* lst, int v){
	ListaV* novo;
	ListaV* anterior = NULL;
	ListaV* p = lst;

	while(p != NULL && p->vertice < v){ //busco a posição adequada de inserção, ou seja, entre quais elementos o novo será inserido
		anterior = p;
		p = p->prox;
	}
	//criação do novo elemento
	novo = (ListaV*)malloc(sizeof(ListaV));
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

ListaV* recebe_vertices(ListaV* lst, int* tam){
	int v;
	int qtde = 0;

	printf("Entre com os vértices do grafo (digite -1 para encerrar):\n");
	do{
		scanf("%d", &v);
		getchar();
		if(v != -1){
			lst = listaV_insere_ordenado(lst, v);
			qtde++;
		}
	}while(v != -1);

	listaV_imprime(lst);

	*tam = qtde;

	return lst;
}