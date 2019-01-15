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

void imprimeTabCodificacao(TabCodificacao* tab, int tam){
	TabCodificacao* p; //auxiliar para percorrer a lista
	int qtde = 0;
	for(p = tab; p != NULL && qtde < tam; p = p->prox){
		qtde++;
		printf("Caracter: %c - Frequência: %d - Código: %s\n", p->linha.caracter, p->linha.frequencia, p->linha.codigo);
	} 
}

void liberaTabCodificacao(TabCodificacao* tab, int tam){
	TabCodificacao* p = tab; //auxiliar para percorrer a lista
	int qtde = 0;
	while(p != NULL && qtde < tam){
		TabCodificacao* t = p->prox; //auxiliar pra salvar o ponteiro para o próximo elemento
		free(p);
		p = t; //atualiza o p
		qtde++;
	}
}

TabCodificacao* buscaTabCodificacao(TabCodificacao* tab, char c){ //varre a lista procurando pelo elemento com o valor desejado, se encontrar, o retorna, senão, retorna null
	TabCodificacao* p;
	//printf("%c\n", c);
	for(p = tab; p!= NULL; p = p->prox){
		if(p->linha.caracter == c){
			return p;
		}
	}

	return NULL;
}

/////////////////////////////////////////////////

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
		printf("\nCaracter: %c - Frequência: %d\n", p->caracter, p->frequencia);
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
 
void insereHeap(int tam, ArvCod* H[tam], ArvCod* p){
	int ult, i;

	for(i = 1; i < tam; i++){ //calculando últimpa posição preenchida antes da inserção
		if(H[i] == NULL){
			ult = i - 1; // essa aqui!
			break;
		}
	}

	ult = ult + 1;
	int k = ult;

	while((k/2) && (p->info->frequencia < H[k/2]->info->frequencia)){
		H[k] = H[k/2];
		k = k/2;
	}

	H[k] = p;
}

ArvCod* removeHeap(int tam, ArvCod* H[tam]){
	ArvCod *x, *y;
	int ult, i;

	for(i = 1; i < tam; i++){ //calculando últimpa posição preenchida antes da remoção
		if(H[i] == NULL){
			ult = i - 1; // essa aqui!
			break;
		}else if(i + 1 == tam){ //cheguei no último e ele não tava vazio
			ult = i;
		}
	}

	y = H[1];
	x = H[ult];

	//apago a ultima posicao
	H[ult] = NULL;

	ult = ult - 1;
	int k = 1;

	while((2*k <= ult) && (((H[2*k] != NULL) && (x->info->frequencia >= H[2*k]->info->frequencia)) || ((H[2*k + 1] != NULL) && (x->info->frequencia >= H[2*k + 1]->info->frequencia)))){
		if(H[2*k] != NULL && H[2*k + 1] != NULL){
			if(H[2*k]->info->frequencia < H[2*k + 1]->info->frequencia){
				H[k] = H[2*k];
				k = 2*k;
			}else{
				H[k] = H[2*k + 1];
				k = 2*k+1;
			}
		}else if(H[2*k] != NULL){
			H[k] = H[2*k];
			k = 2*k;
		}else if(H[2*k + 1] != NULL){
			H[k] = H[2*k + 1];
			k = 2*k+1;
		}	
	}

	if(ult != 0){ //pq se for igual não há necessidade de recolocar o elemento na fila, ela esvaziou!
		H[k] = x;
	}

	return y;
}

ArvCod* criaNo(ListaChar* p){
	ItemHeap* c = (ItemHeap*)malloc(sizeof(ItemHeap));
	c->caracter = p->caracter;
	c->frequencia = p->frequencia;

	ArvCod* arv = (ArvCod*)malloc(sizeof(ArvCod));
	arv->info = c;
	arv->pai = NULL;
	arv->esq = NULL;
	arv->dir = NULL;

	return arv;
}

void preencheHeap(int tam, ArvCod* heap[tam], ListaChar* lst){
	//int tam = calculaTamListaChar(lst);
	int i;

	//ArvCod* heap[tam];

	for(i = 0; i < tam; i++){
		heap[i] = NULL;
	}

	ListaChar* p;
	for(p = lst; p != NULL; p = p->prox){
		insereHeap(tam, heap, criaNo(p));
	}

	/*printf("\nFila de prioridade:\n");

	for(i = 1; i < tam; i++){
		printf("Caracter: %c - Frequência: %d\n", heap[i]->info->caracter, heap[i]->info->frequencia);
	}*/
}

void salvaFolhas(int tam, ArvCod* heap[tam], ArvCod* vFolhas[tam-1]){ //tam-1 é a qtde real de elementos do alfabeto S
	int i;

	for(i = 0; i < tam-1; i++){
		vFolhas[i] = heap[i+1];
		/*if(vFolhas[i] == heap[i+1]){
			printf("hi!"); //DEU CERTO!!
		}*/
	}
}

//////////////////////////////////////////////

ArvCod* fusao(ArvCod* t1, ArvCod* t2){
	ArvCod* t3 = (ArvCod*)malloc(sizeof(ArvCod));
	t3->info = (ItemHeap*)malloc(sizeof(ItemHeap));
	t3->info->caracter = '0'; //preenchido com qualquer coisa só para simbolizar
	t3->info->frequencia = t1->info->frequencia + t2->info->frequencia; //preenchido com a soma das frequencias das subárvores
	t3->pai = NULL;
	t3->esq = t1;
	t3->dir = t2;

	t1->pai = t3;
	t2->pai = t3;

	return t3;
}

