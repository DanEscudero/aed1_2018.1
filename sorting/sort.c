#include <stdlib.h>
#include <stdio.h>

void swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void shuffle (int *v, int n)
{
	int r, aux; 
	for (int i = n-1; i > 0; i--) {
		int r = (rand() % (i+1));
		swap (&v[i], &v[r]);
	}
}

int selection_sort (int *v, int n)
{
	int comparacoes = 0;
	for (int i = 0; i < n-1; i++) {
		int min = i;
		for (int j = i+1; j < n; j++) {
			if (v[min] > v[j])
				min = j;
			comparacoes++;
		}
		swap(&v[i], &v[min]);
	}
	return comparacoes;
}

int insertion_sort (int *v, int n)
{
	int comparacoes = 0;
	for (int i = 1; i < n; i++) {
		int j = i-1;
		int aux = v[i];
		while (j >= 0 && v[j] > aux) {
			comparacoes++;
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = aux;
	}
	return comparacoes;
}

void printVet (int *v, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", v[i]);
	printf("\n");
}

#define TAM 10

int main ()
{
	int vet[TAM];
	for (int i = 0; i < TAM; i++)
		vet[i] = i;
	printVet(vet, TAM);
	
	printf("selection sort:\n");
	shuffle(vet, TAM);
	printVet(vet, TAM);
	selection_sort(vet, TAM);
	printVet(vet, TAM);
	
	printf("insertion sort:\n");
	shuffle(vet, TAM);
	printVet(vet, TAM);
	insertion_sort(vet, TAM);
	printVet(vet, TAM);
	
	return 0;
}











