#include "fila.h"


Fila* fila_cria(){ //cria e aloca espaço da fila e inicializa a lista nula (vazia)
	Fila* nova = (Fila*)malloc(sizeof(Fila));
	nova->ini = NULL;
	nova->fim = NULL;
	return nova;
}

void fila_insere(Fila* fila, char* name){ //insere elemento smp no final da lista
	Lista* novo = (Lista*)malloc(sizeof(Lista)); //criando a alocando novo nó, ou seja, novo elemento da fila
	strcpy(novo->fileName, name);
	novo->prox = NULL; //porque smp inserimos no final da fila, o que significa inserir no fim da lista
	if(fila->fim != NULL){ //verifica se a fila não estava vazia
		fila->fim->prox = novo; //se a fila já tem elementos, o último passa a apontar pro novo (que entra atrás dele)
	}else{
		fila->ini = novo; //se a fila estava vazia, o novo elemento será também o primeiro
	}

	fila->fim = novo; //independente do caso, como o novo elemento smp é o último, o ponteiro pro fim da fila passa a apontar pra ele
}

int fila_vazia(Fila* fila){
	if(fila->fim == NULL){
		return 1;
	}

	return 0;
}

void fila_retira(Fila* fila, char* name){ //análogo ao pilha_pop
	Lista* aux;

	if(fila_vazia(fila)){ //aborta o programa
		printf("Fila vazia!\n");
		exit(1);
	}

	aux = fila->ini;
	strcpy(name, aux->fileName);
	fila->ini = aux->prox;
	
	if(fila->ini == NULL){ //verifica se ao remover o primeiro elemento a fila fica vazia, o que significa que ini e fim eram iguais e, portanto, há
		fila->fim = NULL;	//necessidade de atualizar o ponteiro do fim de fila também
	}

	free(aux);
}


void fila_libera(Fila* fila){

	Lista *t, *p = fila->ini;
	while(p != NULL){
		t = p->prox;
		free(p);
		p = t;
	}

	free(fila);
}