ArvCod* huffman(int tam, ArvCod* heap[tam]){
	int i;
	ArvCod *t1, *t2, *t3;

	for(i = 1; i < tam - 1; i++){
		t1 = removeHeap(tam, heap);
		t2 = removeHeap(tam, heap);
		t3 = fusao(t1, t2);
		insereHeap(tam, heap, t3);
	}

	return t3;
}

void inverteCod(char* cod){
	int i, tam = strlen(cod);
	char temp;

	for(i=0; i < tam/2; i++){
		temp = cod[i];
		cod[i] = cod[tam-1-i];
		cod[tam-1-i] = temp;
	}
}	

TabCodificacao* montaTabCodificacao(int tam, ArvCod* a, ArvCod* vFolhas[tam]){ //lembrar de inserir tam-1 no lugar de tam-1
	int i, j;														//paramêtros: tam = tamanho do alfabeto S, a: árvore de codificação, vFolhas: vetor de folhas
	ArvCod *arvDaVez, *arvPai;
	TabCodificacao* tab;

	for(i = 0; i < tam; i++){
		arvDaVez = vFolhas[i];
		arvPai = arvDaVez->pai;
		char codigo[10];

		for(j = 0; arvPai != NULL; j++){
			if(arvDaVez == arvPai->esq){
				codigo[j] = '0';
			}else if(arvDaVez == arvPai->dir){
				codigo[j] = '1';
			}
			arvDaVez = arvPai;
			arvPai = arvPai->pai;
		}
		codigo[j] = '\0';
		inverteCod(codigo);
		tab = insereTabCodificacao(tab, vFolhas[i]->info->caracter, vFolhas[i]->info->frequencia, codigo);
	}

	return tab;
}

TabCodificacao* montaTabCodificacao1(int tam, ArvCod* a){
	TabCodificacao* tab = NULL;
	tab = insereTabCodificacao(tab, a->info->caracter, a->info->frequencia, "1");

	return tab;
}

void decodificacao(FILE* entrada, FILE* compacto, FILE* descompacto, TabCodificacao* tab){
	rewind(entrada); rewind(compacto); rewind(descompacto);
	char c, auxC[10];
	TabCodificacao* aux;
	int tamCod = 0, i;

	while(fread(&c, sizeof(char), 1, entrada)){
		aux = buscaTabCodificacao(tab, c);
		tamCod = strlen(aux->linha.codigo);
		if(fread(&auxC, sizeof(char), tamCod, compacto)){
			if(strcmp(aux->linha.codigo, auxC) == 0){
				fwrite(&aux->linha.caracter, sizeof(char), 1, descompacto);
			}else{
				printf("Erro de compactação!1 D:\n");
				break;
			}
		}else{
			printf("Erro de compactação!2 D:\n");
		}
		for(i = 0; i < 10; i++){
			auxC[i] = '\0';
		}
	}
}

void montaString(FILE* compacto, char* s){
	rewind(compacto);
	char c;
	int i = 0;

	while(fread(&c, sizeof(char), 1, compacto)){
		s[i] = c;
		i++;
	}
	s[i] = '\0';

	printf("%s\n", s);
}

int stringEhIgual(char* s, int tam){
	int i;

	for(i = 0; i < tam-2; i++){
		if(s[i] != s[i+1]){
			return 0;
		}
	}

	return 1;
}

void decodificacao1(char* s, int size, ArvCod* a, ArvCod* raiz, FILE* descompacto, int ehIgual){
	if(!ehIgual){
		static int i = -1;

		if(a->esq == NULL && a->dir == NULL){
			fprintf(descompacto, "%c", a->info->caracter);
			if(i < size-1){
				//i += 1;
				decodificacao1(s, size, raiz, raiz, descompacto, ehIgual);
			}
		}else{
			i += 1;
			if(s[i] == '0'){
				decodificacao1(s, size, a->esq, raiz, descompacto, ehIgual);
			}else if(s[i] == '1'){
				decodificacao1(s, size, a->dir, raiz, descompacto, ehIgual);
			}
		}
	}else{
		static int j = 1;

		if(a->esq == NULL && a->dir == NULL){
			fprintf(descompacto, "%c", a->info->caracter);
			if(j < size-1){
				j += 1;
				decodificacao1(s, size, raiz, raiz, descompacto, ehIgual);
			}
		}
	}
	
}

void imprimeArquivo(FILE* arquivo){
	rewind(arquivo);
	char c;
	while(fread(&c, sizeof(char), 1, arquivo)){
		printf("%c", c);
	}
	printf("\n\n");
}

void liberaHeap(int tam, ArvCod* heap[tam]){
	int i;

	for(i = 0; i < tam; i++){
		free(heap[i]);
	}
}

/*void liberaFolhas(int tam, ArvCod* vFolhas[tam]){ //desnecessário, representaria dar free no que já foi liberado :S
	int i;

	for(i = 0; i < tam; i++){
		free(vFolhas[i]);
	}
}*/

int arv_vazia(ArvCod* t){
	return t==NULL; //retorna 1 se arvore vazia e 0 se arvore não vazia
}

ArvCod* liberaArv(ArvCod* t){
	if(!arv_vazia(t)){
		liberaArv(t->esq); //libera sae
		liberaArv(t->dir); //libera dir
		free(t); //libera raiz
	}

	return NULL;
}

