#include <stdlib.h>
#include <stdio.h>

void divide (int *vet, int **pos, int **neg, int n, int *len_pos, int *len_neg) {
	printf("divide\n");
	*pos = malloc(sizeof(int));
	*neg = malloc(sizeof(int));
	printf("aloca\n");
	
	for (int i = 0; i < n; i++) {
		printf("for\n");
		if (vet[i] > 0) {
			printf ("DONE +\n");
			
			*pos = realloc(*pos, sizeof(int) * ++(*len_pos));
			*pos[*(len_pos)-1] = vet[i];
		}
		else if (vet[i] < 0) {
			printf ("DONE -\n");
			
			*neg = realloc(*neg, sizeof(int) * ++(*len_neg));
			*neg[*(len_neg)-1] = vet[i];
			
			printf("fim if %d\n", *len_neg);
		}
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
	int *pos = malloc(sizeof(int));
	int *neg = malloc(sizeof(int));
	int len_pos = 0, len_neg = 0;
	
	for (int i = 0; i < 15; i++)
		vet [i] = i-7;
	
	printVet(vet, 15);
	printf ("===\n");
	
	divide(vet, &pos, &neg, 15, &len_pos, &len_neg);
	
	printVet(pos, len_pos);
	printf ("===\n");
	printVet(neg, len_neg);
	printf ("===\n");
	
	return 0;
}





