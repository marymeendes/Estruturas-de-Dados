#include "lefkowitz.h"

//Passo 1: 

//Passo 1.1: arquivo original ordenado pela chave primária

int verificaQtdeRegistros(FILE* in, int tamanhoRegistro){ //calculando quantos elementos existem no arquivo
	int tamanhoArq, qtdeRegistros;
	fseek(in, 0, SEEK_END);
	tamanhoArq = (int)ftell(in);
	qtdeRegistros = tamanhoArq/tamanhoRegistro; //recupero aqui a quantidade de registros que há no arquivo

	return qtdeRegistros;
}


void ordenaCP(FILE* dados){ //função pega o arquivo original, ordena seus registros e cria o arquivo A1 com os registros ordenados
	rewind(dados);
	int i;
	FILE* a1;

	int qtdeRegistros = verificaQtdeRegistros(dados, tamanho()); //calculo a qtde de elementos no arquivo

	//e posso então criar um vetor com esse tamanho para ordenação
	Cliente* clientes[qtdeRegistros];

	//preenchendo o vetor
	rewind(dados);

	for(i = 0; i < qtdeRegistros; i++){
		clientes[i] = le(dados);
	}

	//função de ordenação quick sort (nativa do c) é chamada para a ordenação
	qsort(clientes, qtdeRegistros, sizeof(Cliente*), comparaClientesCP);

	//criando arquivo A1
	if((a1 = fopen("A1.dat", "wb")) == NULL){
		printf("Erro na abertura de A1 D:\n");
		exit(1);
	}

	//escrevendo os registro ordenados em A1
	for(i = 0; i < qtdeRegistros; i++){
		salva(clientes[i], a1);	
	}

	fclose(a1);
	for(i = 0; i < qtdeRegistros; i++){
		free(clientes[i]);	
	}

	printf("\nPasso 1.1 completo!\n");
}

//Passo 1.2: criar o arquivo A2 com elementos do tipo EstruturaA2

void criaA2(FILE* a1){
	rewind(a1);

	EstruturaA2* aux = (EstruturaA2*)malloc(sizeof(EstruturaA2));
	Cliente* c;
	int endereco, i;
	FILE* a2;

	if((a2 = fopen("A2.dat", "wb")) == NULL){
		printf("Erro na abertura de A2 D:\n");
		exit(1);
	}

	//leio os registros de A1, preencho a estrutura de A2 e insiro seus atributos em A2 para cada registro contido em A1
	for(i = 0; (c = le(a1)) != NULL; i++){
		endereco = i*tamanho();
		aux->enderecoDisco = endereco;
		aux->chavePrim = c->codCliente;
		aux->chaveSec = c->idade;

		fwrite(&aux->enderecoDisco, sizeof(int), 1, a2);
		fwrite(&aux->chavePrim, sizeof(int), 1, a2);
		fwrite(&aux->chaveSec, sizeof(int), 1, a2);
	}

	fclose(a2);
	free(aux);
	free(c);

	printf("\nPasso 1.2 completo!\n");
}

//Passo 2: decompor arquivo A2 e arquivos A3, um para cada atributo a ser indexado, no nosso caso apenas 1: idade (fator esse que faz A2 e A3 serem iguais :3)
//Estrutura usada: EstruturaA3

EstruturaA2* leA2(FILE *a2) {
    EstruturaA2 *aux = (EstruturaA2 *) malloc(sizeof(EstruturaA2));
    if (0 >= fread(&aux->enderecoDisco, sizeof(int), 1, a2)) {
	   free(aux);
	   return NULL;
    }
    fread(&aux->chavePrim, sizeof(int), 1, a2);
    fread(&aux->chaveSec, sizeof(int), 1, a2);
    return aux;
}

