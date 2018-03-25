#include <stdlib.h>
#include <stdio.h>

#define MINCAPACITY 4

/*
==========================
==== FUNCOES DE PILHA ====
==========================
*/
typedef struct stack
{
	int topo;
	int *itens;
	int tamanho;
} stack;

/* Cria stack */
stack * createStack ()
{
	stack *novo = malloc(sizeof(stack));
	novo->topo = -1;
	novo->tamanho = MINCAPACITY;
	novo->itens = malloc(sizeof(int) * novo->tamanho);
	
	return novo;	
}

/* Libera Stack, retorna NULL */
stack * freeStack (stack *pilha)
{
	free(pilha->itens);
	pilha->itens = NULL;
	free(pilha);
	return NULL;
}

/* Imprime Stack */
void printStack (stack *pilha)
{
	printf("PILHA: ");

	if (!pilha)
		printf("pilha nao existe");
	
	else if (pilha->topo == -1)
		printf("pilha vazia");
	
	else
		for (int i = pilha->topo; i > -1; i--)
			printf("%d ", pilha->itens[i]);
	
	printf("\n");
}

/* Push data para pilha, retorna 1 se teve espaco, 0 se não */
int push (stack *pilha, int data)
{
	if (pilha->topo == pilha->tamanho-1)
		return 0;
	
	pilha->itens[++pilha->topo] = data;
	return 1;	
}

/* Pop para *elem, 1 se tinha elementos na pilha, 0 se não */
int pop (stack *pilha, int *elem)
{	
	if (!pilha || pilha->topo == -1)
		return 0;
	
	*elem = pilha->itens[pilha->topo--];
	return 1;
}

/*
=========================
==== FUNCOES DE FILA ====
=========================
*/
typedef struct queue
{
	int *itens;
	int tamanho;
	int inicio;
	int final;
} queue;

/* Cria fila */
queue * createQueue ()
{
	queue *novo = malloc(sizeof(queue));
	novo->tamanho = MINCAPACITY;
	novo->itens = malloc(sizeof(int) * novo->tamanho);
	novo->inicio = 0;
	novo->final = 0;
	
	return novo;
}

/* Libera fila e deixa NULL */
queue * freeQueue(queue *fila)
{
	free(fila->itens);
	fila->itens = NULL;
	free(fila);
	return NULL;
}

/* Imprime fila */
void printQueue (queue *fila)
{
	printf("FILA: ");
	
	if (!fila)
		printf("fila nao existe");
	
	else if (fila->inicio == fila->final)
		printf("fila vazia");
	
	else
		for (int i = fila->inicio; i%fila->tamanho < fila->final; i++)
			printf("%d ", fila->itens[i%fila->tamanho]);
	
	printf("\n");
}

/* Enfileira data */
int enfileira (queue *fila, int data)
{
	int novo_final = (fila->final+1)%fila->tamanho;
	
	if (novo_final == fila->inicio)
		return 0;
	
	fila->itens[fila->final] = data;
	fila->final = novo_final;
	return 1;
}

/* Desenfileira para *elem */
int desenfileira (queue *fila, int *elem)
{
	int novo_inicio = (fila->inicio+1)%fila->tamanho;
	
	if(fila->inicio == fila->final)
		return 0;
	
	*elem = fila->itens[fila->inicio];
	fila->inicio = novo_inicio;
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
	printStack(pilha);
	pilha = freeStack(pilha);
	printStack(pilha);
	
	printf("==== FILA ====\n");
	queue *fila = createQueue();
	
	printQueue(fila);
	for (int i = 1; i <= 4; i++) {
		enfileira(fila, 111*i);
		printQueue(fila);
	}
	
	for (int i = 1; i <= 4; i++) {
		desenfileira(fila, &elem);
		printf("desenfileira: %d\n", elem);
	}
	printQueue(fila);
	fila = freeQueue(fila);
	printQueue(fila);
	
	
	
	return 0;
}











