#ifndef SUBSTITUICAO_H
#define SUBSTITUICAO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct registro
{
	int valor;
	int congelado;
}Registro;

int substituicao (char* nome, int memorySize);

int freezer_auxiliary(Registro* v, int size);

#endif