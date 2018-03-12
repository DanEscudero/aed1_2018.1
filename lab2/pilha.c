 #include <stdlib.h>
#include <stdio.h>

#define MINCAPACITY 15

typedef struct arrStack
{
	int top;
	int capacity;
	double *data;
} arrStack;

arrStack* criaPilha ()
{
	arrStack *novo = malloc(sizeof(arrStack));
	if (!novo) return NULL;
	
	novo->data = malloc(MINCAPACITY * sizeof(int));
	if (!novo->data) {
		free(novo);
		return NULL;
	}
	novo->top = 0;
	novo->capacity = MINCAPACITY;
	return novo;
}

int isEmpty (arrStack *pilha)
{
	return !(pilha && pilha->top);
}

int isFull (arrStack *pilha)
{
	return pilha->top == pilha->capacity;
}

/* Empilha, retorna o novo tamanho, e 0 se cheio */
int push (arrStack *pilha, int elem)
{
	if (isFull(pilha)) return 0;
	
	pilha->data[pilha->top] = elem;
	return ++pilha->top;
}

/* Desempilha, retorna o novo tamanho, e -1 se vazio. O elemento fica em *elem */
int pop (arrStack *pilha, int *elem)
{
	if (isEmpty(pilha)) return -1;
	
	*elem = pilha->data[--pilha->top];
	return pilha->top;
}

int main ()
{
	
	return 0;
}


















