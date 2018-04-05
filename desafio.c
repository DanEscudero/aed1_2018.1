#include <stdio.h>
#include <stdlib.h>

/* Celula, tem o indice e os valores, e aponta para as proximas celulas */
typedef struct node
{
	int data;
	int lin;
	int col;
	struct node *down;
	struct node *right;
} node;

/* Borda, aponta para a celula e tem o indice */
typedef struct border
{
	int index;
	struct border *next;
	node *cell;
} border;

/* Matriz, aponta para as bordas */
typedef struct matriz
{
	border *lins;
	border *cols;
} matriz;

void printBorders(matriz *m)
{
	border *aux = m->lins;
	printf("lins: ");
	while (aux) {
		printf("%d ", aux->index);
		aux = aux->next;
	}
	
	aux = m->cols;
	printf("\ncols: ");
	while (aux) {
		printf("%d ", aux->index);
		aux = aux->next;
	}
	printf("\n");
}

/* INUTIL */
/* Insere os nos de borda, com os paramtros (-1, NULL, NULL) */
border * insertBorder (border *inicio)
{
	border *novo = malloc(sizeof(border));
	novo->index = -1;
	novo->next = NULL;
	novo->cell = NULL;
	
	if (!inicio)
		return novo;
	
	border *aux = inicio;
	while (aux->next)
		aux = aux->next;
	
	aux->next = novo;
	return inicio;
}

/* Verifica se x pertence a lista inicio (ordenada) 			*
 * Retorna NULL caso nao pertenca, e o endereco caso pertenca 	*/
border *pertence(border * inicio, int x)
{
	border *aux = inicio
	while (aux && aux->index <= x) {
		if (x == aux->indice) return aux;
		aux = aux->next;
	}
	return NULL;
}

void insertElement (matriz* m, int lin, int col, int x)
{
	cell *novo = malloc(sizeof(cell));
	novo->data = x;
	novo->lin = lin;
	novo->col = col;
	novo->down = NULL;
	novo->right = NULL;
	
	border *pertence_lin = pertence(m->lins, lin);
	border *pertence_col = pertence(m->cols, col);
	
	//Checar se ja existe elemento naquela posicao
	if (pertence_lin && pertence_col) {
		//atualiza
	}
	//Nao existe linha e nem cluna do elemento
	else if (!pertence_lin && !pertence_col) {
		//cria lin e col
	}
	else if (pertence_lin && !pertence_col) {
		//cria col
	}
	else if (!pertence_lin && pertence_col) {
		//cria lin
	}
}

int main ()
{
	matriz *matrizA = malloc(sizeof(matriz));
	matriz *matrizB = malloc(sizeof(matriz));
	
	if (!(matrizA && matrizB)) return 1;
	
	matrizA->lins = NULL;
	matrizA->cols = NULL;

	matrizB->lins = NULL;
	matrizB->cols = NULL;
	
	//input dos parameetros das matrizes
	int la, ca, na, lb, cb, nb;
	scanf("%d %d %d %d %d %d", &la, &ca, &na, &lb, &cb, &nb);
	
	//input de cada elemento
	int lin, col, num;
	
	/*printf("INSERINDO BORDAS\n");
	for (int i = 0; i < la; i++)
		matrizA->lins = insertBorder(matrizA->lins);
	
	for (int i = 0; i < ca; i++)
		matrizA->cols = insertBorder(matrizA->cols);

	for (int i = 0; i < lb; i++)
		matrizB->lins = insertBorder(matrizB->lins);
	
	for (int i = 0; i < cb; i++)
		matrizB->cols = insertBorder(matrizB->cols);
	printf("BORDAS INSERIDAS\n");*/
	
	printBorders(matrizA);
	printBorders(matrizB);
	
	printf("INSERINDO EM A\n")
	for (int i = 0; i < na; i++) {
		scanf("%d %d %d", &lin, &col, &num);
		insertElement(matrizA, lin, col, num);
	}
	
	printf("INSERINDO EM B\n")
	for (int i = 0; i < na; i++) {
		scanf("%d %d %d", &lin, &col, &num);
		insertElement(matrizB, lin, col, num);
	}
	
	return 0;
}












