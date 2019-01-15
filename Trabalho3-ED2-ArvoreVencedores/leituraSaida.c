#include <stdio.h>
#include <stdlib.h>

int main(void){
	
	char nome[20];

	printf("Digite o nome do arquivo de inteiros a ser lido:\n");
	scanf("%s", nome);

	FILE* file = fopen(nome, "rb");
	if(file == NULL){
		printf("Erro ao abrir o arquivo! D:\n");
	}else{
		int chave;
		while(fread(&chave, sizeof(int), 1, file) > 0){
			printf("%i\n", chave);
		}
	}

	fclose(file);

	return 0;
}