#include "huff.h"

int main(void){

	////////Parte 1////////
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

	////////Parte 2: Montando os esqueminha////////

	ListaChar* lst = criaListaChar();
	lst = montaListaChar(lst, entrada);

	imprimeListaChar(lst);

	//montando árvore
	ArvCod* arvoreCodificacao = NULL;
	TabCodificacao* tab = criaTabelaCodificacao();
	
	int tam = calculaTamListaChar(lst);

	ArvCod* heap[tam+1];
	ArvCod* sFolhas[tam-1];

	if(tam == 1){
		arvoreCodificacao = criaNo(lst);
		printf("\nÁrvore de codificação montada!\n");	

		printf("\nValor raiz da árvore (soma das frequências): %d\n", arvoreCodificacao->info->frequencia); //deveria dar a soma de todas as frequencias

		tab = montaTabCodificacao1(tam, arvoreCodificacao);

		printf("\nTabela de codificação criada com sucesso!\n\n");
		imprimeTabCodificacao(tab, tam); 
	}else{
		tam += 1;
		
		preencheHeap(tam, heap, lst);

		salvaFolhas(tam, heap, sFolhas);

		arvoreCodificacao = huffman(tam, heap);

		printf("\nÁrvore de codificação montada!\n");	

		printf("\nValor raiz da árvore (soma das frequências): %d\n", arvoreCodificacao->info->frequencia); //deveria dar a soma de todas as frequencias

		tab = montaTabCodificacao(tam-1, arvoreCodificacao, sFolhas);

		printf("\nTabela de codificação criada com sucesso!\n\n");
		imprimeTabCodificacao(tab, tam-1);
	}

	/////////Parte 3///////////

	fseek(entrada, 0, SEEK_SET);

	FILE* resultado;

	if((resultado = fopen("arquivoComprimido.txt", "w+")) == NULL){
		printf("Erro na abertura do arquivo de saída! D:\n");
		exit(1);
	}

	TabCodificacao* aux;
	char caracter;

	///////Compactação///////

	while(0 < fread(&caracter, sizeof(char), 1, entrada)){
		aux = buscaTabCodificacao(tab, caracter);
		escreveCodigo(aux->linha.codigo, resultado);
	}

	int size = tamanhoArquivoCompacto(resultado); //tam tem o tamanho do arquivo em "bits"
	float size2 = (double)size/8;

	printf("\nCompactação concluída com sucesso!\n");
	printf("\nTamanho do arquivo em bits: %d; Em bytes: %.1f!\n", size, size2); 

	FILE* verificacao;

	if((verificacao = fopen("verificacao.txt", "w+")) == NULL){
		printf("Erro na abertura do arquivo de correção! D:\n");
		exit(1);
	}

	/*decodificacao(entrada, resultado, verificacao, tab);

	printf("\nDescompactação concluída com sucesso!\n");
	printf("\nResultados Finais:\n\n");

	printf("----------Entrada----------:\n");
	imprimeArquivo(entrada);
	printf("----------Compactação----------:\n");
	imprimeArquivo(resultado);
	printf("----------Descompactação----------:\n");
	imprimeArquivo(verificacao);*/

	//----------------------------
	rewind(resultado);

	char stringResultado[size+1];

	montaString(resultado, stringResultado);

	int ehIgual = stringEhIgual(stringResultado, size+1);

	decodificacao1(stringResultado, size+1, arvoreCodificacao, arvoreCodificacao, verificacao, ehIgual);

	// imprimeArquivo(verificacao);
	//----------------------------

	printf("\nDescompactação concluída com sucesso!\n");
	printf("\nResultados Finais:\n\n");

	printf("----------Entrada----------:\n");
	imprimeArquivo(entrada);
	printf("----------Compactação----------:\n");
	imprimeArquivo(resultado);
	printf("----------Descompactação----------:\n");
	imprimeArquivo(verificacao);

	fclose(entrada);
	fclose(resultado);
	fclose(verificacao);

	if(tam == 1){
		liberaTabCodificacao(tab, tam);
		arvoreCodificacao = liberaArv(arvoreCodificacao);
	}else{
		liberaTabCodificacao(tab, tam-1);
		liberaHeap(tam, heap);
		arvoreCodificacao = liberaArv(arvoreCodificacao);
	}

	liberaListaChar(lst);

	return 0;
}
