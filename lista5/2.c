#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int data;
	struct node *next;
} node;

typedef struct line {
	node *first;
	node *last;
} line;

/* Cria fila e devolve o ponteiro caso ocorra a alocação */
line * createLine ()
{
	line * novo = malloc(sizeof(line));
	if (!novo) return 0;
	
	novo->first = NULL;
	novo->last = NULL;
	
	return novo;
}

/* Libera Fila */
void freeLine (line *fila)
{
	node *aux;
	for (aux = fila->first; fila->first; aux = fila->first) {
		fila->first = fila->first->next;
		free(aux);
	}
	free (fila);
}

/* Enfileira data, retorna 1 se sucedido */
int enfileira (line *fila, int data)
{
	node *novo = malloc(sizeof(node));
	if(!novo) return 0;
	
	novo->data = data;
	if (fila->first == NULL && fila->last == NULL) { //FILA VAZIA
		fila->first = novo;
		fila->last = novo;
	}
	else { //FILA NAO VAZIA
		fila->last->next = novo;
		fila->last = novo;
	}
	
	return 1;
}

/* Desenfileira para *elem, retorna 1 se sucedido */
int desenfileira (line *fila, int *elem)
{
	if (!fila->first) return 0;
	node *aux = fila->first;
	fila->first = fila->first->next;
	*elem = aux->data;
	free(aux);
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
	
	a = desenfileira(fila, &b);
	printf("df: (%d) num: %d\n", a, b);
	a = desenfileira(fila, &b);
	printf("df: (%d) num: %d\n", a, b);
	a = desenfileira(fila, &b);
	printf("df: (%d) num: %d\n", a, b);
	
	freeLine(fila);
	 
	return 0;
}
