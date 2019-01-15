#include "huff.h"

TabCodificacao* criaTabelaCodificacao(){
	return NULL;
}

TabCodificacao* insereTabCodificacao(TabCodificacao* tab, char c, int f, char code[10]){
	TabCodificacao* novo = (TabCodificacao*)malloc(sizeof(TabCodificacao));
	novo->linha.caracter = c;
	novo->linha.frequencia = f;
	strcpy(novo->linha.codigo, code);
	novo->prox = tab;

	return novo;
}

void imprimeTabCodificacao(TabCodificacao* tab){
	TabCodificacao* p; //auxiliar para percorrer a lista
	for(p = tab; p != NULL; p = p->prox){
		printf("Caracter: %c - Frequência: %d - Código: %s\n", p->linha.caracter, p->linha.frequencia, p->linha.codigo);
	} 
}

void liberaTabCodificacao(TabCodificacao* tab){
	TabCodificacao* p = tab; //auxiliar para percorrer a lista
	while(p != NULL){
		TabCodificacao* t = p->prox; //auxiliar pra salvar o ponteiro para o próximo elemento
		free(p);
		p = t; //atualiza o p
	}
}

TabCodificacao* buscaTabCodificacao(TabCodificacao* tab, char c){ //varre a lista procurando pelo elemento com o valor desejado, se encontrar, o retorna, senão, retorna null
	TabCodificacao* p;
	printf("%c\n", c);
	for(p = tab; p!= NULL; p = p->prox){
		if(p->linha.caracter == c){
			return p;
		}
	}

	return NULL;
}

void escreveCodigo(char code[10], FILE* in){
	int i;

	for(i = 0; code[i] != '\0'; i++){
		fwrite(&code[i], sizeof(char), 1, in);
	}
}

long tamanhoArquivoCompacto(FILE* compacto){
	rewind(compacto);

	fseek(compacto, 0, SEEK_END);
	long tam = ftell(compacto);

	return tam;
}


ListaChar* criaListaChar(){
	return NULL;
}

ListaChar* insereListaChar(ListaChar* lst, char c, int f){
	ListaChar* novo = (ListaChar*)malloc(sizeof(ListaChar));
	novo->caracter = c;
	novo->frequencia = f;
	novo->prox = lst;

	return novo;
}

void imprimeListaChar(ListaChar* lst){
	ListaChar* p; //auxiliar para percorrer a lista
	for(p = lst; p != NULL; p = p->prox){
		printf("Caracter: %c - Frequência: %d\n", p->caracter, p->frequencia);
	} 
}

void liberaListaChar(ListaChar* lst){
	ListaChar* p = lst; //auxiliar para percorrer a lista
	while(p != NULL){
		ListaChar* t = p->prox; //auxiliar pra salvar o ponteiro para o próximo elemento
		free(p);
		p = t; //atualiza o p
	}
}

int listaCharVazia(ListaChar* lst){
	return lst == NULL;
}

ListaChar* buscaListaChar(ListaChar* lst, char c){ //varre a lista procurando pelo elemento com o valor desejado, se encontrar, o retorna, senão, retorna null
	ListaChar* p;
	for(p = lst; p!= NULL; p = p->prox){
		if(p->caracter == c){
			return p;
		}
	}

	return NULL;
}

