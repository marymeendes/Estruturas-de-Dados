#include <stdio.h>
#include <stdlib.h>

struct elemento{ //representá nó da lista
	float info;
	struct elemento* prox;
};
typedef struct elemento Elemento;

struct pilha{ //aponta pro primeiro elemento da lista (que seria o topo da pilha)
	Elemento* primeiro; //pilha->primeiro é como se fosse o lst da lista
};
typedef struct pilha Pilha;

////// PROTÓTIPOS ///////

Pilha* pilha_cria();
void pilha_push(Pilha* pilha, float val);
float pilha_pop(Pilha* pilha);
int pilha_vazia(Pilha* pilha);
void pilha_libera(Pilha* pilha);

Pilha* pilha_cria(){ //crio e aloco espaço pra pilha e inicia lista com NULL
	Pilha* nova = (Pilha*)malloc(sizeof(Pilha));
	nova->primeiro = NULL;
	return nova;
}

void pilha_push(Pilha* pilha, float val){ //cria elemento e o coloca no topo de pilha (que seria o início da lista)
	Elemento* novo = (Elemento*)malloc(sizeof(Elemento));
	novo->info = val;
	novo->prox = pilha->primeiro;
	pilha->primeiro = novo;
}

float pilha_pop(Pilha* pilha){ //retira o elemento no topo da pilha (que seria o primeiro elemento da lista, que é referenciado pela pilha)
	Elemento* aux;
	float val;
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

int pilha_vazia(Pilha* pilha){
	if(pilha->primeiro == NULL){
		return 1;
	}

	return 0;
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



