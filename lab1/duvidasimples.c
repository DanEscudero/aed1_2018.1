#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	int RA;
	int CodTopico;
	struct node *next;
} node;

void appendNode (node *lst, int RA, int CodTopico)
{
	node *curr;
	for (curr = lst; curr->next; curr = curr->next);
	
	node *new = malloc(sizeof(node));
	new->RA = RA;
	new->CodTopico = CodTopico;
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
		appendNode(duvidas, RA, CodTopico);		
		scanf ("%d %d", &RA, &CodTopico);
	}
	
	printListCabeca (duvidas);
	
	return 0;
}
