#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Registro* leReg(FILE* in);
void imprimeReg(Registro* reg);

int main(void){
	char nome[40];
	Registro* aux;

	printf("Insira o nome do arquivo a ser aberto:\n");
	scanf("%s", nome);

	FILE* file = fopen(nome, "rb");
	if(file == NULL){
		printf("Erro ao abrir o arquivo! D:\n");
	}else{
		while((aux = leReg(file)) != NULL){
			imprimeReg(aux);
			free(aux->cliente);
			free(aux);
		}
	}

	fclose(file);

	return 0;
}

Registro* leReg(FILE* in){
	Registro *reg = (Registro *) malloc(sizeof(Registro));
	reg->cliente = (Cliente*)malloc(sizeof(Cliente));

    if (0 >= fread(&reg->cliente->codCliente, sizeof(int), 1, in)) {
	   free(reg->cliente);
	   free(reg);
	   return NULL;
    }
    fread(reg->cliente->nome, sizeof(char), sizeof(reg->cliente->nome), in);
    fread(&reg->prox, sizeof(int), 1, in);
    fread(&reg->status, sizeof(int), 1, in);
    
    long auxiliarPosicao = ftell(in);
    printf("\nPosição do ponteiro de leitura/escrita ao terminar de ler o registro abaixo: %ld\n", auxiliarPosicao);
    return reg;
}

void imprimeReg(Registro* reg){
	printf("************************************************");
    printf("\nCliente de código: ");
    printf("%d", reg->cliente->codCliente);
    printf("\nNome: ");
    printf("%s", reg->cliente->nome);
    printf("\nEndereço do próximo: ");
    printf("%d", reg->prox);
    printf("\nStatus: ");
    printf("%d", reg->status);
    printf("\n**********************************************");
}