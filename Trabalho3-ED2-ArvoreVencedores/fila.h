#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista{
	char fileName[15];
	struct lista* prox;
};
typedef struct lista Lista;

struct fila{
	Lista* ini;
	Lista* fim;
};
typedef struct fila Fila;

/////// PROTÓTIPOS ///////

Fila* fila_cria();
void fila_insere(Fila* fila, char* name);
int fila_vazia(Fila* fila);
void fila_retira(Fila* fila, char* name);
void fila_libera(Fila* fila);

#endif
