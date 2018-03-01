#include <stdlib.h>
#include <stdio.h>

int * insere (int *vet, int n, int x, int i) {
	if (i < n-1) vet[i] = x;
	else {
		vet = realloc(vet, sizeof(int) * (i+1));
		//for (int j = n; j <= i; j++) vet[j] = 0;
		vet[i] = x;
	}
	return vet;
}

void printVet (int *vet, int n) {
	for (int i = 0; i < n; i++)
		printf ("%d ", vet[i]);
	printf ("\n");
}

int main ()
{
	int *vet, i, x, len = 3;
	
	vet = malloc(sizeof(int) * len);
	
	for (int i = 0; i < len; i++)
		vet[i] = i;
	
	printf ("Elemento a ser inserido: ");
	scanf ("%d", &x);
	
	printf ("Posição: ");
	scanf ("%d", &i);
	
	printVet(vet, len);
	vet = insere(vet, len, x, i);
	printVet(vet, i > len-1 ? i+1 : len);
	
	return 0;
}
