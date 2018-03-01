#include <stdlib.h>
#include <stdio.h>

void swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int * inverte (int *vet, int n)
{
	for (int i = 0; i < n/2; i++)
		swap(&vet[i], &vet[n-1-i]);
	
	return vet;
}

void printVet (int *vet, int n) {
	for (int i = 0; i < n; i++)
		printf ("%d ", vet[i]);
	printf ("\n");
}

int main ()
{
	int n;
	scanf ("%d", &n);
	
	int *vet = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf ("%d", &vet[i]);

	printVet(vet, n);	
	vet = inverte(vet, n);
	printVet(vet, n);
	
	return 0;
}
