#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

typedef struct Cliente {
    int codCliente;
    char nome[100];
}Cliente;

// Imprime cliente
void imprime(Cliente *cliente);

// Cria cliente. Lembrar de usar free(cliente)
Cliente *criaCliente(int cod, char *nome);

// Salva cliente no arquivo out, na posicao atual do cursor
void salva(Cliente *cliente, FILE *out);

// Le um cliente do arquivo in na posicao atual do cursor
// Retorna um ponteiro para cliente lido do arquivo
Cliente *le(FILE *in);

// Retorna tamanho do cliente em bytes
int tamanho();

void insere_clientes(FILE *out, int qtde);


#endif