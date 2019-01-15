#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RET 0
#define TRI 1
#define CIR 2

typedef struct retangulo{
	float b,h;
}Retangulo;


typedef struct triangulo{
	float b,h;
}Triangulo;


typedef struct circulo{
	float r;
}Circulo;

struct lista{
	int tipo;
	void* item;
	struct lista* prox;
};

typedef struct lista ListaHet;

ListaHet* cria_ret(float b, float h);
ListaHet* cria_tri(float b, float h);
ListaHet* cria_circ(float r);
float areaRet (Retangulo* ret);
float areaTri (Triangulo* tri);
float areaCir (Circulo* cir);
float area(ListaHet* p);
ListaHet* insere_ini (ListaHet* lst, ListaHet* item);
ListaHet* busca (ListaHet* lst, int tipo, float area);
ListaHet* remover (ListaHet* lst, int tipo, float area);
void imprime (ListaHet* lst);
void libera (ListaHet* lst);

int main(void)
{
	ListaHet* lst = NULL; //cria lista vazia
	ListaHet* ret1;
	ListaHet* tri1;
	ListaHet* cir1;
	ListaHet* ret2;

	ret1 = cria_ret(2, 4);
	lst = insere_ini(lst, ret1);
	tri1 = cria_tri(2, 4);
	lst = insere_ini(lst, tri1);
	cir1 = cria_circ(4);
	lst = insere_ini(lst, cir1);
	ret2 = cria_ret(5, 10);
	lst = insere_ini(lst, ret2);

	ListaHet* buscado;
	buscado = busca(lst, RET, 8);

	if(buscado != NULL){
		printf("Achou!\n");
	}else{
		printf("Não achou!\n");
	}

	imprime(lst);

	lst = remover(lst, RET, 6);

	imprime(lst);

	libera(lst);

	return 0;
}

ListaHet* cria_ret(float b, float h){

	Retangulo* ret = (Retangulo*)malloc(sizeof(Retangulo));
	ret->b = b;
	ret->h = h;

	ListaHet* lst = (ListaHet*)malloc(sizeof(ListaHet));
	lst->tipo = RET;
	lst->item = ret;
	lst->prox = NULL;

	return lst;
}

ListaHet* cria_tri(float b, float h){

	Triangulo* tri = (Triangulo*)malloc(sizeof(Triangulo));
	tri->b = b;
	tri->h = h;

	ListaHet* lst = (ListaHet*)malloc(sizeof(ListaHet));
	lst->tipo = TRI;
	lst->item = tri;
	lst->prox = NULL;

	return lst;
}

ListaHet* cria_circ(float r){

	Circulo* cir = (Circulo*)malloc(sizeof(Circulo));
	cir->r = r;

	ListaHet* lst = (ListaHet*)malloc(sizeof(ListaHet));
	lst->tipo = CIR;
	lst->item = cir;
	lst->prox = NULL;

	return lst;
}

float areaRet (Retangulo* ret){
	 return ret->b * ret->h;
}

float areaTri (Triangulo* tri){
	return (tri->b * tri->h)/2;
}

float areaCir (Circulo* cir){
	return (3.14 * (cir->r * cir->r));
}

float area(ListaHet* p){
	float resultado = 0;

	if(p->tipo == RET){
		resultado = areaRet((Retangulo*)p->item);
	}else if(p->tipo == TRI){
		resultado = areaTri((Triangulo*)p->item);
	}else if(p->tipo == CIR){
		resultado = areaCir((Circulo*)p->item); 
	}

	return resultado;
}

ListaHet* insere_ini (ListaHet* lst, ListaHet* item){

	ListaHet* novo = item;
	novo->prox = lst;

	return novo;
}


ListaHet* busca (ListaHet* lst, int tipo, float ar){

	ListaHet* p;
 
	for(p = lst; p != NULL; p = p->prox){
		if(p->tipo == tipo){
			if(area(p) == ar){
				return p;
			}
		}
	}

	return NULL;	
}

ListaHet* remover (ListaHet* lst, int tipo, float ar){

	ListaHet* ant = NULL;//ponteiro auxiliar pra marcar o anterior ao que se quer excluir
	ListaHet* p = lst;//ponteiro pra percorrer a lista

	//procura o elemento, guardando o anterior
	while(p != NULL && (p->tipo != tipo || area(p) != ar)){
		ant = p;
		p = p->prox;
	}

	//verifica se achou o elemento
	if(p == NULL){
		return lst; //percorreu todo o vetor e não achou: retorna lista original
	}

	//retira o elemento
	if(ant == NULL){ //retira elemento do início
		lst = p->prox; 
	}else { //retira elemento do meio da lista
		ant->prox = p->prox;
	}

	free(p->item);
	free(p);

	return lst;	
}

void imprime (ListaHet* lst){

	ListaHet* p;

	for(p = lst; p != NULL; p = p->prox){
		printf("Tipo %d, area: %f\n", p->tipo, area(p));
	}
	printf("\n");
}


void libera (ListaHet* lst){
	ListaHet* p = lst;

	while(p != NULL){
		ListaHet* t = p->prox; //guarda referência pro próximo elemento
		free(p->item);
		free(p); //libera a memória apontadas por p
		p = t; //faz p apontar pro próximo
	}

	printf("Lista liberada!\n");
}