ListaChar* montaListaChar(ListaChar* lst, FILE* string){

	char caracterDaVez, outroCaracter;
	int contadorDanado = 0, caracterNaoMapeado = 1, leu;
	ListaChar* aux;

	while(caracterNaoMapeado){ //enquanto houver caracter não mapeado no texto de entrada:
		rewind(string);
		if(listaCharVazia(lst)){ //se a lista está vazia, então o primeiro caracter do arquivo será lido e mapeado
			leu = fread(&caracterDaVez, sizeof(char), 1, string);
			contadorDanado +=1;
		}else{ //senão, procuraremos pelo primeiro caracter ainda não mapeado para mapeá-lo
			do{
				leu = fread(&caracterDaVez, sizeof(char), 1, string);
				if(0 >= leu){ //quando isso for verdade, todos os caracteres já terão sido mapeados e a flag de interrupção receberá 0 para parar o looṕ
					caracterNaoMapeado = 0;
					break;
				}
				aux = buscaListaChar(lst, caracterDaVez);//busco caracter na lista de mapeados, enquanto o encontrar continuo o loop ou até acabar o arquivo
			}while(aux != NULL);

			if(aux == NULL){ //verifico se saí do loop pq aux == NULL, ou seja, achei caracter não mapeado
				contadorDanado +=1;
			}
		}

		if(leu > 0){
			leu = fread(&outroCaracter, sizeof(char), 1, string); //leio outro caracter para comparar com o caracter da vez
		}
		while(leu > 0){ //enquanto há leitura
			if(caracterDaVez == outroCaracter){ //comparo os dois caracteres, se forem iguais: incremento o contador
				contadorDanado +=1;
			}
			leu = fread(&outroCaracter, sizeof(char), 1, string); //e leio o próximo caracter
		}

		if(contadorDanado > 0){ //se o contador tiver sido incrementado, oque significa que havia caracter e não mapeado e, portanto, faz sentido inserir novo elemento nas lista
			lst = insereListaChar(lst, caracterDaVez, contadorDanado); //insiro o novo elemento na lista de mapeados
		}

		contadorDanado = 0; //zero contador para recomeçar
	}

	return lst;
}

int calculaTamListaChar(ListaChar* lst){
	ListaChar* p;
	int qtde = 0;
	for(p = lst; p!= NULL; p = p->prox){
		qtde++;
	}

	return qtde;
}
 
void insereHeap(int tam, ItemHeap H[tam], ListaChar* p){
	int ult, i;

	for(i = 0; i < tam; i++){ //calculando últimpa posição preenchida antes da inserção
		if(H[i].frequencia == 0){
			ult = i - 1; // essa aqui!
			break;
		}
	}

	ult += 1;
	int k = ult;

	while((k/2) && (p->frequencia < H[k/2].frequencia)){
		H[k] = H[k/2];
		k = k/2;
	}

	H[k].caracter = p->caracter;
	H[k].frequencia = p->frequencia;
}

ItemHeap removeHeap(int tam, ItemHeap H[tam]){
	ItemHeap x, y;
	int ult, i;

	for(i = 0; i < tam; i++){ //calculando últimpa posição preenchida antes da inserção
		if(H[i].frequencia == 0){
			ult = i - 1; // essa aqui!
			break;
		}
	}

	y = H[1];
	x = H[ult];

	//apago a ultima posicao
	H[ult].caracter = '0';
	H[ult].frequencia = 0;

	ult = ult - 1;
	int k = 1;

	while((2*k <= ult) && (x.frequencia > H[2*k].frequencia || x.frequencia > H[2*k + 1].frequencia)){
		if(H[2*k].frequencia < H[2*k + 1].frequencia){
			H[k] = H[2*k];
			k = 2*k;
		}else{
			H[k] = H[2*k + 1];
			k = 2*k + 1;
		}

		H[k] = x;
	}

	return y;
}

void preencheHeap(int tam, ItemHeap heap[tam], ListaChar* lst){
	//int tam = calculaTamListaChar(lst);
	int i;

	//ItemHeap heap[tam];

	for(i = 0; i < tam; i++){ //inicializando heap com valores nulos
		heap[i].caracter = '0';
		heap[i].frequencia = 0;
	}

	ListaChar* p;
	for(p = lst; p!= NULL; p = p->prox){
		insereHeap(tam, heap, p);
	}

	/*printf("\nFila de prioridade:\n");

	for(i = 0; i < tam; i++){
		printf("Caracter: %c - Frequência: %d\n", heap[i].caracter, heap[i].frequencia);
	}*/
}