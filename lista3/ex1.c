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

/* Cria nó com dado x depois da posição i	 	*
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

/* Remove o elemento depois de i */
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
	
	insere (lst, 111, 0);
	printList(lst);
	
	removeNode (lst, 1);
	printList(lst);
	
	reverse(&lst);
	printList(lst);

	reverse(&lst);	
	removeNode(lst, 0);
	insere (lst, 1, 0);
	insere (lst, 3, 2);
	insere (lst, 4, 3);
	insere (lst, 5, 4);
	printList(lst);
	
	printf ("metade:\n");
	metade = split(lst);
	printList(lst);
	printList(metade);	
	
	return 0;
}
