#include "lefkowitz.h"

void geraClientes();
void imprimeCli(FILE* clientes);
void imprimeA1(FILE* a1);
void imprimeA2(FILE* a2);
void imprimeA3(FILE* a3);
void imprimeA4(FILE* a4);
void imprimeA5(FILE* a5);
void imprimeA6(FILE* a6);
void imprimeA7(FILE* a7);
void imprimeA8(FILE* a8);

int main(void){

	geraClientes();

	FILE *clis, *a1, *a2, *a3, *a4, *a5, *a6, *a7, *a8;

	if((clis = fopen("clientes.dat", "rb")) == NULL){
		printf("Erro na abertura de clientes para leitura D:\n");
		exit(1);
	}

	imprimeCli(clis);

	//passo 1.1
	ordenaCP(clis);

	if((a1 = fopen("A1.dat", "rb")) == NULL){
		printf("Erro na abertura de A1 para leitura D:\n");
		exit(1);
	}

	imprimeA1(a1);

	printf("\nPressione qualquer tecla para continuar...\n");
	getchar();

	//passo 1.2
	criaA2(a1);

	if((a2 = fopen("A2.dat", "rb")) == NULL){
		printf("Erro na abertura de A2 para leitura D:\n");
		exit(1);
	}

	imprimeA2(a2);

	printf("\nPressione qualquer tecla para continuar...\n");
	getchar();

	//ṕasso 2
	criaA3(a2);

	if((a3 = fopen("A3.dat", "rb")) == NULL){
		printf("Erro na abertura de A3 para leitura D:\n");
		exit(1);
	}

	imprimeA3(a3);

	printf("\nPressione qualquer tecla para continuar...\n");
	getchar();

	//passo 3
	ordenaPorIdade(a3);

	if((a4 = fopen("A4.dat", "rb")) == NULL){
		printf("Erro na abertura de A4 para leitura D:\n");
		exit(1);
	}

	imprimeA4(a4);

	printf("\nPressione qualquer tecla para continuar...\n");
	getchar();

	//passo 4
	criaA5(a4);

	if((a5 = fopen("A5.dat", "rb")) == NULL){
		printf("Erro na abertura de A5 para leitura D:\n");
		exit(1);
	}

	imprimeA5(a5);

	printf("\nPressione qualquer tecla para continuar...\n");
	getchar();

	criaA6(a4, a5);

	if((a6 = fopen("A6.dat", "rb")) == NULL){
		printf("Erro na abertura de A6 para leitura D:\n");
		exit(1);
	}

	imprimeA6(a6);

	printf("Pressione qualquer tecla para continuar...\n");
	getchar();

	//passo 5
	criaA7(a6);

	if((a7 = fopen("A7.dat", "rb")) == NULL){
		printf("Erro na abertura de A7 para leitura D:\n");
		exit(1);
	}

	imprimeA7(a7);

	printf("Pressione qualquer tecla para continuar...\n");
	getchar();

	//passo 6
	criaA8(a1, a7);

	if((a8 = fopen("A8.dat", "rb")) == NULL){
		printf("Erro na abertura de A8 para leitura D:\n");
		exit(1);
	}

	imprimeA8(a8);

	printf("\nExecução concluída!\nPressione qualquer tecla para imprimir resultados...\n");
	getchar();

	imprimeA5(a5);

	imprimeA8(a8);

	int fcloseall();

	return 0;
}

void geraClientes(){
	FILE* clientes;

	if((clientes = fopen("clientes.dat", "wb")) == NULL){
		printf("Erro na abertura de clientes D:\n");
		exit(1);
	}

	Cliente *c1, *c2, *c3, *c4, *c5, *c6, *c7;

	c1 = criaCliente(16, "Charlote", 13);
	salva(c1, clientes);

	c2 = criaCliente(10, "André", 13);
	salva(c2, clientes);

	c3 = criaCliente(30, "Antonella", 14);
	salva(c3, clientes);

	c4 = criaCliente(21, "Carlos", 15);
	salva(c4, clientes);

	c5 = criaCliente(2, "Luiza", 15);
	salva(c5, clientes);

	c6 = criaCliente(53, "Gabriel", 17);
	salva(c6, clientes);

	c7 = criaCliente(42, "Mariana", 15);
	salva(c7, clientes);

	free(c1); free(c2); free(c3); free(c4); free(c5); free(c6); free(c7);

	fclose(clientes);
}

