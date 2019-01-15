#include "pilha.h"

Pilha* pilha_cria(){ //crio e aloco espaço pra pilha e inicia lista com NULL
	Pilha* nova = (Pilha*)malloc(sizeof(Pilha));
	nova->primeiro = NULL;
	return nova;
}

void pilha_push(Pilha* pilha, Arv* val){ //cria elemento e o coloca no topo de pilha (que seria o início da lista)
	Elemento* novo = (Elemento*)malloc(sizeof(Elemento));
	novo->info = val;
	novo->prox = pilha->primeiro;
	pilha->primeiro = novo;
}

int pilha_vazia(Pilha* pilha){
	if(pilha->primeiro == NULL){
		return 1;
	}

	return 0;
}

Arv* pilha_pop(Pilha* pilha){ //retira o elemento no topo da pilha (que seria o primeiro elemento da lista, que é referenciado pela pilha)
	Elemento* aux;
	Arv* val;
	if(pilha_vazia(pilha)){ //aborta programa
		printf("Pilha Vazia!\n");
		exit(1);
	}
	aux = pilha->primeiro;
	pilha->primeiro = aux->prox;
	val = aux->info;
	free(aux);

	return val;
}

void pilha_libera(Pilha* pilha){

	Elemento *t, *p = pilha->primeiro;
	while(p != NULL){ //processo análogo ao de liberação de lista
		t = p->prox;
		free(p);
		p = t;
	}

	//liberação da pilha

	free(pilha);
}



