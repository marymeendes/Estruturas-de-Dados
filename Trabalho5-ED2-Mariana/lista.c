#include "lista.h"

Registro* reg_cria(Cliente* cli){ //recebe um cliente, retorna um registro pra ser inserido na tabela hash
	
	Registro* novo = (Registro*)malloc(sizeof(Registro));
	novo->cliente = cli;
	novo->prox = -1;
	novo->status = 1;

	return novo;
}

int tamanhoRegistro(){
	return tamanho()  //tamanho do Cliente
			+ sizeof(int) //tamanho do ponteiro pro próximo
			+ sizeof(int); //tamanho do status
}

Registro* cria_reg_vazio(){ //cria registros nulos para incialização da tabela
    static int i = 0;
    Cliente* c;
    Registro* r;
    char nomeCliente[40];
   
    sprintf(nomeCliente, "XXXXXX%d", i);
    c = criaCliente(-1, nomeCliente);
    r = reg_cria(c);

    r->status = 0; //pois é um regitro vazio

    i++; 

    return r;     
}
