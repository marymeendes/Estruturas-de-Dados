#include "compartimento_hash.h"

int h(int x){ //função de hashing
	return x%4; //4 espaços e endereçamento e 3 de colisão
}

void set_table(FILE* tab){ //seta tabela hash com registros nulos
	rewind(tab);

	int c;
	Registro* r;
	r = cria_reg_vazio();

	for(c = 0; c < 7; c++){
		fwrite(&r->cliente->codCliente, sizeof(int), 1, tab);
		fwrite(r->cliente->nome, sizeof(char), sizeof(r->cliente->nome), tab);
		fwrite(&r->prox, sizeof(int), 1, tab);
		fwrite(&r->status, sizeof(int), 1, tab);
	}

	rewind(tab);
	free(r);
}

int busca_table(FILE* tab, int chave){ //lembrar de dar free(registro)
	printf("\nBuscando registro de chave %d...", chave);

	rewind(tab);//pela poĺítica

	////SETANDO VARIÁVEIS, AUXILIARES E FLAGS////

	Registro* aux = (Registro*)malloc(sizeof(Registro));
	aux->cliente = (Cliente*)malloc(sizeof(Cliente));

	int hashing = h(chave); //aplicando função de hashing na chave do registro buscado
	int codigo, status, p = 4, s = 7, i; //p = limite do espaço de hashing e s é o limite da zona de colisões
	int end = hashing*tamanhoRegistro();

	////FIM DO SET DE VARIÁVEIS, AUXILIARES E FLAGS//// 

	fseek(tab, end, SEEK_SET);//posiciono ponteiro do arquivo para a posição correta da tabela hash
	fread(&codigo, sizeof(int), 1, tab); //leio o código do cliente naquela posição
	rewind(tab);
	fseek(tab, (end + tamanho() + sizeof(int)), SEEK_SET);
	fread(&status, sizeof(int), 1, tab); //leio o status do cliente naquela posição

	if(codigo == -1 || status == 0){ //compartimento vazio
		free(aux->cliente);
		free(aux);
		return end; //local onde o registro pode ser inserido
	}else{

		do{ //percorrendo a lista
			fseek(tab, end, SEEK_SET); //posiciono o ponteiro do arquivo de clientes na posição indicada pela função de hashing

			fread(&aux->cliente->codCliente, sizeof(int), 1, tab);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), tab);
			fread(&aux->prox, sizeof(int), 1, tab);
			fread(&aux->status, sizeof(int), 1, tab);

			if(aux->cliente->codCliente == chave && aux->status == 1){ //verifica-se tbm o status, pois caso o registro buscado tenha acabado de ser excluído
																	//e, portanto, ainda esteja no arquivo como lixo, ele não poderá ser encontrado
				free(aux->cliente);
				free(aux);
				return end; //retorno o endereço do registro
			}

			end = aux->prox;

		}while(end > -1);

		//se saiu do while sem sair da função, o registro não foi encontrado
	 	//se eu não achei o registro, posso inserí-lo caso haja espaço
		rewind(tab);
		fseek(tab, p*tamanhoRegistro(), SEEK_SET); //posiciono ponteiro na zona de colisão

		for(i = p; i < s; i++){ //procurando espaço pra possível inserção na zona de colisão
			
			fread(&aux->cliente->codCliente, sizeof(int), 1, tab);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), tab);
			fread(&aux->prox, sizeof(int), 1, tab);
			fread(&aux->status, sizeof(int), 1, tab);

			if(aux->status == 0){
				end = i*tamanhoRegistro();
				return end;
			}
		}

		return -1; //senão for encontrado espaço vazio não será possível inserir o registro. Retorna -1
	}
}

int acha_anterior_insercao(FILE* tab, int chave, int endereco){
	rewind(tab);

	if((h(chave)*tamanhoRegistro()) == endereco){
		return -1;
	}else{
		////SETANDO VARIÁVEIS, AUXILIARES E FLAGS////
		Registro* aux;
		aux = (Registro*)malloc(sizeof(Registro));
		aux->cliente = (Cliente*)malloc(sizeof(Cliente));
		int end = h(chave)*tamanhoRegistro();
		int endAnterior;
		////FIM DO SET DE VARIÁVEIS, AUXILIARES E FLAGS//// 

		do{ //prucurando pelo registro que aponta pra null
			endAnterior = end;
			fseek(tab, end, SEEK_SET);

			fread(&aux->cliente->codCliente, sizeof(int), 1, tab);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), tab);
			fread(&aux->prox, sizeof(int), 1, tab);
			fread(&aux->status, sizeof(int), 1, tab);

			end = aux->prox;

		}while(end > -1);

		return endAnterior; //retorna o endereço desse registro
	}	
	
}

