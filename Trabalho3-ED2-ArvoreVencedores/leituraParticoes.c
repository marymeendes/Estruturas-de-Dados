#include <stdio.h>
#include <stdlib.h>

int main(void){

	int i, qtde, chave;
	char nomeArq[15];

	printf("Informe a quantidade de particoes: ");
	scanf("%d", &qtde);

	for(i = 1; i <= qtde; i++){
		sprintf(nomeArq, "particao%d.dat", i);
		
		FILE* file = fopen(nomeArq, "rb");
		if(file == NULL){
			printf("Erro ao abrir o arquivo! D:\n");
		}else{
			printf("%s\n", nomeArq);
			while(fread(&chave, sizeof(int), 1, file) > 0){
				printf("%i\n", chave);
			}
		}

		fclose(file);
	}

	return 0;
}