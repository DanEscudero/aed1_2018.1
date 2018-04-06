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
	
	int line_counter = 1;
	
	if (!aux_lin || !aux_col) return 0;
	
	while (aux_lin->down && aux_lin->down->lin < y) {
		aux_lin = aux_lin->down;
		line_counter++;
	}
	//printf("lc: %d\n", line_counter);
	while (aux_col->right && aux_col->right->col < x) {
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

void insertElement (matriz *m, int lin, int col, int x)
{
	node *inserido = malloc(sizeof(node));
	inserido->data = x;
	inserido->lin = lin;
	inserido->col = col;
	inserido->down = NULL;
	inserido->right = NULL;
	
	node *aux_lin = m->lins;
	node *aux_col = m->cols;
	
	if (!aux_lin && !aux_col) {								//MATRIZ VAZIA
		node *novo_lin = malloc(sizeof(node));
		novo_lin->lin = lin;
		novo_lin->right = inserido;
		novo_lin->down = NULL;
		m->lins = novo_lin;
		
		node *novo_col = malloc(sizeof(node));
		novo_col->col = col;
		novo_col->right = NULL;
		novo_col->down = inserido;
		m->cols = novo_col;
	}
	
	else {													//MATRIZ JA TEM ALGUM ELEMENTO
		printf("1\n");
		while (aux_lin->down && aux_lin->down->lin < lin) {
			printf("w\n");
			aux_lin = aux_lin->down;
		}
		printf("2\n");
		if (aux_lin->lin != lin) {							//aux->lin é menor que lin
			printf("3\n");
			node *novo_lin = malloc(sizeof(node));
			novo_lin->lin = lin;
			novo_lin->right = inserido;						//erro pode estar aqui
			novo_lin->down = aux_lin->down;
			aux_lin->down = novo_lin;
			printf("4\n");
		}
		else {												//aux->lin é igual a lin	
			//ja existe a borda, insere o elemento
		}
		
		printf("5\n");
		while (aux_col->right && aux_col->right->col < col) {
			aux_col = aux_col->right;
			printf("w\n");
		}
		printf("6\n");
		if (aux_col->col != col) {							//aux->col é menor que col
			printf("7\n");
			node *novo_col = malloc(sizeof(node));
			novo_col->col = col;
			novo_col->down = inserido;
			novo_col->right = aux_col->right;
			aux_col->right = novo_col;
			printf("8\n");
		}
		else {												//aux->col é igual a col
			//ja existe a borda, insere o elemento
		}
		//NAO PODE FAZER SEPARADO AAAAAA	
	}
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
}

void multiplica (matriz *m, matriz *a, matriz *b)
{
	for (int i = 0; i < a->nLins; i++) {
		for (int j = 0; j < b->nCols; j++) {
			int soma = 0;
			
			for (int k = 0; k < b->nLins; k++)
				soma += acesso(a, i, k)*acesso(b, k, j);
			
			//insertElement(i, j, sum);
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
	
	char input;
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
					printf("MATRIZ MULTIMPLICADA\n");
					//matriz *mult = setupMatriz(ca, lb);
					//multiplica(mult, matrizA, matrizB);
					//printMatriz(mult);
				}
				break;
			case 'I':
			case 'i':
				scanf("%d %d %d", &lin, &col, &num);
				insertElement(matrizA, lin, col, num);
				printMatriz(matrizA);
				break;
		}
		scanf("%c", &input);
	}
	
	
	return 0;
}