void criaA3(FILE* a2){
	rewind(a2);

	EstruturaA2* aux1;
	EstruturaA3* aux2 = (EstruturaA3*)malloc(sizeof(EstruturaA3));
	int i;
	FILE* a3;

	if((a3 = fopen("A3.dat", "wb")) == NULL){
		printf("Erro na abertura de A3 D:\n");
		exit(1);
	}

	//leio os registros de A2, preencho a estrutura de A3 e insiro seus atributos em A3 para cada registro contido em A2
	for(i = 0; (aux1 = leA2(a2)) != NULL; i++){
		aux2->enderecoDisco = aux1->enderecoDisco;
		aux2->chavePrim = aux1->chavePrim; //codCliente
		aux2->chaveSec_i = aux1->chaveSec; //idade

		fwrite(&aux2->enderecoDisco, sizeof(int), 1, a3);
		fwrite(&aux2->chavePrim, sizeof(int), 1, a3);
		fwrite(&aux2->chaveSec_i, sizeof(int), 1, a3);
	}

	fclose(a3);
	free(aux1);
	free(aux2);

	printf("Passo 2 completo!\n");
}

//Passo 3: Ordenar os Arquivos A3 por chave secundária: no nosso caso, idade

int tamanhoA3(){
	return sizeof(int) //enderecoDisco
			+ sizeof(int) //chavePrim
			+ sizeof(int); //chaveSec_i
}

EstruturaA3* leA3(FILE *a3) {
    EstruturaA3 *aux = (EstruturaA3 *) malloc(sizeof(EstruturaA3));
    if (0 >= fread(&aux->enderecoDisco, sizeof(int), 1, a3)) {
	   free(aux);
	   return NULL;
    }
    fread(&aux->chavePrim, sizeof(int), 1, a3);
    fread(&aux->chaveSec_i, sizeof(int), 1, a3);
    return aux;
}

void salvaA3(EstruturaA3* reg, FILE* out){
	fwrite(&reg->enderecoDisco, sizeof(int), 1, out);
    fwrite(&reg->chavePrim, sizeof(int), 1, out);
    fwrite(&reg->chaveSec_i, sizeof(int), 1, out);
}

void ordenaPorIdade(FILE* a3){ //função ordena pela chave secundária idade e cria o arquivo A4 com os registros ordenados
	rewind(a3);

	int i;
	FILE* a4;

	int qtdeRegistrosA3 = verificaQtdeRegistros(a3, tamanhoA3()); //calculo q qtde de registros em A3, que deve se igual a de A1

	//e posso então criar um vetor com esse tamanho para ordenação
	EstruturaA3* registros[qtdeRegistrosA3];

	//preenchendo o vetor
	rewind(a3);

	for(i = 0; i < qtdeRegistrosA3; i++){
		registros[i] = leA3(a3);
	}

	//função de ordenação quick sort (nativa do c) é chamada para a ordenação
	qsort(registros, qtdeRegistrosA3, sizeof(EstruturaA3*), comparaEstruturaA3);

	//criando arquivo A4
	if((a4 = fopen("A4.dat", "wb")) == NULL){
		printf("Erro na abertura de A4 D:\n");
		exit(1);
	}

	//escrevendo os registro ordenados em A4
	for(i = 0; i < qtdeRegistrosA3; i++){
		salvaA3(registros[i], a4);	
	}

	fclose(a4);
	for(i = 0; i < qtdeRegistrosA3; i++){
		free(registros[i]);	
	}

	printf("Passo 3 completo!\n");

}

//Passo 4: criar arquivos A5 e A6

void criaA5(FILE* a4){ //Passo 4.1:
	rewind(a4);

	FILE* a5;

	int i = 0, idade = 0, continua = 1, endereco;
	EstruturaA3* auxA3;
	EstruturaA5* auxA5 = (EstruturaA5 *) malloc(sizeof(EstruturaA5));

	if((a5 = fopen("A5.dat", "wb")) == NULL){
		printf("Erro na abertura de A5 D:\n");
		exit(1);
	}

	auxA3 = leA3(a4);

	while(continua){
		
		idade = auxA3->chaveSec_i;
		endereco = auxA3->enderecoDisco;
		i=0;

		while(auxA3->chaveSec_i == idade){
			i+=1;
			auxA3 = leA3(a4);
			if(auxA3 == NULL){
				continua = 0;
				break;
			}
		}

		auxA5->chaveSec_i = idade;
		auxA5->ponteiro = endereco;
		auxA5->quantidade = i;

		fwrite(&auxA5->chaveSec_i, sizeof(int), 1, a5);
	    fwrite(&auxA5->ponteiro, sizeof(int), 1, a5);
	    fwrite(&auxA5->quantidade, sizeof(int), 1, a5);
	}

	fclose(a5);
	free(auxA3);
	free(auxA5);

	printf("Passo 4.1 completo!\n");
}

