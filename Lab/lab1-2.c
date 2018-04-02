#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	int RA;
	int CodTopico;
	struct node *next;
} node;

void insert_group_Node (node *lst, int RA, int CodTopico)
{
	node *curr = lst;
	/* Anda até chegar em RA igual ou acabar a lista */
	while (curr->next != NULL && curr->RA != RA)
		curr = curr->next;
	
	/* Se chegar em RA igual, chega até o fim destes, ou ate acabar a lista */
	while (curr->next && curr->next->RA == RA) {
		curr = curr->next;
	}
	
	node *new = malloc(sizeof(node));
	new->RA = RA;
	new->CodTopico = CodTopico;
	
	new->next = curr->next;
	curr->next = new;
}

/* Imprime a lista a partir do segundo nó */
void printListCabeca (node* lst)
{
	for (node *curr = lst->next; curr; curr = curr->next)
		printf ("%d %d\n", curr->RA, curr->CodTopico);
}

int main () {
	int RA, CodTopico;
	node *duvidas = malloc(sizeof(node));
	
	scanf ("%d %d", &RA, &CodTopico);
	
	while (RA != -1 && CodTopico != -1) {
		insert_group_Node(duvidas, RA, CodTopico);		
		scanf ("%d %d", &RA, &CodTopico);
	}
	
	printListCabeca (duvidas);
	
	return 0;
}
