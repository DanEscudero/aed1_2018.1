#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	int data;
	struct node *next;
} node;

/* Imprime a lista */
void printList (node *lst)
{
	if (!lst) {
		printf("Lista: ");
		printf("lista vazia\n");
		return;
	}
	printf("Lista: ");
	for (node *aux = lst; aux; aux = aux->next)
		printf("%d ", aux->data);
	printf("\n");
}

/* Insere no final */
node * append (node *lst, int data)
{
	node *novo = malloc(sizeof(node));
	novo->data = data;
	novo->next = NULL;
	
	if (!lst)
		return novo;
	
	node *aux;
	for (aux = lst; aux->next; aux = aux->next);
	aux->next = novo;
	return lst;
}
/* Insere em ordem crescente na lista */
node * insereOrdenado (node *lst, int data)
{
	node *novo = malloc(sizeof(node));
	novo->data = data;
	novo->next = NULL;
	
	if (!lst)
		return novo;
	
	if (lst->data > data) {
		novo->next = lst;
		return novo;
	}
	
	node *aux = lst;
	while (aux->next && aux->next->data < data)
		aux = aux->next;
	
	novo->next = aux->next;
	aux->next = novo;
	return lst;
}

/* Insere depois do primeiro no com data == pos */
node * inserePosicao (node *lst, int data, int pos)
{
	node *novo = malloc(sizeof(node));
	novo->data = data;
	novo->next = NULL;
	
	if (!lst)
		return novo;
	
	node *aux;
	for (aux = lst; aux->next && aux->data != pos; aux = aux->next);
	novo->next = aux->next;
	aux->next = novo;
	return lst;
}

/* Remove o no que contem data */
void removeLista (node *lst, int data)
{
	if (!lst) return;
	node *aux;
	for (aux = lst; aux->next && aux->next->data != data; aux = aux->next);
	
	if (!aux->next) return;
	
	node *tmp = aux->next;
	aux->next = aux->next->next;
	free(tmp);
}

/* Libera Lista */
node * freeList (node *lst)
{
	node *aux = lst;
	while (aux) {
		lst = lst->next;
		free(aux);
		aux = lst;
	}
	return NULL;
}

int main ()
{
	node *lista = NULL;
	printList(lista);
	
	for (int i = 1; i <= 5; i++) {
		lista = append(lista, 111*i);		
		printList(lista);
	}
	
	lista = insereOrdenado (lista, 500);
	printList(lista);
	lista = insereOrdenado (lista, 250);
	printList(lista);
	lista = insereOrdenado (lista, 100);
	printList(lista);
	lista = insereOrdenado (lista, 600);
	printList(lista);
	
	for (int i = 1; i <= 5; i++) {
		removeLista (lista, i*111);
		printList(lista);
	}
	lista = freeList(lista);
	printList(lista);
	
	return 0;
}
