#ifndef HUFF_H
#define HUFF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct itemTabCod
{	
	char caracter;
	int frequencia;
	char codigo[10];
}ItemTabCod;

typedef struct tabCodificacao TabCodificacao;

struct tabCodificacao
{
	ItemTabCod linha;
	TabCodificacao* prox;
};

typedef struct listaChar ListaChar;

struct listaChar
{
	char caracter;
	int frequencia;
	ListaChar* prox;
};

typedef struct itemHeap
{
	char caracter;
	int frequencia;
}ItemHeap;

typedef struct arvCod ArvCod;

struct arvCod
{
	ItemHeap* info;
	ArvCod* pai;
	ArvCod* esq; //0
	ArvCod* dir; //1
};

TabCodificacao* criaTabelaCodificacao();
TabCodificacao* insereTabCodificacao(TabCodificacao* tab, char c, int f, char code[10]);
void imprimeTabCodificacao(TabCodificacao* tab, int tam);
void liberaTabCodificacao(TabCodificacao* tab, int tam);
TabCodificacao* buscaTabCodificacao(TabCodificacao* tab, char c);
void escreveCodigo(char code[10], FILE* in);
long tamanhoArquivoCompacto(FILE* compacto);

ListaChar* criaListaChar();
ListaChar* insereListaChar(ListaChar* lst, char c, int f);
void imprimeListaChar(ListaChar* lst);
void liberaListaChar(ListaChar* lst);
int listaCharVazia(ListaChar* lst);
ListaChar* buscaListaChar(ListaChar* lst, char c);
ListaChar* montaListaChar(ListaChar* lst, FILE* string);
int calculaTamListaChar(ListaChar* lst);
void insereHeap(int tam, ArvCod* H[tam], ArvCod* p);
ArvCod* removeHeap(int tam, ArvCod* H[tam]);
ArvCod* criaNo(ListaChar* p);
void preencheHeap(int tam, ArvCod* heap[tam], ListaChar* lst);
void salvaFolhas(int tam, ArvCod* heap[tam], ArvCod* vFolhas[tam-1]);

ArvCod* fusao(ArvCod* t1, ArvCod* t2);
ArvCod* minimo(int tam, ArvCod* heap[tam]);
ArvCod* huffman(int tam, ArvCod* heap[tam]);

void inverteCod(char* cod);
TabCodificacao* montaTabCodificacao(int tam, ArvCod* a, ArvCod* vFolhas[tam]);
TabCodificacao* montaTabCodificacao1(int tam, ArvCod* a);

void liberaHeap(int tam, ArvCod* heap[tam]);
void liberaFolhas(int tam, ArvCod* vFolhas[tam]);
int arv_vazia(ArvCod* t);
ArvCod* liberaArv(ArvCod* t);

void decodificacao(FILE* entrada, FILE* compacto, FILE* descompacto, TabCodificacao* tab);
void montaString(FILE* compacto, char* s);
int stringEhIgual(char* s, int tam);
void decodificacao1(char* s, int size, ArvCod* a, ArvCod* raiz, FILE* descompacto, int ehIgual);
void imprimeArquivo(FILE* arquivo);

#endif