int insere_table(FILE* tab, Registro* r){
	rewind(tab); //resetando ponteiros de leitura/escrita dos arquivos (precaução)
	//política do código: sempre após o uso de um arquivo: dar rewind(arquivo);

	////SETANDO VARIÁVEIS, AUXILIARES E FLAGS////
	Registro* aux;
	aux = (Registro*)malloc(sizeof(Registro));
	aux->cliente = (Cliente*)malloc(sizeof(Cliente));
	
	int end, endAnterior, endAux;

	////FIM DO SET DE VARIÁVEIS, AUXILIARES E FLAGS//// 

	//1º e grande passo: Inserção do cliente na tabela

	//1.1: buscar o elemento a ser inserido
	end = busca_table(tab, r->cliente->codCliente);

	//1.2: verificar os resultados da busca
	if(end == -1){ //não há espaço para inserção do arquivo
		printf("Erro: Não há espaço para inserção na tabela D:\n");
		return 0; //flag para falha
	}else{ //se a função retornou um endereço diferente de nulo, devemos verificar o conteúdo desse endereço
		rewind(tab);

		fseek(tab, end, SEEK_SET);
		fread(&aux->cliente->codCliente, sizeof(int), 1, tab);
		fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), tab);
		fread(&aux->prox, sizeof(int), 1, tab);
		fread(&aux->status, sizeof(int), 1, tab);

		if(aux->status == 1){ //endereço retornado pela função está ocupado
			printf("Erro: Registro já se encontra na lista!\n");
			return 0;
		}

		if(aux->status == 0){ //espaço livre
			rewind(tab);

			fseek(tab, end, SEEK_SET);

			fwrite(&r->cliente->codCliente, sizeof(int), 1, tab);
			fwrite(r->cliente->nome, sizeof(char), sizeof(r->cliente->nome), tab);
			fwrite(&r->prox, sizeof(int), 1, tab);
			fwrite(&r->status, sizeof(int), 1, tab);

			endAnterior = acha_anterior_insercao(tab, r->cliente->codCliente, end);

			rewind(tab);

			if(endAnterior != -1){
				fseek(tab, (endAnterior + tamanho()), SEEK_SET);
				endAux = end;
				fwrite(&endAux, sizeof(int), 1, tab); //atualizando o ->prox do anterior ao registro inserido
			}
		}
	}

	printf("\nRegistro inserido com sucesso! :3\n");

	free(aux->cliente);
	free(aux);

	return 1; //se correu tudo ok
}

int acha_anterior_remocao(FILE* tab, int chaveExcluido, int endExcluido){
	rewind(tab);

	//verificando se o item a ser excluído está em p
	if(h(chaveExcluido)*tamanhoRegistro() == endExcluido){
		return -1;
	}else{
		////SETANDO VARIÁVEIS, AUXILIARES E FLAGS////
		Registro* aux;
		aux = (Registro*)malloc(sizeof(Registro));
		aux->cliente = (Cliente*)malloc(sizeof(Cliente));
		int end = h(chaveExcluido)*tamanhoRegistro();
		int endAnterior;
		////FIM DO SET DE VARIÁVEIS, AUXILIARES E FLAGS//// 

		do{ //prucurando pelo registro que aponta pro excluído
			endAnterior = end;
			fseek(tab, end, SEEK_SET);

			fread(&aux->cliente->codCliente, sizeof(int), 1, tab);
			fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), tab);
			fread(&aux->prox, sizeof(int), 1, tab);
			fread(&aux->status, sizeof(int), 1, tab);

			end = aux->prox;

		}while(end != endExcluido);

		free(aux->cliente);
		free(aux);

		return endAnterior; //retorna o endereço desse registro	
	}
}

int remove_table(FILE* tab, int chave){
	printf("\nRemovendo registro de chave %d...\n", chave);

	rewind(tab);

	////SETANDO VARIÁVEIS, AUXILIARES E FLAGS////
	Registro* aux;
	aux = (Registro*)malloc(sizeof(Registro));
	aux->cliente = (Cliente*)malloc(sizeof(Cliente));

	int endRemocao, endAnterior, proxRemovido, novoStatus = 0;
	////FIM DO SET DE VARIÁVEIS, AUXILIARES E FLAGS//// 

	endRemocao = busca_table(tab, chave);

	if(endRemocao == -1){
		printf("Erro na remoção: Registro não encontrado!\n");
		return 0;
	}else{
		rewind(tab);

		fseek(tab, endRemocao, SEEK_SET);
		fread(&aux->cliente->codCliente, sizeof(int), 1, tab);
		fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), tab);
		fread(&aux->prox, sizeof(int), 1, tab);
		fread(&aux->status, sizeof(int), 1, tab);

		if(aux->status == 0){
			printf("Erro na remoção: Registro não encontrado!\n");
			return 0;
		}else{ //se o item a ser excluído for encontrado, o excluímos
			rewind(tab);

			fseek(tab, (endRemocao + tamanho()), SEEK_SET);
			fread(&proxRemovido, sizeof(int), 1, tab); //armazenando o prox
			fwrite(&novoStatus, sizeof(int), 1, tab); //excluindo o registro

			endAnterior = acha_anterior_remocao(tab, chave, endRemocao);

			if(endAnterior == -1){ //excluído estava em p (não tinha anterior)

				if(proxRemovido != -1){ //tinha proximo diferente de null
					rewind(tab);

					fseek(tab, proxRemovido, SEEK_SET);

					fread(&aux->cliente->codCliente, sizeof(int), 1, tab);
					fread(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), tab);
					fread(&aux->prox, sizeof(int), 1, tab);
					fread(&aux->status, sizeof(int), 1, tab);

					rewind(tab);

					fseek(tab, (proxRemovido + tamanho() + sizeof(int)), SEEK_SET);
					fwrite(&aux, sizeof(int), 1, tab); //removo o proximo de sua posição

					rewind(tab);

					fseek(tab, endRemocao, SEEK_SET);
					//sobrescrevo o excluído com o proximo
					fwrite(&aux->cliente->codCliente, sizeof(int), 1, tab);
					fwrite(aux->cliente->nome, sizeof(char), sizeof(aux->cliente->nome), tab);
					fwrite(&aux->prox, sizeof(int), 1, tab);
					fwrite(&aux->status, sizeof(int), 1, tab);
				}
			}else{
				rewind(tab);
				fseek(tab, (endAnterior + tamanho()), SEEK_SET);
				fwrite(&proxRemovido, sizeof(int), 1, tab); //atualizo ponteiro do anterior para apontar pro proximo do removido
			}
		}
	}

	printf("Registro removido com sucesso!\n");
	
	free(aux->cliente);
	free(aux);
	
	return 1;
}

