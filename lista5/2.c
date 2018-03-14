#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int data;
	struct node *next;
} node;

typedef struct line {
	node *list;
	int len;
} line;

/* Cria fila e devolve o ponteiro caso ocorra a alocação */
line * createLine ()
{
	line * novo = malloc(sizeof(line));
	if (!novo) return 0;
	
	novo->len = 0;
	
	return novo;
}

/* Libera Fila */
void freeLine (line *fila)
{
	node *aux;
	for (aux = fila->list; fila->list; aux = fila->list) {
		fila->list = fila->list->next;
		free(aux);
	}
	free (fila);
}

/* Imprime a Fila */
void printLine (line *fila)
{
	node *aux;
	printf("FILA: ");
	for (aux = fila->list; aux; aux = aux->next)
		printf ("%d  ", aux->data);
	printf("\n");
}

/* Enfileira data */
int enfileira (line *fila, int data)
{
	node *novo = malloc(sizeof(node));
	if(!novo) return 0;
	
	novo->data = data;
	novo->next = fila->list;
	fila->list = novo;
	
	return 1;
}

/* Retorna o ultimo elemento para *elem, retorna 1 se sucedido */
int desenfileira (line *fila, int *elem)
{
	if (!fila->list) return 0;
	node *aux;
	for(aux = fila->list; aux->next != NULL; aux = aux->next);
	*elem = aux->data;
	
	return 1;
}

int main ()
{
	line *fila = createLine();
	int a, b;
	enfileira(fila, 111);
	enfileira(fila, 222);
	enfileira(fila, 333);
	enfileira(fila, 444);
	enfileira(fila, 555);
	
	printLine(fila);
	
	a = desenfileira (fila, &b);
	printf("df: (%d) num: %d\n", a, b);
	a = desenfileira (fila, &b);
	printf("df: (%d) num: %d\n", a, b);
	a = desenfileira (fila, &b);
	printf("df: (%d) num: %d\n", a, b);
	
	return 0;
}
