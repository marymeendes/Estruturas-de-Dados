#include "compartimento_hash.h"

void insere_6_clientes(FILE* out);
Registro* le_cliente(FILE *in);

int main(void){
	FILE* baseFile;
	FILE* tabHash;

	Registro* aux;
	Cliente* c;
	Registro* r;

	int endereco;

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

	set_table(tabHash);

	////INSERINDO CLIENTES////

	printf("Inserindo os clientes na tabela...\n");
	while((aux = le_cliente(baseFile)) != NULL){
		insere_table(tabHash, aux);
		free(aux->cliente);
		free(aux);
	}

	////REMOVENDO O JOÃO////

	remove_table(tabHash, 49); //vai ficar com status = 0

	////BUSCANDO PELA MARIA////

	endereco = busca_table(tabHash, 59);

	printf("Endereço do registro procurado: %d\n", endereco); //tem que imprimir 448

	////INSERINDO UM NOVO CLIENTE NO LUGAR DO JOÃO////

	c = criaCliente(37, "Marilda");
	r = reg_cria(c);

	insere_table(tabHash, r);

	////INSERINDO MAIS UM REGISTRO QUE NÃO TERÁ ESPAÇO PRA SER ARMAZENADO NA ZONA DE COLISÕES///
	c = criaCliente(67, "Carlos");
	r = reg_cria(c);

	insere_table(tabHash, r);

	return 0;
}

void insere_6_clientes(FILE* out){

    printf("Inserindo 6 clientes no arquivo...\n");
    
    Cliente* c1 = criaCliente(49, "João");
    salva(c1, out);
    free(c1);
    Cliente* c2 = criaCliente(51, "Ana");
    salva(c2, out);
    free(c2);
    Cliente* c3 = criaCliente(59, "Maria");
    salva(c3, out);
    free(c3);
    Cliente* c4 = criaCliente(10, "Janio");
    salva(c4, out);
    free(c4);
    Cliente* c5 = criaCliente(103, "Pedro");
    salva(c5, out);
    free(c5);
    Cliente* c6 = criaCliente(63, "Joanna");
    salva(c6, out);
    free(c6);

    printf("Inserção concluída!\n\n");
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