EstruturaA5* leA5(FILE *a5) {
    EstruturaA5 *aux = (EstruturaA5 *) malloc(sizeof(EstruturaA5));
    if (0 >= fread(&aux->chaveSec_i, sizeof(int), 1, a5)) {
	   free(aux);
	   return NULL;
    }
    fread(&aux->ponteiro, sizeof(int), 1, a5);
    fread(&aux->quantidade, sizeof(int), 1, a5);
    return aux;
}

void criaA6(FILE* a4, FILE* a5){ //Passo 4.2:
	rewind(a4); rewind(a5);

	FILE* a6;

	int i = 0, continua = 1;

	EstruturaA3* auxA3;
	EstruturaA5* auxA5;
	EstruturaA6* auxA6 = (EstruturaA6*)malloc(sizeof(EstruturaA6));

	if((a6 = fopen("A6.dat", "wb")) == NULL){
		printf("Erro na abertura de A6 D:\n");
		exit(1);
	}

	while(continua){

		printf("hola\n");

		auxA3 = leA3(a4);

		if(auxA3 != NULL){
			printf("Hi!\n");
			auxA6->enderecoDisco = auxA3->enderecoDisco;
			auxA6->chavePrim = auxA3->chavePrim;
			auxA6->chaveSec_i = auxA3->chaveSec_i;

			auxA5 = leA5(a5);

			if(auxA5->quantidade == 1){
				printf("oiee\n");
				auxA6->proximo = -1;
				fwrite(&auxA6->enderecoDisco, sizeof(int), 1, a6);
				fwrite(&auxA6->chavePrim, sizeof(int), 1, a6);
				fwrite(&auxA6->chaveSec_i, sizeof(int), 1, a6);
				fwrite(&auxA6->proximo, sizeof(int), 1, a6);
			}else{
				i=1;
				while(i <= auxA5->quantidade){
					if(i == auxA5->quantidade){
						auxA6->proximo = -1;
						printf("olá\n");
						fwrite(&auxA6->enderecoDisco, sizeof(int), 1, a6);
					    fwrite(&auxA6->chavePrim, sizeof(int), 1, a6);
					    fwrite(&auxA6->chaveSec_i, sizeof(int), 1, a6);
					    fwrite(&auxA6->proximo, sizeof(int), 1, a6);
						break;
					}else{
						auxA3 = leA3(a4);
						i+=1;
						auxA6->proximo = auxA3->enderecoDisco;	
					}

					printf("(cof cof)\n");

					fwrite(&auxA6->enderecoDisco, sizeof(int), 1, a6);
				    fwrite(&auxA6->chavePrim, sizeof(int), 1, a6);
				    fwrite(&auxA6->chaveSec_i, sizeof(int), 1, a6);
				    fwrite(&auxA6->proximo, sizeof(int), 1, a6);

				    auxA6->enderecoDisco = auxA3->enderecoDisco;
					auxA6->chavePrim = auxA3->chavePrim;
					auxA6->chaveSec_i = auxA3->chaveSec_i;
				}
			}
		}else{
			continua = 0;
		}
	}

	fclose(a6);
	free(auxA3);
	free(auxA5);
	free(auxA6);

	printf("Passo 4.2 completo!\n");
}

//Passo 5: ordenar os registros de A6 por chave primária e criar um arquivo A7 com os registros ordenados

int tamanhoA6(){
	return sizeof(int) //enderecoDisco
			+ sizeof(int) //chavePrim
			+ sizeof(int) //chaveSec_i
			+ sizeof(int); //proximo
}

