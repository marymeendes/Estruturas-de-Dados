#include "compartimento_hash.h"

void insere_6_clientes(FILE* out);
Registro* le_cliente(FILE *in);

int main(void){
	FILE* baseFile;
	FILE* tabHash;
	FILE* clientes;
	Registro* aux1;
	Registro* aux2;
	Registro* aux3;
	Registro* aux4;
	Registro* aux5;
	Registro* aux6;

	if((baseFile = fopen("fonteClientes.dat", "r+b")) == NULL){
		printf("Erro ao abrir o arquivo base D:\n");
		exit(1);
	}

	insere_6_clientes(baseFile);
	rewind(baseFile);

	if((tabHash = fopen("tabHash.dat", "r+b")) == NULL){
		printf("Erro ao abrir a tabela hash D:\n");
		exit(1);
	}

	if((clientes = fopen("clientes.dat", "r+b")) == NULL){
		printf("Erro ao abrir o arquivo dos clientes D:\n");
		exit(1);
	}

	set_table(tabHash, 7);

	////INSERINDO CLIENTES////

	aux1 = le_cliente(baseFile);
	insere_table(tabHash, clientes, aux1);
	free(aux1->cliente);
	free(aux1);

	aux2 = le_cliente(baseFile);
	insere_table(tabHash, clientes, aux2);
	free(aux2->cliente);
	free(aux2);

	aux3 = le_cliente(baseFile);
	insere_table(tabHash, clientes, aux3);
	free(aux3->cliente);
	free(aux3);

	aux4 = le_cliente(baseFile);
	insere_table(tabHash, clientes, aux4);
	free(aux4->cliente);
	free(aux4);

	aux5 = le_cliente(baseFile);
	insere_table(tabHash, clientes, aux5);
	free(aux5->cliente);
	free(aux5);

	aux6 = le_cliente(baseFile);
	insere_table(tabHash, clientes, aux6);
	free(aux6->cliente);
	free(aux6);

	remove_table(tabHash, clientes, 49);

	aux1 = busca_table(tabHash, clientes, 3);

	imprime(aux1->cliente);

	return 0;
}

void insere_6_clientes(FILE* out){

    printf("Inserindo 6 clientes no arquivo...\n");
    
    Cliente* c1 = criaCliente(49, "João");
    salva(c1, out);
    free(c1);
    Cliente* c2 = criaCliente(51, "Carla");
    salva(c2, out);
    free(c2);
    Cliente* c3 = criaCliente(59, "Maria");
    salva(c3, out);
    free(c3);
    Cliente* c4 = criaCliente(3, "José");
    salva(c4, out);
    free(c4);
    Cliente* c5 = criaCliente(87, "Bia");
    salva(c5, out);
    free(c5);
    Cliente* c6 = criaCliente(103, "Ana");
    salva(c6, out);
    free(c6); 

    printf("Inserção concluída!\n");
}

Registro* le_cliente(FILE *in) { //lê um cliente do arquivo base e cria um registro pra inserção

    Cliente* c;
    Registro* r;

    c = le(in);

    if(c == NULL){
    	free(c);
    	return NULL;
    }
    	
    r = reg_cria(c);

    return r;
}