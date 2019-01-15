#ifndef LEFKOWITZ_H
#define LEFKOWITZ_H

#include "cliente.h"
#include "qsort.h"

typedef struct estruturaA2
{
	int enderecoDisco;
	int chavePrim; //codCliente
	int chaveSec; //idade (atributo que será indexado)
}EstruturaA2;

typedef struct estruturaA3
{
	int enderecoDisco;
	int chavePrim; //codCliente
	int chaveSec_i; //idade (atributo que será indexado)
}EstruturaA3;

typedef struct estruturaA5
{
	int chaveSec_i; //idade
	int ponteiro; //enderecoDisco do primeiro registro com determinado valor para a chaveSec_i
	int quantidade; //qtde de elementos com um mesmo valor para a chaveSec_i
}EstruturaA5;

typedef struct estruturaA6
{
	int enderecoDisco;
	int chavePrim; //codCliente
	int chaveSec_i; //idade (atributo que será indexado)
	int proximo; //acrescento, em relação a A3, o ponteiro pro próximo
}EstruturaA6;

typedef struct estruturaA8 
{
    int codCliente;
    char nome[50];
    int idade;
    int prox;
}EstruturaA8;

int verificaQtdeRegistros(FILE* in, int tamanhoRegistro);

void ordenaCP(FILE* dados);

void criaA2(FILE* a1);

EstruturaA2* leA2(FILE *a2);

void criaA3(FILE* a2);

int tamanhoA3();

EstruturaA3* leA3(FILE *a3);

void salvaA3(EstruturaA3* reg, FILE* out);

void ordenaPorIdade(FILE* a3);

void criaA5(FILE* a4);

EstruturaA5* leA5(FILE *a5);

void criaA6(FILE* a4, FILE* a5);

int tamanhoA6();

EstruturaA6* leA6(FILE *a6);

void salvaA6(EstruturaA6* reg, FILE* out);

void criaA7(FILE* a6);

void criaA8(FILE* a1, FILE* a7);

EstruturaA8* leA8(FILE *a8); 

#endif