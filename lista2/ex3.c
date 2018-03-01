#include <stdlib.h>
#include <stdio.h>

void divide (int *vet, int *pos, int *neg, int n, int *len_pos, int *len_neg) {
	pos = malloc(sizeof(int));
	neg = malloc(sizeof(int));
	for (int i = 0; i < n; i++) {
		if (vet[i] > 0) {
			//printf ("DONE %d\n", i);
			pos = realloc(pos, sizeof(int) * ++(*len_pos));
			pos[*(len_pos)-1] = vet[i];
		}
		else if (vet[i] < 0) {
			neg = realloc(neg, sizeof(int) * ++(*len_neg));
			neg[*(len_neg)-1] = vet[i];
		}
		//vet = realloc(vet, sizeof(int) * --n);
	}
	free(vet);
}

void printVet (int *vet, int n) {
	for (int i = 0; i < n; i++)
		printf ("%d | ", vet[i]);
	printf ("\n");
}

int main ()
{
	int *vet = malloc (sizeof(int) * 15);
	int *pos, *neg;
	int len_pos = 0, len_neg = 0;
	
	for (int i = 0; i < 15; i++)
		vet [i] = i-7;
	
	printVet(vet, 15);
	printf ("===\n");
	
	divide(vet, pos, neg, 15, &len_pos, &len_neg);
	
	printVet(pos, len_pos);
	printf ("===\n");
	printVet(neg, len_neg);
	printf ("===\n");
	
	return 0;
}





