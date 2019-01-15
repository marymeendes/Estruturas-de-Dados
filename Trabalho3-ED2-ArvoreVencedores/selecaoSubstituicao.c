#include "selecaoSubstituicao.h"

int substituicao (char* nome, int memorySize){ //algoritmo de seleção por substituição que recebe um arquivo de inteiros e o tamanho da memória disponível
	printf("Particionando arquivo em células ordenadas...\n\n");

	Registro v[memorySize], menor;
	int i, aux, flag_eof = 1, inicio = 1, posicaoLeitura = 0;
	static int indice = 1;

	FILE* file;

	if((file = fopen(nome, "rb")) == NULL){
		printf("Erro ao abrir o arquivo!\n");
		exit(1);
	} 

	while(flag_eof){

		char nome_doc[40];
		sprintf(nome_doc, "particao%d.dat", indice);

		FILE* disco;
		if((disco = fopen(nome_doc, "wb")) == NULL){
			printf("Erro ao abrir particao!\n");
		}

		//passo 1 do algoritmo
		if(inicio){
			for(i=0; i<memorySize; i++){
				fread(&v[i].valor, sizeof(int), 1, file);
				v[i].congelado = 0;
				posicaoLeitura++;
				//printf("%d(%d) ", v[i].valor, v[i].congelado);
			}
			//getchar();
			inicio = 0;
		}
		
		while(freezer_auxiliary(v, memorySize)){
			
			//passo 2 do algoritmo
			for(i = 0; v[i].congelado == 1 && i < memorySize; i++){}

			menor = v[i]; //inicio setando o primeiro item descongelado como o menor

			for(i=0; i<memorySize; i++){
				//printf("%d(%d) ", v[i].valor, v[i].congelado);
				if(v[i].congelado == 0 && v[i].valor > -1){ //somente compara se o registro estiver descongelado
					if(v[i].valor < menor.valor){
						menor = v[i];
					}
				}
			}
			//printf("\n");


			//passo 3 do algoritmo
			fwrite(&menor.valor, sizeof(int), 1, disco);
			//printf("\nmenor da rodada%d --- %d\n", menor.valor, menor.congelado);
			//getchar();

			//passos 4 e 5 do algoritmo
			for(i=0; i<memorySize; i++){
				if(v[i].congelado == 0 && v[i].valor == menor.valor){
					//printf("%d --- %d\n", v[i].valor, v[i].congelado);
					//printf("%d --- %d\n", menor.valor, menor.congelado);
					fseek(file, posicaoLeitura*sizeof(int), SEEK_SET);
					if (fread(&aux, sizeof(int), 1, file) > 0){ //guardando próximo registro do arquivo numa variável auxiliar
						//printf("aux: %d\n", aux);
						v[i].valor = aux; //substituindo seu valor no vetor em memória
						//passo 5 a partir daqui
						if(aux < menor.valor){
							v[i].congelado = 1;
						}else{
							v[i].congelado = 0;
						}
						//printf("%d --- %d\n\n", v[i].valor, v[i].congelado);
						//getchar();
						posicaoLeitura++;

					}else{
						v[i].congelado = 1;
						v[i].valor = -1;
						flag_eof = 0;
						//printf("Flag:%d\n", flag_eof);
						//getchar();
					}

					break;
				}
			}

			/*for(i=0; i<memorySize; i++){
				printf("%d(%d) ", v[i].valor, v[i].congelado);
			}
			printf("\n");*/
		}
				
		//passo 7 do algoritmo

		fclose(disco); //parte 1 do passo 7: fechar a partição

		for(i=0; i<memorySize; i++){ //parte 2: descongelar os registros em memória
			v[i].congelado = 0;
		}

		indice++; //passos 3 e 4: abrir nova partição e voltar ao passo 2 
	}
	
	printf("Sucesso!\n%d particoes criadas!\nPara vê-las execute o programa leituraParticoes.c :3\n", indice-1);

	return indice-1;
}	

int freezer_auxiliary(Registro* v, int size){ //verifica se ainda existem registros descongelados na memória
	int i;
	
	for(i=0; i<size; i++){
		if(v[i].congelado == 0){
			return 1; //se tiver pelo menos 1 registro descongelado retorna 1
		}
	}

	return 0; //senão retorna 0
}