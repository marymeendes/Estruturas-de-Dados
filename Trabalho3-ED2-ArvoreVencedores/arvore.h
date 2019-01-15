#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct chave
{
	int val;
	int fileId;
}Chave;

struct arv{
	Chave info;
	struct arv* esq;
	struct arv* dir;
};

typedef struct arv Arv;

////// PROTÓTIPOS ///////

Arv* arv_criavazia();
Arv* arv_cria(int c, int i, Arv* sae, Arv* sad);
int arv_vazia(Arv* a);
Arv* arv_libera(Arv* a);
int arv_pertence(Arv* a, int c);
void arv_imprime(Arv* a);
Arv* arv_compara(Arv* a1, Arv* a2);
Arv* arv_igualdadePaterna(Arv* a);
int arv_verificacao(Arv* a);

#endif