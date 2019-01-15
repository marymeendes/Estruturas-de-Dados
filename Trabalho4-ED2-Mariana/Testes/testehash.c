#include "cliente.h"
#include "lista.h"
#include "compartimento_hash.h"

int main(void){

	FILE* tab;
	FILE* cli;
	Registro* r;
	Registro* aux;

	tab = fopen("hash.dat", "r+b");
	cli = fopen("cli.dat", "r+b");

	set_table(tab, 7);

	r = (Registro*)malloc(sizeof(Registro));
	r->cliente = (Cliente*)malloc(sizeof(Cliente));

	aux = (Registro*)malloc(sizeof(Registro));
	aux->cliente = (Cliente*)malloc(sizeof(Cliente));

	r->cliente = criaCliente(28, "Mariana");
	r = reg_cria(r->cliente);

	/*--------------------------------------*/

	long hashing = h(r->cliente->codCliente);
	long ponteiro, n;
	long tamanhoArqCli, auxiliarPosicao;

	fseek(tab, hashing*sizeof(long), SEEK_SET);
	fread(&ponteiro, sizeof(long), 1, tab);

	printf("Ponteiro: %ld\n", ponteiro);

	rewind(tab);

	while(0 < fread(&n, sizeof(long), 1, tab)){
		printf("->%ld\n", n);
	}

	rewind(tab);

	//calculando tamanho do arquivo de clientes
	fseek(cli, 0, SEEK_END);
	tamanhoArqCli = ftell(cli);

	printf("Tamanho arquivo dos clientes: %ld\n", tamanhoArqCli);

	rewind(cli);

	if(ponteiro == -1 && tamanhoArqCli == 0){ //no primeiro uso do programa: lista e arquivo vazios
		auxiliarPosicao = ftell(cli);
		fwrite(&r->cliente->codCliente, sizeof(int), 1, cli);
		fwrite(r->cliente->nome, sizeof(char), sizeof(r->cliente->nome), cli);
		fwrite(&ponteiro, sizeof(int), 1, cli);
		fwrite(&r->status, sizeof(int), 1, cli);

		fseek(tab, hashing*sizeof(long), SEEK_SET);
		fwrite(&auxiliarPosicao, sizeof(long), 1, tab);

	}

	rewind(tab);

	while(0 < fread(&n, sizeof(long), 1, tab)){
		printf("-->%ld\n", n);
	}

	rewind(tab);

	/*----------------------------------------*/

	r->cliente = criaCliente(50, "Gabriel Mozao");
	r = reg_cria(r->cliente);

	hashing = h(r->cliente->codCliente);

	fseek(tab, hashing*sizeof(long), SEEK_SET);
	fread(&ponteiro, sizeof(long), 1, tab);

	printf("Ponteiro2: %ld\n", ponteiro);

	rewind(tab);

	while(0 < fread(&n, sizeof(long), 1, tab)){
		printf("->%ld\n", n);
	}

	rewind(tab);

	//calculando tamanho do arquivo de clientes
	fseek(cli, 0, SEEK_END);
	tamanhoArqCli = ftell(cli);

	printf("Tamanho arquivo dos clientes: %ld\n", tamanhoArqCli);

	rewind(cli);

	if(ponteiro == -1 && tamanhoArqCli > 0){

		int contador = 0;
		auxiliarPosicao = 0;

		while(auxiliarPosicao < tamanhoArqCli){
			
			fread(&aux->cliente->codCliente, sizeof(int), 1, cli);
			printf("%d\n", aux->cliente->codCliente);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
			fread(&aux->prox, sizeof(int), 1, cli);
			fread(&aux->status, sizeof(int), 1, cli);
			auxiliarPosicao = ftell(cli);
			printf("First: %ld\n", auxiliarPosicao);
			contador++;
			printf("oie\n");

			if(aux->status == 1){
				break;
			}

			getchar();
		}
		printf("%d\n", contador);
		//printf("%ld\n", auxiliarPosicao);
		printf("%d\n", contador*tamanhoRegistro());

		auxiliarPosicao = contador*tamanhoRegistro();

		rewind(cli);

		fseek(cli, auxiliarPosicao, SEEK_SET);
		auxiliarPosicao = ftell(cli);
		printf("%ld\n", auxiliarPosicao);
		fwrite(&r->cliente->codCliente, sizeof(int), 1, cli);
		fwrite(r->cliente->nome, sizeof(char), sizeof(r->cliente->nome), cli);
		fwrite(&ponteiro, sizeof(int), 1, cli);
		fwrite(&r->status, sizeof(int), 1, cli);


		fseek(tab, hashing*sizeof(long), SEEK_SET);
		fwrite(&auxiliarPosicao, sizeof(long), 1, tab);

		rewind(tab);

		while(0 < fread(&n, sizeof(long), 1, tab)){
			printf("->%ld\n", n);
		}

		rewind(tab);
	}
	
	//-----------------------------------------------*
	r->cliente = criaCliente(49, "Thalia Ferreira");
	r = reg_cria(r->cliente);

	hashing = h(r->cliente->codCliente);

	fseek(tab, hashing*sizeof(long), SEEK_SET);
	fread(&ponteiro, sizeof(long), 1, tab);

	printf("Ponteiro2: %ld\n", ponteiro);

	rewind(tab);

	//calculando tamanho do arquivo de clientes
	fseek(cli, 0, SEEK_END);
	tamanhoArqCli = ftell(cli);

	printf("Tamanho arquivo dos clientes: %ld\n", tamanhoArqCli);

	rewind(cli);

	if(ponteiro > -1){ //compartimento e arquivo não estão vazios

		long attProximo;
		int counter = 0;

		auxiliarPosicao = 0;

		while(auxiliarPosicao < tamanhoArqCli){
			
			fread(&aux->cliente->codCliente, sizeof(int), 1, cli);
			printf("%d\n", aux->cliente->codCliente);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
			fread(&aux->prox, sizeof(int), 1, cli);
			fread(&aux->status, sizeof(int), 1, cli);
			auxiliarPosicao = ftell(cli);
			printf("First: %ld\n", auxiliarPosicao);
			counter++;
			printf("oie\n");

			if(aux->status == 1){
				break;
			}

			getchar();
		}
		printf("%d\n", counter);
		//printf("%ld\n", auxiliarPosicao);
		printf("%d\n", counter*tamanhoRegistro());

		auxiliarPosicao = counter*tamanhoRegistro(); //guardando posição de inserção

		rewind(cli);

		do{
			fseek(cli, ponteiro, SEEK_SET);

			fread(&aux->cliente->codCliente, sizeof(int), 1, cli);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
			attProximo = ftell(cli);
			fread(&aux->prox, sizeof(int), 1, cli);
			fread(&aux->status, sizeof(int), 1, cli);
			//auxiliarPosicao = ftell(cli);
			//printf("First: %ld\n", auxiliarPosicao);
			ponteiro = aux->prox;
			printf("aloha\n");
			printf("%ld\n", attProximo);

			getchar();
		}while(ponteiro > -1);

		rewind(cli);

		fseek(cli, auxiliarPosicao, SEEK_SET);

		fwrite(&r->cliente->codCliente, sizeof(int), 1, cli);
		fwrite(r->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), cli);
		fwrite(&r->prox, sizeof(int), 1, cli);
		fwrite(&r->status, sizeof(int), 1, cli);

		printf("%ld\n", auxiliarPosicao);

		rewind(cli);

		//int c = 2;

		fseek(cli, attProximo, SEEK_SET);
		fwrite(&auxiliarPosicao, sizeof(int), 1, cli); //mantendo encadeamento

		rewind(cli);

		while(0 < fread(&n, sizeof(long), 1, tab)){
			printf("->%ld\n", n);
		}

		printf("HEHE\n");

	}

	return 0;

}