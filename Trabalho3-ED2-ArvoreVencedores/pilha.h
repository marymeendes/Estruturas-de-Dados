#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

struct elemento{ //representá nó da lista
	Arv* info;
	struct elemento* prox;
};
typedef struct elemento Elemento;

struct pilha{ //aponta pro primeiro elemento da lista (que seria o topo da pilha)
	Elemento* primeiro; //pilha->primeiro é como se fosse o lst da lista
};
typedef struct pilha Pilha;

////// PROTÓTIPOS ///////

Pilha* pilha_cria();
void pilha_push(Pilha* pilha, Arv* val);
Arv* pilha_pop(Pilha* pilha);
int pilha_vazia(Pilha* pilha);
void pilha_libera(Pilha* pilha);



