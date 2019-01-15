#ifndef COMPARTIMENTO_HASH_H
#define COMPARTIMENTO_HASH_H

#include "lista.h"

int h(int x); //função de hashing

void set_table(FILE* tabHash, int tabSize);

int insere_table(FILE* tab, FILE* cli, Registro* r);

void remove_table(FILE* tab, FILE* cli, int chave);

Registro* busca_table(FILE* tab, FILE* cli, int chave);

#endif


 