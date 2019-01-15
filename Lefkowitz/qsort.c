#include "qsort.h"
//qsort(void* base, size_t num, size_t size, int *(compar)(const void*, const void*));

//algoritmo de comparação para ordenacão do arquivo original pela sua chave primária
int comparaClientesCP(const void *a, const void *b){
	Cliente **x = (Cliente**)a;
	Cliente **y = (Cliente**)b;

	if((*x)->codCliente == (*y)->codCliente){
		return 0;
	}else if((*x)->codCliente > (*y)->codCliente){
		return 1;
	}else{
		return -1;
	}
}

int comparaEstruturaA3(const void *a, const void *b){
	EstruturaA3 **x = (EstruturaA3**)a;
	EstruturaA3 **y = (EstruturaA3**)b;

	if((*x)->chaveSec_i == (*y)->chaveSec_i){
		return 0;
	}else if((*x)->chaveSec_i > (*y)->chaveSec_i){
		return 1;
	}else{
		return -1;
	}
}

int comparaEstruturaA6(const void *a, const void *b){
	EstruturaA6 **x = (EstruturaA6**)a;
	EstruturaA6 **y = (EstruturaA6**)b;

	if((*x)->chavePrim == (*y)->chavePrim){
		return 0;
	}else if((*x)->chavePrim > (*y)->chavePrim){
		return 1;
	}else{
		return -1;
	}
}


/*int main(void){

	Cliente *clientes[5];
	int i;

	clientes[0] = (Cliente*)malloc(sizeof(Cliente));
	clientes[0]->codCliente = 55;
	strcpy(clientes[0]->nome, "Marcelo");

	clientes[1] = (Cliente*)malloc(sizeof(Cliente));
	clientes[1]->codCliente = 14;
	strcpy(clientes[1]->nome, "Gideao");

	clientes[2] = (Cliente*)malloc(sizeof(Cliente));
	clientes[2]->codCliente = 18;
	strcpy(clientes[2]->nome, "Mariana");

	clientes[3] = (Cliente*)malloc(sizeof(Cliente));
	clientes[3]->codCliente = 100;
	strcpy(clientes[3]->nome, "Gabriel");

	clientes[4] = (Cliente*)malloc(sizeof(Cliente)); 
	clientes[4]->codCliente = 34;
	strcpy(clientes[4]->nome, "Alicia");

	qsort(clientes, 5, sizeof(Cliente*), comparaClientes);

	//printf("%d\n", comparaClientes(clientes[0], clientes[1]));

	for(i = 0; i<5; i++){
		printf("%d\n", clientes[i]->codCliente);
	}

	return 0;
}*/
