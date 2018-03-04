#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	int data;
	struct node *next;
} node;

void printList (node *lst)
{
	for (node *curr = lst; curr; curr = curr->next)
		printf ("%d ", curr->data);
	printf ("\n");
}

/* Libera a lista iniciada por lst */
void freeList (node *lst)
{
	node *curr, *aux;
	for (curr = lst; curr; curr = curr->next) {
		aux = curr;
		free(aux);
	}
}

/* Cria nó com dado x seguinte a posição i	 	*
 * Assume que a lista tem tamanho i, no minimo 	*/
void insere (node *lst, int x, int i)
{
	node *curr;
	for (curr = lst; i; curr = curr->next, i--);
	node *novo = malloc(sizeof(node));
	
	novo->data = x;
	novo->next = curr->next;
	curr->next = novo;
}

/* Remove o elemento seguinte a posicao i */
void removeNode (node *lst, int i)
{
	node *curr;
	for (curr = lst; i; curr = curr->next, i--);
	
	node *aux = curr->next;
	curr->next = curr->next->next;
	free(aux);	
}

/* Reverte a lista */
/* Inverte os ponteiros ao inves de trocar valores */
void reverse(node** lst)
{
	node* prev = NULL, *curr = *lst, *next;	
    while (curr) {
        next = curr->next;  
        curr->next = prev;   
        prev = curr;
        curr = next;
    }
    *lst = prev;
}

/* Divide a lista. A que foi passada tem a primeira *
 * metade e a do retorno tem a segunda metade 		*/
node * split (node *lst)
{
	int len = 0;
	node *meio, *aux = malloc(sizeof(node));
	
	for (node *curr = lst; curr; curr = curr->next, len++);
	
	meio = lst;
	aux->next = lst;
		
	for (; len > 0; len-=2) {
		aux = aux->next;
		meio = meio->next;
	}
	
	aux->next = NULL;
	
	return meio;
}

void printCirc (node *lst)
{
	node *aux = lst;
	printf ("%d ", aux->data);	
	
	aux = lst->next;
	
	while (aux != lst) {
		printf ("%d ", aux->data);
		aux = aux->next;
	}
	
	printf ("\n");
}

void appendCirc(node *lst, int x)
{
	node *last = lst->next;
	
	while (last->next != lst)
		last = last->next;
	
	node *new = malloc(sizeof(node));
	new->data = x;
	new->next = last->next;
	
	last->next = new;	
}

void removeLastCirc(node *lst)
{
	node *penultimo = lst->next;
	while (penultimo->next->next != lst)
		penultimo = penultimo->next;
	
	node *temp = penultimo->next;
	penultimo->next = penultimo->next->next;
	free(temp);	
}

int main ()
{
	node *lst = malloc(sizeof(node));
	node *second = malloc(sizeof(node));
	node *third = malloc(sizeof(node));
	node *metade = malloc(sizeof(node));
	
	lst->data = 0;
	lst->next = second;
	
	second->data = 1;
	second->next = third;
	
	third->data = 2;
	third->next = NULL;
	
	printList(lst);
	
	printf("===\n");
	
	insere (lst, 99, 0);
	printList(lst);
	
	removeNode (lst, 1);
	printList(lst);
		
	reverse(&lst);
	printList(lst);

	printf("===\n");
	
	reverse(&lst);
	removeNode(lst, 0);
	insere (lst, 1, 0);
	insere (lst, 3, 2);
	insere (lst, 4, 3);
	insere (lst, 5, 4);
	printList(lst);

	printf("===\n");
	printf("metade:\n");
	metade = split(lst);
	printList(lst);
	printList(metade);
	
	freeList(lst);
	freeList(metade);
	
	printf("===\n");
	printf("Circular:\n");
	
	node *circular = malloc(sizeof(node));
	node *circular2 = malloc(sizeof(node));
	node *circular3 = malloc(sizeof(node));
	
	circular->data = 0;
	circular->next = circular2;
	circular2->data = 1;
	circular2->next = circular3;
	circular3->data = 2;
	circular3->next = circular;
	
	printCirc(circular);
	appendCirc(circular, 33);
	printCirc(circular);
	removeLastCirc(circular);
	printCirc(circular);
	
	return 0;
}








