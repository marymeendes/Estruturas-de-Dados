/*
	Teste de mesa do QuickSort para a sequência: 6, 8, 2, 1, 7, 9, 3
	Autores: Mariana Mendes e Luis Antônio
*/

#include <stdio.h>
#include <stdlib.h>

void rapida (int n, int* v);

int main(){

	int vetor[] = {6, 8, 2, 1, 7, 9, 3};
	
	for(int i = 0; i < 7; i++){
		printf("%d ", vetor[i]);
	}
	printf("\n");

	rapida(7, vetor);
	
	for(int i = 0; i < 7; i++){
		printf("%d ", vetor[i]);
	}
	printf("\n");

	return 0;
}


void rapida (int n, int* v){
	int i;
	if (n > 1) {
		int x = v[0];
		int a = 1, b = n-1;
		printf("Pivô incial: %d\n", x);
		printf("a: %d\n", a);
		printf("b: %d\n", b);
		do {
			while (a < n && v[a] <= x) a++;
			/* teste a < n */
			while (v[b] > x) b--;
			/* nao testa */
			printf("Posicao com valor maior que o do pivô à esquerda (a): %d\n", a);
			printf("Posicao com valor menor que o do pivô à direita (b): %d\n", b);
			if (a < b) { /* faz troca */
				printf("Como a < b, troca, incrementa a e decrementa b.\n");
				int temp = v[a];
				v[a] = v[b];
				v[b] = temp;
				a++; b--;

				printf("Situação do vetor:\n");
				for(i = 0; i < n; i++){
					printf("%d ", v[i]);
				}
				printf("\n");
			}
		} while (a <= b);
		/* troca pivô */
		printf("Como a > b, troca pivô com o valor na posicao b.\n");
		v[0] = v[b];
		v[b] = x;
		/* ordena sub-vetores restantes */
		printf("Situação do vetor:\n\n");
		for(i = 0; i < n; i++){
			printf("%d ", v[i]);
		}
		printf("\n--------------------------------\n\n");

		if(b == 0){
			printf("Chamando a função rapida para o intervalo [0, %i]\n", b);
			printf("Vetor unitário e, portanto, já ordenado. Nenhuma ação necessária.\n");
		}else{
			printf("Chamando a função rapida para o intervalo [0, %i]\n", b-1);
		}
		rapida(b,v);

		printf("Chamando a função rapida para o intervalo [%d, %i]\n", a, n-1);
		rapida(n-a,&v[a]);
	}
}