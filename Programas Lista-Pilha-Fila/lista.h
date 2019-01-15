#include <stdio.h>
#include <stdlib.h>

typedef struct lista Lista;

struct lista{
	int info;
	Lista* prox;
}

////// PROTÓTIPOS ///////

Lista* lista_cria();
Lista* lista_insere(Lista* lst, int val);
int lista_vazia(Lista* lst);
void lista_imprime(Lista* lst);
Lista* lista_busca(Lista* lst, int val);
Lista* lista_retira(Lista* lst, int val);
void lista_libera(Lista* lst);
Lista* lista_insere_ordenado(Lista* lst, int val);
void lcircular_imprime(Lista* lst);
Lista* lcircular_insere(Lista* lst, int val);

Lista* lista_cria(){ //cria lista vazia
	return NULL;
}

Lista* lista_insere(Lista* lst, int val){ //insere no ínicio da lista e retorna a lista atualizada
	
	Lista* novo = (Lista*)malloc(sizeof(Lista));
	novo->info = val;
	novo->prox = lst;

	return novo;
}

int lista_vazia(Lista* lst){ //verifica se o ponteiro que representa a lista aponta pra null, se sim, lista vazia, senão lista ocupada

	return (lst == NULL);
}

void lista_imprime(Lista* lst){
	Lista* p; //auxiliar para percorrer a lista
	for(p = lst; p != NULL; p = p->prox){
		printf("Elemento %d\n", p->info);
	} 
}

Lista* lista_busca(Lista* lst, int val){ //varre a lista procurando pelo elemento com o valor desejado, se encontrar, o retorna, senão, retorna null
	Lista* p;
	for(p = lst; p!= NULL; p = p->prox){
		if(p->info == val){
			return p;
		}
	}

	return NULL;
}

Lista* lista_retira(Lista* lst, int val){
	Lista* anterior = NULL; //ponteiro para guardar o elemento anterior ao que se quer excluir
	Lista* p = lst; //variável auxiliar para percorrer a lista

	while(p != NULL && p->info != val){
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

Lista* lista_insere_ordenado(Lista* lst, int val){
	Lista* novo;
	Lista* anterior = NULL;
	Lista* p = lst;

	while(p != NULL && p->info < val){ //busco a posição adequada de inserção, ou seja, entre quais elementos o novo será inserido
		anterior = p;
		p = p->prox;
	}
	//criação do novo elemento
	novo = (Lista*)malloc(sizeof(Lista));
	novo->info = val;

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

void lcircular_imprime(Lista* lst){ //para lista circular
	Lista* p = lst;

	if(p){ //verifica se há elemento na lista
		do{
			printf("Elemento %d\n", p->info);
			p = p->prox;
		}while(p != lst);
	}
}


Lista* lcircular_insere(Lista* lst, int val){ //insere no ínicio da lista e retorna a lista atualizada
	
	Lista* novo = (Lista*)malloc(sizeof(Lista));
	novo->info = val;
	novo->prox = lst;

	if(lst != NULL){ //isso significa que há um último que precisa ter o ponteiro do prox atualizado
		Lista* p = lst;
		do{
			p = p->prox;
		}while(p != lst); //ao sair do loop, p estará apontando para o último da lista
		p->prox = novo; //atualizo o último para apontar para o novo primeiro
	}else{
		novo->prox = novo; //se a lista estava vazia, o novo->prox deve apontar pra ele mesmo, pois é o primeiro e o último
	}

	return novo;
}