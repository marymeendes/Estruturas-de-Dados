#ifndef ARVOREVENCEDORES_H
#define ARVOREVENCEDORES_H

#include "fila.h"
#include "arvore.h"
#include "pilha.h"

Arv* arvVencedor(int* v, int nFiles); //nFiles é o número de arquivos simultâneos que o sistema suporta abrir, na função é usado nFiles-1 (Intercalção Ótima)

void intercalacao(Fila* filesName, int filesQtde, char* outFile, int nFilesOpen);//nFilesOpen = nFiles, outros parâmetros da função são os fornecidos pelo usuário

#endif