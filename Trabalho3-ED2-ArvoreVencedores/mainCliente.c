
#include "cliente.h"
#include "selecaoSubstituicao.h"
#include "arvVencedores.h"

void insere_clientes(FILE *out, int qtde);
void le_clientes(FILE *in, FILE* aux);

int main(void) {

    FILE *in;
    Fila* arquivos;
    int qtdeParticoes, i;
    char nome_part[15];

    if ((in = fopen("clientes.dat", "r+b")) == NULL) {
        printf("Erro ao abrir arquivo dos clientes!\n");
        exit(1);
    }else{
        insere_clientes(in, 50);
        rewind(in);
        printf("\nLista de clientes gerada! Para vê-la aperte qualquer tecla.\n");
        getchar();
        Cliente* c;
        while(!feof(in)){
            c = le(in);
            if(c != NULL){
                imprime(c);
            }
        }

        printf("\nPressione qualquer tecla para continuar...\n");
        getchar();

        FILE *aux;
        if ((aux = fopen("chaves.dat", "wb")) == NULL) {
            printf("Erro ao abrir arquivo das chaves!\n");
            exit(1);
        }else{
            le_clientes(in, aux);
            fclose(in); 
            fclose(aux);

            qtdeParticoes = substituicao("chaves.dat", 6); 
        }        
    }

    printf("\nPressione qualquer tecla para continuar...\n");
    getchar();
    
    arquivos = fila_cria();

    for(i = 1; i <= qtdeParticoes; i++){
        sprintf(nome_part, "particao%d.dat", i);
        fila_insere(arquivos, nome_part);
    }

    intercalacao(arquivos, qtdeParticoes, "saida.dat", 4); //intercala as partições gerando o arquivo com as chaves (codCliente) ordenadas

    printf("Sucesso :3\n");
    printf("Para visualizar o arquivo final ordenado execute o programa leituraSaida.c :3\n");

    return 0; 
}

void insere_clientes(FILE *in, int qtde) { //insere qtde x de clientes num arquivo para os testes
    int i;
    Cliente* c;
    char nomeCliente[40];

    printf("Inserindo %d clientes no arquivo...", qtde);
    
    for(i=0; i<qtde; i++){
        sprintf(nomeCliente, "Carlos%d", i);
        c = criaCliente(1+(rand()%1000), nomeCliente, "XX/XX/XXXX");
        salva(c, in);
        free(c);
    }      
}

void le_clientes(FILE *in, FILE* aux) { //função que preenche um arquivo auxiliar somente com os códigos dos clientes para ordenação
    printf("\n\nLendo clientes do arquivo...\n\n");
    rewind(in);
    Cliente *c;
    while ((c = le(in)) != NULL) {
        fwrite(&c->codCliente, sizeof(int), 1, aux);
        free(c);
    }
}
