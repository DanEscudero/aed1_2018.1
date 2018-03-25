#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	int data;
	struct node *next;
} node;

/*
====================
= FUNCOES DE PILHA =
====================
*/
typedef struct stack
{
	node *top;
} stack;

/* Cria stack */
stack * createStack ()
{
	stack *novo = malloc(sizeof(stack));
	return novo;
}

/* Libera stack, e deixa com NULL */
void freeStack (stack *pilha)
{
	node *aux = pilha->top;
	while (aux) {
		aux = aux->next;
		free(pilha->top);
		pilha->top = aux;
	}
	pilha = NULL;
}

/* Imprime stack */
void printStack (stack *pilha)
{
	printf("PILHA: ");
	if (!pilha || !pilha->top)
		printf("pilha vazia");
	else {
		for (node *aux = pilha->top; aux; aux = aux->next)
			printf("%d ", aux->data);
	}
	printf("\n");
}

/* Push para a pilha */
void push (stack *pilha, int data)
{
	node *aux = malloc(sizeof(node));
	aux->data = data;
	aux->next = pilha->top;
	pilha->top = aux;	
}

/* Pop para *elem */
int pop (stack *pilha, int *elem)
{
	if (!pilha->top) return 0;
	*elem = pilha->top->data;
	pilha->top = pilha->top->next;
	return 1;
}

/*
===================
= FUNCOES DE FILA =
===================
*/
typedef struct queue
{
	node *inicio;
	node *final;
} queue;

/* Cria fila */
queue * createQueue ()
{
	queue *novo = malloc(sizeof(queue));
	novo->inicio = NULL;
	novo->final = NULL;
	
	return novo;
}

/* Libera fila e deixa como NULL */
void freeQueue (queue* fila)
{
	node *aux = fila->inicio;
	while (aux) {
		aux = aux->next;
		free (fila->inicio);
		fila->inicio = aux;
	}
	fila->inicio = NULL;
	fila->final = NULL;
}

/* Imprime a fila */
void printQueue (queue *fila)
{
	printf("FILA: ");
	
	if (!fila->inicio && !fila->final) {
		printf("fila vazia");
	}
	
	else {
		node *aux = fila->inicio;
		while (aux) {
			printf("%d ", aux->data);
			aux = aux->next;
		}
	}
	
	printf("\n");
}

/* Enfileira data */
void enfileira (queue *fila, int data)
{
	node *novo = malloc(sizeof(node));
	novo->data = data;
	novo->next = NULL;
	
	if (!fila->final && !fila->final) {
		fila->inicio = novo;
		fila->final = novo;
	}
	else {
		fila->final->next = novo;
		fila->final = novo;
	}
}

/* Desenfileira para *elem */
int desenfileira (queue *fila, int *elem)
{
	node *aux = fila->inicio;
	if (!aux) {
		fila->final = fila->inicio;
		return 0;
	}
	*elem = aux->data;
	fila->inicio = fila->inicio->next;
	free(aux);
	return 1;
}

int main ()
{
	int elem;
	
	printf("==== PILHA ====\n");
	stack *pilha = createStack();
	printStack(pilha);
	
	for (int i = 1; i <= 5; i++) {
		push(pilha, 111*i);
		printStack(pilha);
	}

	for (int i = 1; i <= 5; i++) {
		pop(pilha, &elem);
		printf("pop: %d\n", elem);	
	}
	
	freeStack(pilha);
	printStack(pilha);
	
	printf("\n==== FILA ====\n");
	queue *fila = createQueue();
	printQueue(fila);
	
	for (int i = 1; i <= 5; i++) {
		enfileira(fila, i*111);
		printQueue(fila);
	}
	
	for (int i = 1; i <= 5; i++) {
		desenfileira(fila, &elem);
		printf("desenfileira: %d\n", elem);
	}
	
	freeQueue(fila);
	printQueue(fila);
	
	return 0;
}















