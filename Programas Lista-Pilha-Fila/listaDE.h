#include <stdio.h>
#include <stdlib.h>

typedef struct lista2 Lista2;

struct lista2{
	int info;
	Lista2* ant;
	Lista2* prox;
}

////// PROTÓTIPOS ///////

Lista2* lista2_cria();
Lista2* lista2_insere(Lista2* lst2, int val);
Lista2* lista2_busca(Lista2* lst2, int val);
Lista2* lista2_retira(Lista2* lst2, int val);
void lista2_libera(Lista2* lst2);

Lista2* lista2_cria(){
	return NULL;
}

Lista2* lista2_insere(Lista2* lst2, int val){ //no início

	Lista2* novo = (Lista2*)malloc(sizeof(Lista2));
	novo->info = val;
	novo->prox = lst2;
	novo->ant = NULL;

	if(lst2 != NULL){ //verifica se a lista está vazia ou não
		lst2->ant = novo;
	}

	return novo; //lista atualiza
}

Lista2* lista2_busca(Lista2* lst2, int val){
	Lista2* p;
	for(p = lst2; p != NULL; p = p->prox){
		if(p->info == val){
			return p;
		}
	}

	return NULL;
}

Lista2* lista2_retira(Lista2* lst2, int val){
	
	Lista2* p = lista2_busca(lst2, val);

	if(p == NULL){ //elemento não encontrado, retorna lista inalterada
		return lst2;
	}

	if(lst2 == p){ //se for o primeiro elemento (ponteiro da lista deve apontar para p->prox)
		lst2 = p->prox;
	}else{
		p->ant->prox = p->prox; //senão for o primeiro o elemento (garantindo que há um p->ant)
	}

	if(p->prox != NULL){ //p->prox existe, p->prox->ant deve apontar pra p->ant
		p->prox->ant = p->ant;
	}

	/*if(p->ant != NULL && p->prox != NULL){
		p->ant->prox = p->prox;
		p->prox->ant = p->ant;
	}else if(p->ant == NULL){
		p->prox->ant = NULL;
		lst2 = p->prox;
	}else if(p->prox == NULL){
		p->ant->prox = NULL;
	}*/

	free(p); //libero p

	return lst2; //retorno lista atualizada
}

void lista2_libera(Lista2* lst2){ //igual a liberação de lista encadeada simples
	Lista2* p = lst2; //auxiliar para percorrer a lista
	while(p != NULL){
		Lista2* t = p->prox; //auxiliar pra salvar o ponteiro para o próximo elemento
		free(p);
		p = t; //atualiza o p
	}
}
