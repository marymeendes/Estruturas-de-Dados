#include "cliente.h"
#include "lista.h"
#include "compartimento_hash.h"

void insere_table(FILE* tab, FILE* cli, Registro* r){
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
			fwrite(&ponteiro, sizeof(long), 1, cli);
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
				fread(&aux->prox, sizeof(long), 1, cli);
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
			fwrite(&ponteiro, sizeof(long), 1, cli);
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
			fread(&aux->prox, sizeof(long), 1, cli);
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
			fread(&aux->prox, sizeof(long), 1, cli);
			fread(&aux->status, sizeof(int), 1, cli);
			
			ponteiro = aux->prox;

		}while(ponteiro > -1);
		//ao término do loop, temos o antigo último elemento da lista e a posição onde está registrada o seu ->prox

		rewind(cli); //pela política	

		//posiciono o ponteiro de leitura/escrita no local de inserção do registro novo
		fseek(cli, auxiliarPosicao, SEEK_SET);
		//e insiro o novo registro
		fwrite(&r->cliente->codCliente, sizeof(int), 1, cli);
		fwrite(r->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
		fwrite(&r->prox, sizeof(long), 1, cli);
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
}