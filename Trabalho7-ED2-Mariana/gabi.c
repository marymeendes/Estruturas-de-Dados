#include <stdio.h>
#include <stdlib.h>

int main(void){
	
	int* vetor = (int*)malloc(100*sizeof(int));
	int i;
	for(i=0; i<100; i++){
		vetor[i] = i;
		printf("%d\n", vetor[i]);
	}

	printf("\n%i\n", vetor);

	vetor = (int*)realloc(vetor, 100*sizeof(int));

	for(i=100; i<200; i++){
		vetor[i] = i;
		printf("%d\n", vetor[i]);
	}

	printf("%i\n", vetor);

	free(vetor);

	return 0;
}