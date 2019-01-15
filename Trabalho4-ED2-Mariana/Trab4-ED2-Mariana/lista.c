#include "lista.h"

Registro* reg_cria(Cliente* cli){ //recebe um cliente, retorna um registro pra ser inserido na tabela hash
	
	Registro* novo = (Registro*)malloc(sizeof(Registro));
	novo->cliente = cli;
	novo->prox = -1;
	novo->status = 0;

	return novo;
}

int tamanhoRegistro(){
	return tamanho()  //tamanho do Cliente
			+ sizeof(int) //tamanho do ponteiro pro próximo
			+ sizeof(int); //tamanho do status
}