void imprimeCli(FILE* clientes){
	rewind(clientes);

	Cliente* c;

	printf("\nArquivo de clientes:\n\n");

	printf("************************\n");
	while((c = le(clientes)) != NULL){
		printf("%d | ", c->codCliente);
		printf("%s | ", c->nome);
		printf("%d\n", c->idade);
	}
	printf("************************\n");

	rewind(clientes);
}

void imprimeA1(FILE* a1){
	rewind(a1);

	Cliente* c;

	printf("\nArquivo de clientes ordenado por CP:\n\n");

	printf("************************\n");
	while((c = le(a1)) != NULL){
		printf("%d | ", c->codCliente);
		printf("%s | ", c->nome);
		printf("%d\n", c->idade);
	}
	printf("************************\n");

	rewind(a1);
}

void imprimeA2(FILE* a2){
	rewind(a2);

	EstruturaA2* aux;

	printf("\nArquivo de chave secundária indexada:\n\n");

	printf("************************\n");
	while((aux = leA2(a2)) != NULL){
		printf("%d | ", aux->enderecoDisco);
		printf("%d | ", aux->chavePrim);
		printf("%d\n", aux->chaveSec);
	}
	printf("************************\n");

	rewind(a2);
}

void imprimeA3(FILE* a3){
	rewind(a3);

	EstruturaA3* aux;

	printf("\nArquivo de cada chave secundária indexada:\n\n");

	printf("************************\n");
	while((aux = leA3(a3)) != NULL){
		printf("%d | ", aux->enderecoDisco);
		printf("%d | ", aux->chavePrim);
		printf("%d\n", aux->chaveSec_i);
	}
	printf("************************\n");

	rewind(a3);
}

void imprimeA4(FILE* a4){
	rewind(a4);

	EstruturaA3* aux;

	printf("\nArquivo A3 ordenado por idade:\n\n");

	printf("************************\n");
	while((aux = leA3(a4)) != NULL){
		printf("%d | ", aux->enderecoDisco);
		printf("%d | ", aux->chavePrim);
		printf("%d\n", aux->chaveSec_i);
	}
	printf("************************\n");

	rewind(a4);
}

void imprimeA5(FILE* a5){
	rewind(a5);

	EstruturaA5* aux;

	printf("\nArquivo de indice:\n\n");

	printf("************************\n");
	while((aux = leA5(a5)) != NULL){
		printf("%d | ", aux->chaveSec_i);
		printf("%d | ", aux->ponteiro);
		printf("%d\n", aux->quantidade);
	}
	printf("************************\n");

	rewind(a5);
}

void imprimeA6(FILE* a6){
	rewind(a6);

	EstruturaA6* aux;

	printf("\nArquivo de registros ordenados por CS com ponteiro pro proximo:\n\n");

	printf("************************\n");
	while((aux = leA6(a6)) != NULL){
		printf("%d | ", aux->enderecoDisco);
		printf("%d | ", aux->chavePrim);
		printf("%d | ", aux->chaveSec_i);
		printf("%d\n", aux->proximo);
	}
	printf("************************\n");

	rewind(a6);
}

void imprimeA7(FILE* a7){
	rewind(a7);

	EstruturaA6* aux;

	printf("\nArquivo A6 ordenado por CP:\n\n");

	printf("************************\n");
	while((aux = leA6(a7)) != NULL){
		printf("%d | ", aux->enderecoDisco);
		printf("%d | ", aux->chavePrim);
		printf("%d | ", aux->chaveSec_i);
		printf("%d\n", aux->proximo);
	}
	printf("************************\n");

	rewind(a7);
}


void imprimeA8(FILE* a8){
	rewind(a8);

	EstruturaA8* aux;

	printf("\nArquivo de dados:\n\n");

	printf("************************\n");
	while((aux = leA8(a8)) != NULL){
		printf("%d | ", aux->codCliente);
		printf("%s | ", aux->nome);
		printf("%d | ", aux->idade);
		printf("%d\n", aux->prox);
	}
	printf("************************\n");

	rewind(a8);
}
