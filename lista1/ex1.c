#include <stdio.h>
#include <stdlib.h>

void printVet (int *vet, int n)
{
	for (int i = 0; i < n; i++) 
		printf ("%d ", vet[i]);
	
	printf ("\n");
}

int printSubseq (int *seq, int size, int k)
{
	int i, j, consec;
	for (i = 0; i < size; i++) {
		consec = 1;
		for (j = 1; consec && j < k && i + j < size; j++) {
			if (*(seq+i+j-1) == *(seq+i+j) - 1) {
				if (j == 1)	printf("\n%d ", seq[i+j-1]);
				printf("%d ", seq[i+j]);
			}
			else consec = 0;
		}
		if (seq[i+j-1] != seq[i + j] - 1)
		i = i + j - 1;
	}
}

int main () {
	int n, k;
	int *seq = malloc(sizeof(int) * n);
	
	printf ("tamanho da sequencia: ");
	scanf("%d", &n);
	printf ("tamanho das subsequencias: ");
	scanf("%d", &k);
	
	for (int i = 0; i < n; i++)
		scanf("%d", &seq[i]);
	
	printSubseq (seq, n, k);
	printf ("\n");
	
    return 0;
}
