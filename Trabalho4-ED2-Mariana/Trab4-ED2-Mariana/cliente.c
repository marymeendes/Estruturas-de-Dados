#include "cliente.h"

// Imprime cliente
void imprime(Cliente *cliente) {
    printf("************************************************");
    printf("\nCliente de código: ");
    printf("%d", cliente->codCliente);
    printf("\nNome: ");
    printf("%s", cliente->nome);
    printf("\n*************************************************\n");
}

// Cria cliente. Lembrar de usar free(cliente)
Cliente *criaCliente(int cod, char *nome) {
    Cliente *cliente = (Cliente *) malloc(sizeof(Cliente));
    //inicializa espaço de memória com ZEROS
    if (cliente) memset(cliente, 0, sizeof(Cliente));
    //copia valores para os campos de cliente
    cliente->codCliente = cod;
    strcpy(cliente->nome, nome);
    return cliente;
}

// Salva cliente no arquivo out, na posicao atual do cursor
void salva(Cliente *cliente, FILE *out) {
    fwrite(&cliente->codCliente, sizeof(int), 1, out);
    //cliente->nome ao invés de &cliente->nome, pois string já é ponteiro
    fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), out);
}

// Le um cliente do arquivo in na posicao atual do cursor
// Retorna um ponteiro para cliente lido do arquivo
Cliente* le(FILE *in) {
    Cliente *cliente = (Cliente *) malloc(sizeof(Cliente));
    if (0 >= fread(&cliente->codCliente, sizeof(int), 1, in)) {
	   free(cliente);
	   return NULL;
    }
    fread(cliente->nome, sizeof(char), sizeof(cliente->nome), in);
    return cliente;
}

// Retorna tamanho do cliente em bytes
int tamanho() {
    return sizeof(int)  //codCliente
            + sizeof(char) * 100; //nome
}

void insere_clientes(FILE *out, int qtde) { //insere qtde x de clientes num arquivo para os testes
    int i;
    Cliente* c;
    char nomeCliente[40];

    printf("Inserindo %d clientes no arquivo...", qtde);
    
    for(i=0; i<qtde; i++){
        sprintf(nomeCliente, "Carla%d", i);
        c = criaCliente(1+(rand()%1000), nomeCliente);
        salva(c, out);
        free(c);
    }      
}