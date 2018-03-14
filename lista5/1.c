#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
} node;

typedef struct stack {
	node *list;
} stack;

/* Aloca a lista, e retorna o ponteiro */
stack * createStack ()
{
	stack *novo = malloc(sizeof(stack));
	
	if (!novo) return 0;
	return novo;
}

/* Libera a memoria da pilha, e fica NULL */
void freeStack (stack *pilha)
{
	node *aux = pilha->list->next;
	while (aux) {
		aux = aux->next;
		free(pilha->list);
		pilha->list = aux;
	}
	pilha = NULL;
}

/* Imprime a lista */
void printStack (stack *pilha)
{
	node *aux;
	printf("PILHA:\t");
	for (aux = pilha->list; aux; aux = aux->next)
		printf("%d  ", aux->data);
	printf("\n");
	
}

/* Push data para a lista, 1 se bem sucedido */
int push (stack *pilha, int data)
{
	node *aux = malloc(sizeof(node));
	if (!aux) return 0;
	
	aux->data = data;
	aux->next = pilha->list;
	pilha->list = aux;
	
	return 1;
}

/* Pop o elemento da lista para *elem, retorna 1 se or sucedido */
int pop (stack *pilha, int *elem)
{
	if (!pilha->list) return 0;
	
	*elem = pilha->list->data;
	
	node *aux;
	aux = pilha->list;
	pilha->list = pilha->list->next;
	free(aux);
	return 1;
}

int main ()
{
	stack *pilha = createStack();
	int a, b;
	
	push (pilha, 111);
	push (pilha, 222);
	push (pilha, 333);
	push (pilha, 444);
	printStack(pilha);
	
	a = pop(pilha, &b);
	printf("pop: (%d) num: %d\n", a, b);
	printStack(pilha);
	
	printf("FREE STACK\n");
	freeStack(pilha);
	a = pop(pilha, &b);
	printf("pop: (%d) num: %d\n", a, b);
	
	return 0;
}

















