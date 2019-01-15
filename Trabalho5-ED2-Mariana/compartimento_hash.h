#ifndef COMPARTIMENTO_HASH_H
#define COMPARTIMENTO_HASH_H

#include "lista.h"

int h(int x); //função de hashing

void set_table(FILE* tab);

int busca_table(FILE* tab, int chave);

int acha_anterior_insercao(FILE* tab, int chave, int endereco);

int insere_table(FILE* tab, Registro* r);

int acha_anterior_remocao(FILE* tab, int chaveExcluido, int endExcluido);

int remove_table(FILE* tab, int chave);

#endif


 