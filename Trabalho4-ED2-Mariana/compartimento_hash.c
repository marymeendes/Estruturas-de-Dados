#include "compartimento_hash.h"

int h(int x){ //função de hashing
	return x%7;
}

void set_table(FILE* tab, int tabSize){
	rewind(tab);

	long hashTable[tabSize];

	int i;
	for(i=0; i<tabSize; i++){
		hashTable[i] = -1; //como trata-se de arquivo, -1 representa o NULL (nossa tabela hash possui ponteiros para as listas encadeadas de registros)
							//por ser arquivo, esses ponteiros são inteiros que representam a posição do primeiro elemento da lista no arquivo de registros
		fwrite(&hashTable[i], sizeof(long), 1, tab);
	}

	rewind(tab);

	printf("olá\n");
}

int insere_table(FILE* tab, FILE* cli, Registro* r){
	rewind(tab); rewind(cli); //resetando ponteiros de leitura/escrita dos arquivos (precaução)
	//política do código: sempre após o uso de um arquivo: dar rewind(arquivo);

	////SETANDO VARIÁVEIS, AUXILIARES E FLAGS////
	Registro* aux;
	aux = (Registro*)malloc(sizeof(Registro));
	aux->cliente = (Cliente*)malloc(sizeof(Cliente));

	long hashing = h(r->cliente->codCliente);//1º passo: aplicar a função de hash na chave do registro
	
	long ponteiro, nTabelaHash, contador, attProximo;
	long tamanhoArqCli, auxiliarPosicao;

	////FIM DO SET DE VARIÁVEIS, AUXILIARES E FLAGS//// 

	//2º passo: acessar o compartimento apontado pela função de hashing
	fseek(tab, hashing*sizeof(long), SEEK_SET);
	//e ler seu ponteiro
	fread(&ponteiro, sizeof(long), 1, tab);
	rewind(tab); //reinicializando o ponto de leitura do arquivo da tabela (precaução)

	//3º e grande passo: Inserção do cliente no arquivo de clientes

	//3.1: calculando o tamanho do arquivo de clientes
	fseek(cli, 0, SEEK_END);
	tamanhoArqCli = ftell(cli); //se tamanhoArqCli = 0, então arquivo vazio ;)
	rewind(cli); //de acordo com a política

	//3.2: Inserindo o registro com compartimento da tabela apontando pra "NULL"
	if(ponteiro == -1){//lista do compartimento apontado está vazia

		//3.2.1: inserindo com o arquivo vazio
		if(tamanhoArqCli == 0){ //e o arquivo está vazio, logo, pode-se inserir direto o cliente (caso + fácil)

			auxiliarPosicao = ftell(cli); //guarda-se a posição de inserção
			//faz-se a inserção
			fwrite(&r->cliente->codCliente, sizeof(int), 1, cli);
			fwrite(r->cliente->nome, sizeof(char), sizeof(r->cliente->nome), cli);
			fwrite(&ponteiro, sizeof(int), 1, cli);
			fwrite(&r->status, sizeof(int), 1, cli);

			//atualiza-se ponteiro pra lista no compartimento da tabela hash com a posição de inserção do registro
			fseek(tab, hashing*sizeof(long), SEEK_SET);
			fwrite(&auxiliarPosicao, sizeof(long), 1, tab);

			rewind(cli); rewind(tab); //de acordo com a política

		//3.2.2: inserindo com o arquivo contendo informações prévias
		}else if(tamanhoArqCli > 0){ //e arquivo já tem informação, logo, deve procurar o espaço vago para inserção
			contador = 0;
			auxiliarPosicao = 0;

			//percorre-se os registros já contidos no arquivo em busca de um espaço vago
			while(auxiliarPosicao < tamanhoArqCli){
			
				fread(&aux->cliente->codCliente, sizeof(int), 1, cli);
				fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
				fread(&aux->prox, sizeof(int), 1, cli);
				fread(&aux->status, sizeof(int), 1, cli);
				auxiliarPosicao = ftell(cli);
				
				contador++;

				if(aux->status == 1){
					break;
				}
			}
			//esse espaço vago pode estar no final do arquivo (qnd o while termina pela sua condição de parada)
			//ou no meio do arquivo (qnd o while é interrompido pelo break)

			//ao término do loop, portanto, verifica-se qual foi o caso
			if(aux->status == 1){//se a condição do break foi cumprida
				auxiliarPosicao = (contador-1)*tamanhoRegistro();
			}else{ //se o loop correu livremente hehe
				auxiliarPosicao = contador*tamanhoRegistro();
			}

			rewind(cli); //pela política

			//ajusto o ponteiro de leitura/escrita para a posição de inserção e insiro o registro
			fseek(cli, auxiliarPosicao, SEEK_SET);
			fwrite(&r->cliente->codCliente, sizeof(int), 1, cli);
			fwrite(r->cliente->nome, sizeof(char), sizeof(r->cliente->nome), cli);
			fwrite(&ponteiro, sizeof(int), 1, cli);
			fwrite(&r->status, sizeof(int), 1, cli);

			//atualiza-se ponteiro pra lista no compartimento da tabela hash com a posição de inserção do registro
			fseek(tab, hashing*sizeof(long), SEEK_SET);
			fwrite(&auxiliarPosicao, sizeof(long), 1, tab);
			
			rewind(cli); rewind(tab); //pela política

		}	
	//3.2: Inserindo o registro com compartimento da tabela apontando pra uma lista
	}else if(ponteiro > -1){//compartimento e arquivo não estão vazios, logo, é necessário buscar espaço vago e percorrer a lista
		contador = 0;
		auxiliarPosicao = 0;

		//percorre-se os registros já contidos no arquivo em busca de um espaço vago
		while(auxiliarPosicao < tamanhoArqCli){
			
			fread(&aux->cliente->codCliente, sizeof(int), 1, cli);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
			fread(&aux->prox, sizeof(int), 1, cli);
			fread(&aux->status, sizeof(int), 1, cli);
			auxiliarPosicao = ftell(cli);
				
			contador++;

			if(aux->status == 1){
				break;
			}
		}
		//esse espaço vago pode estar no final do arquivo (qnd o while termina pela sua condição de parada)
		//ou no meio do arquivo (qnd o while é interrompido pelo break)

		//ao término do loop, portanto, verifica-se qual foi o caso
		if(aux->status == 1){//se a condição do break foi cumprida
			auxiliarPosicao = (contador-1)*tamanhoRegistro();
		}else{ //se o loop correu livremente hehe
			auxiliarPosicao = contador*tamanhoRegistro();
		}

		rewind(cli); //pela política

		//percorre-se a lista em busca do seu último elemento para manter o encadeamento
		do{
			fseek(cli, ponteiro, SEEK_SET);

			fread(&aux->cliente->codCliente, sizeof(int), 1, cli);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
			attProximo = ftell(cli);
			fread(&aux->prox, sizeof(int), 1, cli);
			fread(&aux->status, sizeof(int), 1, cli);

			/*if(aux->cliente->codCliente == r->cliente->codCliente){
				printf("Erro na inserção: Registro já inserido! hehe\n");
				free(aux->cliente);
				free(aux);
				return 0; //caso aja erro na inserção
			}*/
			
			ponteiro = aux->prox;

		}while(ponteiro > -1);
		//ao término do loop, temos o antigo último elemento da lista e a posição onde está registrada o seu ->prox

		rewind(cli); //pela política	

		//posiciono o ponteiro de leitura/escrita no local de inserção do registro novo
		fseek(cli, auxiliarPosicao, SEEK_SET);
		//e insiro o novo registro
		fwrite(&r->cliente->codCliente, sizeof(int), 1, cli);
		fwrite(r->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
		fwrite(&r->prox, sizeof(int), 1, cli);
		fwrite(&r->status, sizeof(int), 1, cli);

		rewind(cli); //pela política
		//posiciono o ponteiro de leitura/escrita para o local em que está armazenado
		//o ->prox do antigo último elemento e o atualizo para a posição de inserção
		//do novo elemento
		fseek(cli, attProximo, SEEK_SET);
		fwrite(&auxiliarPosicao, sizeof(long), 1, cli); //mantendo encadeamento

		rewind(cli);
	}

	printf("\nRegistro inserido com sucesso! :3\n");

	/////////PARA TESTES//////////

	while(0 < fread(&nTabelaHash, sizeof(long), 1, tab)){
			printf("->%ld\n", nTabelaHash);
	}
	rewind(tab);
	printf("HEHE\n");

	free(aux->cliente);
	free(aux);

	return 1; //se correu tudo ok
}

void remove_table(FILE* tab, FILE* cli, int chave){
	rewind(tab); rewind(cli);

	////SETANDO VARIÁVEIS, AUXILIARES E FLAGS////

	Cliente* c = criaCliente(-1, "XXXX");
	Registro* anterior = reg_cria(c);

	Registro* aux = (Registro*)malloc(sizeof(Registro));
	aux->cliente = (Cliente*)malloc(sizeof(Cliente));

	long hashing = h(chave); //aplicando função de hashing na chave do registro a ser excluído
	long ponteiro, attProximo, attProximoAnterior, attStatus, savedPointer, achou, nTabelaHash;

	////FIM DO SET DE VARIÁVEIS, AUXILIARES E FLAGS//// 

	fseek(tab, hashing*sizeof(long), SEEK_SET);//posiciono ponteiro do arquivo para a posição correta da tabela hash
	fread(&ponteiro, sizeof(long), 1, tab);
	rewind(tab); //pela política

	if(ponteiro == -1){ //se o compartimento aponta pra NULL, então sua lista é vazia e já sabemos, portanto, que o elemento não se encontra nos arquivos
		printf("Erro na exclusão: Registro não encontrado!\n");
	}else{ //senao, devemos procurar pelo registro na lista
		
		achou = 0;

		fseek(cli, ponteiro, SEEK_SET); //posiciono o ponteiro no início da lista no arquivo de registros (cli)
		//percorre-se a lista
		do{
			fseek(cli, ponteiro, SEEK_SET);

			savedPointer = ftell(cli);
			fread(&aux->cliente->codCliente, sizeof(int), 1, cli);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
			attProximo = ftell(cli);
			fread(&aux->prox, sizeof(int), 1, cli);
			attStatus = ftell(cli);
			fread(&aux->status, sizeof(int), 1, cli);

			if(aux->cliente->codCliente == chave){//ao achar o registro a ser excluído, para-se o loop
				achou = 1;
				break;
			}else{
				anterior = aux;
				attProximoAnterior = attProximo;
			}

			ponteiro = aux->prox;

		}while(ponteiro > -1);

		rewind(cli);

		if(achou == 0){ 
			printf("Erro na exclusão: Registro não encontrado!\n");
		}

		if(achou){
			if(anterior->cliente->codCliente == -1){ //anterior não foi att, logo, item a ser excluído é o primeiro
				//excluo o registro
				fseek(cli, attStatus, SEEK_SET);
				aux->status = 1;
				fwrite(&aux->status, sizeof(int), 1, cli);

				//ajustando o compartimento da tabela pra apontar pra aux->prox
				fseek(tab, hashing*sizeof(long), SEEK_SET);
				long extra = aux->prox;
				fwrite(&extra, sizeof(long), 1, tab);
			
			}else{//anterior modificado, logo o registro a ser excluído está no "meio"
				//excluo o registro
				fseek(cli, attStatus, SEEK_SET);
				aux->status = 1;
				fwrite(&aux->status, sizeof(int), 1, cli);

				//mantenho o encadeamento
				fseek(cli, attProximoAnterior, SEEK_SET);//coloco o ponteiro de leitura/escrita onde li o ->prox do anterior
				long extra = aux->prox;
				fwrite(&extra, sizeof(long), 1, cli);//faço anterior apontar pra aux->prox
			}

			rewind(cli); rewind(tab); //pela política

			printf("Cliente removido com sucesso!\n");
		}

		/////////PARA TESTES//////////

		while(0 < fread(&nTabelaHash, sizeof(long), 1, tab)){
			printf("->%ld\n", nTabelaHash);
		}
		rewind(tab);
		printf("HEHE\n");
	}
	
	free(aux->cliente);
	free(aux);
	free(anterior->cliente);
	free(anterior);
}

Registro* busca_table(FILE* tab, FILE* cli, int chave){ //lembrar de dar free(registro)
	rewind(tab); rewind(cli); //pela poĺítica

	////SETANDO VARIÁVEIS, AUXILIARES E FLAGS////

	Registro* aux = (Registro*)malloc(sizeof(Registro));
	aux->cliente = (Cliente*)malloc(sizeof(Cliente));

	int hashing = h(chave); //aplicando função de hashing na chave do registro a ser excluído
	int ponteiro, achou;

	////FIM DO SET DE VARIÁVEIS, AUXILIARES E FLAGS//// 
	
	fseek(tab, hashing*sizeof(long), SEEK_SET);//posiciono ponteiro do arquivo para a posição correta da tabela hash
	fread(&ponteiro, sizeof(long), 1, tab);
	rewind(tab);

	if(ponteiro == -1){
		printf("Erro na busca: Cliente não encontrado!\n");
		return NULL;
	}else{

		achou = 0;

		do{ //percorrendo a lista
			fseek(cli, ponteiro, SEEK_SET); //posiciono o ponteiro do arquivo de clientes na posição indicada pelo compartimento da tabela hash

			fread(&aux->cliente->codCliente, sizeof(int), 1, cli);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
			fread(&aux->prox, sizeof(int), 1, cli);
			fread(&aux->status, sizeof(int), 1, cli);

			if(aux->cliente->codCliente == chave && aux->status == 0){ //verifica-se tbm o status, pois caso o registro buscado tenha acabado de ser excluído
				achou = 1;											//e, portanto, ainda esteja no arquivo como lixo, ele não poderá ser encontrado
				break;
			}

			ponteiro = aux->prox;

		}while(ponteiro > -1);

		if (achou == 0){
			printf("Erro na busca: Cliente não encontrado!\n");
			return NULL;
		}

		if(achou){
			return aux;
		}
	}
}