#include "arvVencedores.h"

//HV = 1001
//em caso de alteração do HV, é seguro substituir todos os "1001" pelo novo HV.

Arv* arvVencedor(int* v, int nFiles){ //nFiles = nFilesOpen da função intercalacao
	int i, n, ehpar;
	Arv* aux;

	if(nFiles%2 == 0){ //nFiles é par e, portanto, o n(número de arquivos intercalados) será ímpar - problema!
		n = nFiles;
		ehpar = 0;
	}else{ //se nFiles é ímpar acontece o contrário e é sucesso, posso seguir feliz com a ideia da Intercalação Ótima
		n = nFiles - 1; //(ideia da Intercalação Ótima aqui)
		ehpar = 1;
	}

	Arv* folhas[n];

	for(i=0; i < n; i++){
		if(!ehpar){
			if(i == n-1){
				folhas[i] = arv_cria(1001, -1, arv_criavazia(), arv_criavazia()); //quando n é naturalmente ímpar, eu forço a existênica de mais uma nó
			}else{																//para torná-lo par, a esse nó devo associar o HV, nesse caso 1001
				folhas[i] = arv_cria(v[i], i, arv_criavazia(), arv_criavazia());
			}																
		}else{
			folhas[i] = arv_cria(v[i], i, arv_criavazia(), arv_criavazia());
		}	
	}

	while(n > 1){
		
		Arv* pais[n/2];
		for(i=0; i<n-1; i+=2){
			aux = arv_compara(folhas[i], folhas[i+1]);
			pais[i/2] = arv_cria(aux->info.val, aux->info.fileId, folhas[i], folhas[i+1]);
		}
		
		for(i=0; i<n; i++){ //atualizando vetor folhas para receber as arvores do vetor pais
			if(i < n/2){
				folhas[i] = pais[i];
			}else{
				folhas[i] = NULL;
			}
		}

		n/=2; //no final, n é atualizado
	}

	//árvore montada! Ao final, tenho um vetor unitário pais que representa a minha árvore, ou seja, é seu nó raiz que é também o vencedor!

	return folhas[0]; //retorno a raíz da árvore de vencedores
}


void intercalacao(Fila* filesName, int filesQtde, char* outFile, int nFilesOpen){ //recebe: a fila de nomes, a quantidade de nomes na fila, o nome do arquivo de saída,
	int indice = filesQtde + 1;													//e a quantidade de arquivos que podem ser abertos simultaneamente (no caso, 4)
	char nomeParticao[15], nome_doc[15];
	int i, valido, folhas[nFilesOpen-1];
	FILE* files[nFilesOpen-1];
	FILE* out;
	Arv* vitorioso;
	Arv* aux;
	Arv* atribuidor;
	Pilha* p = pilha_cria();

	printf("Intercalando partições...\n");

	while(filesName->ini != filesName->fim){ //faz-se o procedimento abaixo até que só reste um nome de arquivo na fila, o do de saída
 
 		for(i=0; i<nFilesOpen-1; i++){ //pegando nomes dos arquivos, os abrindo e colocando seus ponteiros no vetor de FILE*
 			if(!fila_vazia(filesName)){
 				fila_retira(filesName, nomeParticao);
				if((files[i] = fopen(nomeParticao, "rb")) == NULL){
					printf("Erro ao abrir particao.\n");
					exit(1);
				} 
 			}else{
 				files[i] = NULL;
 				//break;
 			}	
 		}

 		if(!fila_vazia(filesName)){ //se, quando dessa abertura, a fila ainda não estiver vazia, gera-se um arquivo com nome padrão
 			sprintf(nome_doc, "particao%d.dat", indice);
 		}else{//se a fila ficar vazia, significa que o próximo arquivo gerado será o final e, portanto, deve ter o nome solicitado pelo usuário
 			strcpy(nome_doc, outFile);
 		}

 		if((out = fopen(nome_doc, "w+b")) == NULL){ //abertura do arquivo produto
 			printf("Erro ao abrir particao.\n");
 			exit(1);
 		}

 		//intercalação propriamente dita

 		//start
 		for(i=0; i<nFilesOpen-1; i++){
		 	if(files[i] != NULL){
		 		if(0 >= fread(&folhas[i], sizeof(int), 1, files[i])){
		 			folhas[i] = 1001;
		 		}
			}else{
				folhas[i] = 1001;
			}
	 	}
		 	
		vitorioso = arvVencedor(folhas, 4); //nesse caso de testes, são suportados apenas 4 arquivos simultâneos
		fwrite(&vitorioso->info.val, sizeof(int), 1, out); 

	 	//continue	
	 	valido = 1;
	 	while(valido){

		 	pilha_push(p, vitorioso);

		 	aux = arv_igualdadePaterna(vitorioso);
		 	while(aux != NULL){
		 		pilha_push(p, aux);
		 		aux = arv_igualdadePaterna(aux);
		 	}

		 	aux = pilha_pop(p);
		 	if(files[aux->info.fileId] != NULL){
		 		if(0 >= fread(&aux->info.val, sizeof(int), 1, files[aux->info.fileId])){
		 			aux->info.val = 1001;
		 		}
		 	}else{
		 		aux->info.val = 1001;
		 	}

		 	while(!pilha_vazia(p)){
		 		aux = pilha_pop(p);
		 		atribuidor = arv_compara(aux->esq, aux->dir);
		 		aux->info.val = atribuidor->info.val;
		 		aux->info.fileId = atribuidor->info.val;
		 	}//aux sai do loop com o novo vencedor

		 	if(aux->info.val == 1001){
		 		valido = 0;
		 	}else{
		 		fwrite(&aux->info.val, sizeof(int), 1, out); 
		 	}
		 	
		}
		//end

 		fila_insere(filesName, nome_doc); //inserção do nome do arquivo produto na fila

 		rewind(out); //só por garantia

 		indice++; //atualização do indice
	
		int fcloseall(); //fechamento dos arquivos
	}

	arv_libera(vitorioso);
	pilha_libera(p);
	fila_libera(filesName);

	printf("Intercalação concluída!\n");
}
