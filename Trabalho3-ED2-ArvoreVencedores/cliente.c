#include "cliente.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime cliente
void imprime(Cliente *cliente) {
    printf("**********************************************");
    printf("\nCliente de código: ");
    printf("%d", cliente->codCliente);
    printf("\nNome: ");
    printf("%s", cliente->nome);
    printf("\nData de Nascimento: ");
    printf("%s", cliente->data_nascimento);
    printf("\n**********************************************");
}

// Cria cliente. Lembrar de usar free(cliente)
Cliente *criaCliente(int cod, char *nome, char *data_nascimento) {
    Cliente *cliente = (Cliente *) malloc(sizeof(Cliente));
    //inicializa espaço de memória com ZEROS
    if (cliente) memset(cliente, 0, sizeof(Cliente));
    //copia valores para os campos de cliente
    cliente->codCliente = cod;
    strcpy(cliente->nome, nome);
    strcpy(cliente->data_nascimento, data_nascimento);
    return cliente;
}

// Salva cliente no arquivo out, na posicao atual do cursor
void salva(Cliente *cliente, FILE *out) {
    fwrite(&cliente->codCliente, sizeof(int), 1, out);
    //cliente->nome ao invés de &cliente->nome, pois string já é ponteiro
    fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), out);
    fwrite(cliente->data_nascimento, sizeof(char), sizeof(cliente->data_nascimento), out);
}

// Le um cliente do arquivo in na posicao atual do cursor
// Retorna um ponteiro para cliente lido do arquivo
Cliente* le(FILE *in) {
    Cliente *cliente = (Cliente *) malloc(sizeof(Cliente));
    if (0 >= fread(&cliente->codCliente, sizeof(int), 1, in)) {
	   free(cliente);
	   return NULL;
    }
    fread(cliente->nome, sizeof(char), sizeof(cliente->nome), in);
    fread(cliente->data_nascimento, sizeof(char), sizeof(cliente->data_nascimento), in);
    return cliente;
}

// Retorna tamanho do cliente em bytes
int tamanho() {
    return sizeof(int)  //codCliente
            + sizeof(char) * 50 //nome
            + sizeof(char) * 11; //data_nascimento
}

