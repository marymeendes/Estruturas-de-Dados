#include "huff.h"

int main(void){

	FILE* entrada;

	if((entrada = fopen("entrada.txt", "w+")) == NULL){
		printf("Erro na abertura do arquivo de entrada! D:\n");
		exit(1);
	}

	char c;
	char flag;

	printf("Entre com a string (pressione ctrl+d para finalizar a entrada):\n");

	flag = scanf("%c", &c);
	while(flag != EOF){
		fprintf(entrada, "%c", c);
		flag = scanf("%c", &c);
	}

	ListaChar* lst = criaListaChar();
	lst = montaListaChar(lst, entrada);

	imprimeListaChar(lst);	

	int tam = calculaTamListaChar(lst) + 1;
	ArvCod* heap[tam];

	preencheHeap(tam, heap, lst);

	ArvCod* sFolhas[tam-1];
	salvaFolhas(tam, heap, sFolhas);

	ArvCod* arvoreCodificacao = huffman(tam, heap);

	printf("\nValor raiz da árvore (soma das frequências): %d\n", arvoreCodificacao->info->frequencia); //deveria dar a soma de todas as frequencias

	TabCodificacao* tab = criaTabelaCodificacao();
	tab = montaTabCodificacao(tam-1, arvoreCodificacao, sFolhas);

	printf("\nTabela de codificação criada com sucesso!\n\n");
	imprimeTabCodificacao(tab, tam-1);

	/*char resposta;
	char caracter;
	int frequencia;
	char codigo[10];
	TabCodificacao* tab = criaTabelaCodificacao();*/

	//fclose(entrada);

	/*printf("Entre com os dados da tabela de codificação:\n");

	do{
		scanf("%c", &caracter);
		scanf("%d", &frequencia);
		scanf("%s", codigo);

		tab = insereTabCodificacao(tab, caracter, frequencia, codigo);

		printf("Continuar? (s/n) \n");
		getchar();
		scanf("%c", &resposta);
		getchar();
	}while(resposta == 's');*/

	//imprimeTabCodificacao(tab);

	/*if((entrada = fopen("entrada.txt", "r+")) == NULL){
		printf("Erro na abertura do arquivo de entrada! D:\n");
		exit(1);
	}*/

	fseek(entrada, 0, SEEK_SET);

	FILE* resultado;

	if((resultado = fopen("arquivoComprimido.txt", "w+")) == NULL){
		printf("Erro na abertura do arquivo de saída! D:\n");
		exit(1);
	}

	TabCodificacao* aux;
	char caracter;

	///////compactação///////

	while(0 < fread(&caracter, sizeof(char), 1, entrada)){
		aux = buscaTabCodificacao(tab, caracter);
		escreveCodigo(aux->linha.codigo, resultado);
	}

	long size = tamanhoArquivoCompacto(resultado); //tam tem o tamanho do arquivo em "bits"
	double size2 = size/8;

	printf("Compactação concluída com sucesso!\n");
	printf("Tamanho do arquivo em bits: %ld; Em bytes: %.2lf!\n", size, size2); 

	fclose(entrada);
	fclose(resultado);

	//liberaTabCodificacao(tab);
	liberaListaChar(lst);
	liberaHeap(tam, heap);
	arvoreCodificacao = liberaArv(arvoreCodificacao);
	
	return 0;
}
