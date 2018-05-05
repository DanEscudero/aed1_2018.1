/*
Index:
	Insertion Sort
	Selection Sort
	Merge Sort
	Quick Sort
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define SIZE 8

void swap (int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void printVet (int *v, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", v[i]);
	printf("\n");
}

void randomize (int *v, int n)
{
	for (int i = n-1; i >= 0; i--) {
		int r = random()%n;
		swap(&v[i], &v[r]);
	}
}

void InsertionSort (int *v, int n)
{
	for (int i = 1; i < n; i++) {
		int j = i;
		while (j >= 0 && v[j] < v[--j])
			swap(&v[j], &v[j+1]);
	}
}

/* Retorna o index do menor elemento, considerando so o intervalo v[inicio..fim] */
int minInArray(int *v, int inicio, int fim)
{
	int menorIdx = inicio;
	
	for (int i = inicio; i < fim; i++)
		if (v[i] < v[menorIdx])
			menorIdx = i;
	
	return menorIdx;
}

void SelectionSort (int *v, int n)
{
	for (int i = 0; i < n; i++) {
		int minIndex = minInArray(v, i, n);
		swap(&v[i], &v[minIndex]);
	}
}

int *merge (int *v, int inicio, int meio, int fim)
{
	int com1 = inicio;
	int com2 = meio+1;
	int aux[fim - inicio + 1];
	
	int k = 0;
	while (com1 <= meio && com2 <= fim) {
		if (v[com1] <= v[com2])
			aux[k++] = v[com1++];
		else
			aux[k++] = v[com2++];
	}
	
	while (com1 <= meio)
		aux[k++] = v[com1++];
	
	while (com2 <= fim)
			aux[k++] = v[com2++];
	
	for (int i = inicio; i <= fim; i++) {
		v[i] = aux[i-inicio];
	}
}

void MergeSort (int *v, int inicio, int fim)
{
	if (inicio < fim) {
		int meio = inicio + (fim-inicio)/2;
		MergeSort(v, inicio, meio);
		MergeSort(v, meio+1, fim);
		merge(v, inicio, meio, fim);
	}
}

int part(int *v, int inicio, int fim)
{
	int pivo = fim;
	int j = inicio;
	for (int i = inicio; i < fim; i++)
		if (v[i] <= v[pivo])
			swap (&v[i], &v[j++]);
	swap (&v[pivo], &v[j]);
	return j;
}

void QuickSort (int *v, int inicio, int fim)
{
	if (inicio < fim) {
		int p = part(v, inicio, fim);
		QuickSort(v, inicio, p-1);
		QuickSort(v, p+1, fim);
	}
}

int main ()
{
	int v[] = {1, 3, 5, 2, 9, 7, 8, 0};
	printVet(v, SIZE);
	
	printf("Insertion Sort: ");	
	InsertionSort(v, SIZE);
	printVet(v, SIZE);
	randomize(v, SIZE);
	
	printf("Selection Sort: ");
	SelectionSort(v, SIZE);
	printVet(v, SIZE);
	randomize(v, SIZE);

	printf("Merge Sort: ");
	MergeSort(v, 0, SIZE-1);
	printVet(v, SIZE);
	randomize(v, SIZE);

	printf("Quick Sort: ");
	QuickSort(v, 0, SIZE-1);
	printVet(v, SIZE);
	randomize(v, SIZE);
	
	return 0;
	
}
