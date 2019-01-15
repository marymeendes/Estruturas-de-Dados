#ifndef LISTA_H
#define LISTA_H

#include "cliente.h"

typedef struct registro
{
	Cliente* cliente;
	int prox;
	int status;	
}Registro;

Registro* reg_cria(Cliente* cli);
int tamanhoRegistro();

#endif