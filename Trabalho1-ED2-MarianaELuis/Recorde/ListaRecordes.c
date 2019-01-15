/*
    Tarefa: Alterar o algoritmo de ordenação utilizado originalmente nesse código (bubblesort).
    Algoritmo de ordenação escolhido como substituto: quicksort.

    Autores da mudança: Mariana Mendes e Luis Antônio

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY 10
#define MAX_NOME 50

typedef struct
{
    char nome[MAX_NOME];
    int pontuacao;
} RECORDE;

typedef struct
{
    RECORDE vetor[MAX_ARRAY];
    int n;

} ARRAY;

RECORDE elemento(ARRAY *, int);
int tamanho(ARRAY *);
void insere(ARRAY *, RECORDE);

void remove_posicao(ARRAY *, int);
void imprime(ARRAY *);
void sort(ARRAY *);
void bubble_sort(RECORDE *, int);
void rapida (RECORDE *, int); //função de implementação do quicksort

int main(int argc, char *argv [])
{
    char *nome_arquivo = "recordes3.dat"; //novo arquivo do recorde
    FILE *p_arquivo;

    ARRAY array;
    array.n = 0;

    if((p_arquivo = fopen(nome_arquivo, "r")) != NULL)
    {
        fread(&array, sizeof(ARRAY), 1, p_arquivo);
        fclose(p_arquivo);
    }

    imprime(&array);

    RECORDE rec1;
    
    printf("Nome do Recordista:");
    fgets(rec1.nome, MAX_NOME, stdin);

    rec1.nome[strlen(rec1.nome) - 1] = '\0';

    printf("Pontuação:");
    scanf("%d", &rec1.pontuacao);

    insere(&array, rec1);
    
    imprime(&array);

    if((p_arquivo = fopen(nome_arquivo, "w")) == NULL)
    {
        perror("fopen:");
        return 1;
    }

    fwrite(&array, sizeof(ARRAY), 1, p_arquivo);
    fclose(p_arquivo);

    return 0;
}

RECORDE elemento(ARRAY *array, int posicao)
{
	return array->vetor[posicao];
}

int tamanho(ARRAY *array)
{
	return array->n;
}

void insere(ARRAY *array, RECORDE recorde)
{
    if(tamanho(array) < MAX_ARRAY)
    {
        array->vetor[tamanho(array)] = recorde;
        array->n += 1;
    }
    else
    {
        RECORDE menor_recorde;
        menor_recorde = elemento(array, MAX_ARRAY - 1);
        
        if(menor_recorde.pontuacao >= recorde.pontuacao)
        {
            return;
        }
        else
        {
            remove_posicao(array, MAX_ARRAY - 1);
            insere(array, recorde);
            return;
        }
    }
    
    sort(array);
}

void remove_posicao(ARRAY *array, int posicao)
{
	if(tamanho(array) == 0)
	{
		return;
	}
	else if(tamanho(array) == 1)
	{
		array->n -= 1;
		return;
	}
	else
	{
		array->n -= 1;
		array->vetor[posicao] = array->vetor[tamanho(array)];
	}
    
    sort(array);
}

void imprime(ARRAY *array)
{
	int i;
    RECORDE recorde;

    printf("------------------------------\n");
	printf("Recordes:\n");

	for(i = 0; i < tamanho(array); i++)
	{
        recorde = elemento(array, i);
        printf("%d - %d :: %s \n", i+1, recorde.pontuacao, recorde.nome);
	}

	printf("------------------------------\n");
}

///////////////////////////////MUDANÇAS NO CÓDIGO AQUI/////////////////////////////////

void sort(ARRAY *array)
{
	rapida(array->vetor, array->n);
}

void bubble_sort(RECORDE list[], int n)
{
	int i, j;
    RECORDE swap;

	for(i = 0 ; i < ( n - 1 ); i++)
	{
		for(j = 0 ; j < n - i - 1; j++)
		{
			if(list[j].pontuacao < list[j+1].pontuacao)
			{ 
				swap = list[j];
				list[j] = list[j+1];
				list[j+1] = swap;
			}
		}
	}
}

//alterações na função rapida para implementar o quicksort como algoritmo de ordenação do recorde

void rapida (RECORDE v[], int n){
    RECORDE temp;

    if (n > 1) {
        RECORDE x = v[0];
        int a = 1, b = n-1;
        
        do {
            while (a < n && v[a].pontuacao > x.pontuacao) a++; //a vai do início ao fim do vetor procurando elementos menores que o pivô
            /* teste a < n */
            while (b > 0 && v[b].pontuacao <= x.pontuacao) b--; //b vai do fim ao início do vetor procurando elementos maiores que o pivô, 
            /* nao testa */                                     //necessário, portanto, verificar se ele b chegou no inicio do vetor
            
            if (a < b) { /* faz troca */
                
                temp = v[a];
                v[a] = v[b];
                v[b] = temp;
                a++; b--;
            }
        } while (a <= b);
        /* troca pivô */
        v[0] = v[b];
        v[b] = x;
        /* ordena sub-vetores restantes */
        rapida(v, b);
        rapida(&v[a], n-a);
    }
}