#include "cliente.h"

int main(void){

	char nome[40];
	Cliente* aux;

	printf("Insira o nome do arquivo a ser aberto:\n");
	scanf("%s", nome);

	FILE* file = fopen(nome, "rb");
	if(file == NULL){
		printf("Erro ao abrir o arquivo! D:\n");
	}else{
		while(aux != NULL){
			aux = le(file);
			imprime(aux);
			free(aux);
		}
	}

	fclose(file);

	return 0;
}