EstruturaA6* leA6(FILE *a6) {
    EstruturaA6 *aux = (EstruturaA6 *) malloc(sizeof(EstruturaA6));
    if (0 >= fread(&aux->enderecoDisco, sizeof(int), 1, a6)) {
	   free(aux);
	   return NULL;
    }
    fread(&aux->chavePrim, sizeof(int), 1, a6);
    fread(&aux->chaveSec_i, sizeof(int), 1, a6);
    fread(&aux->proximo, sizeof(int), 1, a6);
    return aux;
}

void salvaA6(EstruturaA6* reg, FILE* out){
	fwrite(&reg->enderecoDisco, sizeof(int), 1, out);
    fwrite(&reg->chavePrim, sizeof(int), 1, out);
    fwrite(&reg->chaveSec_i, sizeof(int), 1, out);
    fwrite(&reg->proximo, sizeof(int), 1, out);
}

void criaA7(FILE* a6){//ordena os registro de A6 e cria A7
	rewind(a6);

	int i;
	FILE* a7;

	int qtdeRegistrosA6 = verificaQtdeRegistros(a6, tamanhoA6()); //calculo q qtde de registros em A6, que deve se igual a de A1

	//e posso então criar um vetor com esse tamanho para ordenação
	EstruturaA6* registros[qtdeRegistrosA6];

	//preenchendo o vetor
	rewind(a6);

	for(i = 0; i < qtdeRegistrosA6; i++){
		registros[i] = leA6(a6);
	}

	//função de ordenação quick sort (nativa do c) é chamada para a ordenação
	qsort(registros, qtdeRegistrosA6, sizeof(EstruturaA6*), comparaEstruturaA6);

	//criando arquivo A4
	if((a7 = fopen("A7.dat", "wb")) == NULL){
		printf("Erro na abertura de A7 D:\n");
		exit(1);
	}

	//escrevendo os registro ordenados em A4
	for(i = 0; i < qtdeRegistrosA6; i++){
		salvaA6(registros[i], a7);	
	}

	fclose(a7);
	for(i = 0; i < qtdeRegistrosA6; i++){
		free(registros[i]);	
	}

	printf("Passo 5 completo!\n");
}

//Passo 6: unir A1 e A7 para formar A8, A5 é o indice

void criaA8(FILE* a1, FILE* a7){
	rewind(a1); rewind(a7);

	EstruturaA8* auxA8 = (EstruturaA8 *) malloc(sizeof(EstruturaA8));
	Cliente* c;
	EstruturaA6* auxA6;
	FILE* a8;

	if((a8 = fopen("A8.dat", "wb")) == NULL){
		printf("Erro na abertura de A8 D:\n");
		exit(1);
	}

	while((c = le(a1)) != NULL){
		auxA6 = leA6(a7);

		auxA8->codCliente = c->codCliente;
		strcpy(auxA8->nome, c->nome);
		auxA8->idade = c->idade;
		auxA8->prox = auxA6->proximo;

		fwrite(&auxA8->codCliente, sizeof(int), 1, a8);
	    fwrite(auxA8->nome, sizeof(char), sizeof(auxA8->nome), a8);
	    fwrite(&auxA8->idade, sizeof(int), 1, a8);
	    fwrite(&auxA8->prox, sizeof(int), 1, a8);
	}

	fclose(a8);
	free(auxA8);
	free(c);
	free(auxA6);

	printf("Passo 6 completo!\n");
}

EstruturaA8* leA8(FILE *a8) {
    EstruturaA8 *aux = (EstruturaA8 *) malloc(sizeof(EstruturaA8));
    if (0 >= fread(&aux->codCliente, sizeof(int), 1, a8)) {
	   free(aux);
	   return NULL;
    }
    fread(aux->nome, sizeof(char), sizeof(aux->nome), a8);
    fread(&aux->idade, sizeof(int), 1, a8);
    fread(&aux->prox, sizeof(int), 1, a8);
    return aux;
}

//FIM! AMÉM? AMÉM!
