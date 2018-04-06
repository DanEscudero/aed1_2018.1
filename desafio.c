#include <stdio.h>
#include <stdlib.h>

/* Celula tem o indice e os valores e aponta para as proximas celulas */
typedef struct node
{
	int data;
	int lin;
	int col;
	struct node *down;
	struct node *right;
} node;

/* Matriz aponta para as celulas de borda */
typedef struct matriz
{
	int nLins;
	int nCols;
	node *lins;
	node *cols;
} matriz;

/* Seta a matriz com l, c e os pointeiros NULL */
matriz *setupMatriz(int l, int c)
{
	matriz *m = malloc(sizeof(matriz));
	
	if (!m) return m;
	
	m->nLins = l;
	m->nCols = c;
	m->lins = NULL;
	m->cols = NULL;
	
	return m;
}

/* Acessa a posicao (x,y) de m e retorna o elemento caso exista, 0 caso nao exista */
int acesso (matriz *m, int y, int x)
{
	node *aux_lin = m->lins;
	node *aux_col = m->cols;
	
	int line_counter = 0;
	
	if (!aux_lin || !aux_col) return 0;
	
	while (aux_lin->lin < y && aux_lin->down) {
		aux_lin = aux_lin->down;
		line_counter++;
	}
	
	while (aux_col->col < x && aux_col->right) {
		aux_col = aux_col->right;
	}
	
	if (aux_col->col == x && aux_lin->lin == y) {
		for (int i = 0; i < line_counter; i++) {
			aux_col = aux_col->down;
		}
		return aux_col->data;
	}
	else
		return 0;
}



/* Imprime a m formatada */
void printMatriz (matriz *m)
{
	for (int i = 0; i < m->nLins; i++) {
		printf("[");
		
		for (int j = 0; j < m->nCols; j++)
			printf("%d ", acesso(m, i, j));
		
		printf("]\n");
	}
	printf("\n");
}

void multiplica (matriz *m, matriz *a, matriz *b)
{
	for (int i = 0; i < a->nLins; i++) {
		for (int j = 0; j < b->nCols; j++) {
			int soma = 0;
			
			for (int k = 0; k < b->nLins; k++)
				soma += acesso(a, i, k)*acesso(b, k, j);
			
			//insertElement(sum, i, j);
		}
	}
}

int main ()
{
	//input dos parametros das matrizes
	int la, ca, na, lb, cb, nb;
	scanf("%d %d %d %d %d %d", &la, &ca, &na, &lb, &cb, &nb);
	
	//Setup das matrizes
	matriz *matrizA = setupMatriz(la, ca);
	matriz *matrizB = setupMatriz(lb, cb);
	
	if (!(matrizA && matrizB)) return 1;
		
	
	//input de elementos
	int lin, col, num;
	
	/*for (int i = 0; i < na; i++) {
		scanf("%d %d %d", &lin, &col, &num);
		insertElement(matrizA, lin, col, num);
	}
	
	for (int i = 0; i < na; i++) {
		scanf("%d %d %d", &lin, &col, &num);
		insertElement(matrizB, lin, col, num);
	}*/
	
	printf("MATRIZ A:\n");
	printMatriz(matrizA);
	printf("MATRIZ B:\n");
	printMatriz(matrizB);
	
	
	/*char input;
	scanf("%c", &input);
	while (!(input == 's' || input == 'S')) {
		switch (input) {
			case 'A':
			case 'a':
				printMatriz(matrizA);
				break;
			case 'B':
			case 'b':
				printMatriz(matrizB);
				break;
			case 'M':
			case 'm':
				if (ca != lb) printf("ERRO\n");
				else {
					matriz *mult = setupMatriz(ca, lb);
					multiplica(mult, matrizA, matrizB);
					printMatriz(mult);
				}
				break;
		}
		scanf("%c", &input);
	}*/
	
	
	return 0;
}












