#include <stdlib.h>
#include <stdio.h>

typedef struct cell
{
	int i;
	int j;
	int data;
	struct cell *dir;
	struct cell *baixo;
} cell;

typedef struct borda
{
	int pos;
	struct borda *prox;
	struct cell *elem;
} borda;

void printMatriz(int *matriz, int m, int n)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			printf ("%d ", *(matriz + i*n + j));
		printf ("\n");
	}
}

void printMatrizT(int *matriz, int m, int n)
{
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++)
			printf ("%d ", *(matriz + i*n + j));
		printf ("\n");
	}
}

borda * MatrizParaLista (int *matriz, int m, int n)
{
	
}

int main () {
	int matriz[6][5] =
	{{0, 0, 0, 5, 0},
	 {0, 9, 0, 0, 0},
	 {4, 0, 0, 6, 0},
	 {0, 0, 0, 0, 0},
	 {0, 7, 0, 0, 0},
	 {0, 0, 0, 0, 0}};
	
	int *ptr = (int*)matriz;
	
	printMatriz(ptr, 6, 5);
	printf ("===\n");
	printMatrizT(ptr, 6, 5);
	printf ("===\n");	
	
	return 0;	
}













