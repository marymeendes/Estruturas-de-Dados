#include "arvore.h"

Arv* arv_criavazia(){
	return NULL;
}

Arv* arv_cria(int c, int i, Arv* sae, Arv* sad){ //cria nó raiz
	Arv* p = (Arv*)malloc(sizeof(Arv));
	p->info.val = c;
	p->info.fileId = i;
	p->esq = sae;
	p->dir = sad;
	return p;
}

int arv_vazia(Arv* a){
	return a == NULL; //retorna 1 se arvore vazia e 0 se arvore não vazia
}

Arv* arv_libera(Arv* a){
	if(!arv_vazia(a)){
		arv_libera(a->esq); //libera sae
		arv_libera(a->dir); //libera dir
		free(a); //libera raiz
	}

	return NULL;
}

int arv_pertence(Arv* a, int c){
	if(arv_vazia(a)){
		return 0; //árvore vazia: não encontrou
	}else{
		return a->info.val == c || arv_pertence(a->esq, c) || arv_pertence(a->dir, c);
	}
}

void arv_imprime(Arv* a){
	printf("<");
	if(!arv_vazia(a)){
		printf("%d ", a->info.val); //imprimo raiz
		arv_imprime(a->esq); //imprimo sae
		arv_imprime(a->dir); //imprimo sad
	}
	printf(">");
}

Arv* arv_compara(Arv* a1, Arv* a2){
	if(!arv_vazia(a1) && !arv_vazia(a2)){
		if(a1->info.val < a2->info.val){
			return a1;
		}else if(a2->info.val < a1->info.val){
			return a2;
		}else if(a1->info.val == 1001 && a2->info.val == 1001){
			return a1;
		}else if(a1->info.val == a2->info.val){
			return a1;
		}

	}else{
		return NULL;
	}

	return NULL;
}

Arv* arv_igualdadePaterna(Arv* a){
	if(a->esq != NULL && a->dir != NULL){
		if(a->info.val == a->esq->info.val){
			return a->esq;
		}else if(a->info.val == a->dir->info.val){
			return a->dir;
		}
	}else{
		return NULL;
	}
	return NULL;
}

int arv_verificacao(Arv* a){
	if(a->esq == NULL && a->dir == NULL){
		if(a->info.val == 1001){
			return 1;
		}else{
			return 0;
		}
	}else{
		return arv_verificacao(a->esq) && arv_verificacao(a->dir);
	}
}