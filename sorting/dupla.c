#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista {
	int RA;
	char *nome;
	struct Lista *next;
} lista;

/* param: 1 = ra, 2 = nome */
lista *min_List (lista *lst, int param)
{
	if (!lst) return NULL;
	lista *aux = lst;
	lista *min;
	if (param == 1) {
		min = aux;
		while (aux) {
			if (aux->RA < min->RA) min = aux;
			aux = aux->next;
		}
	}
	return min;
}

/* param: 1 = ra, 2 = nome */
/*int *selection_sort (lista *lst, int param)
{
	int comparacoes = 0;
	lista *aux = lst;
	while (aux) {
		aux = aux->next;
	}
}*/

/* coloca no com nome e ra no fim da lista lst e retorna */
lista* appendList (lista *lst, char *nome, int ra)
{
	lista *novo = malloc(sizeof(lista));
	novo->nome = nome;
	novo->RA = ra;
	novo->next = NULL;
	
	if (!lst) return novo;
	else {
		lista *aux = lst;
		while (aux->next)
			aux = aux->next;
		aux->next = novo;
	}
	return lst;
}

/*int selection_sort (int *v, int n)
{
	int comparacoes = 0;
	for (int i = 0; i < n-1; i++) {
		int min = i;
		for (int j = i+1; j < n; j++) {
			if (v[min] > v[j])
				min = j;
			comparacoes++;
		}
		swap(&v[i], &v[min]);
	}
	return comparacoes;
}*/

void printList(lista *lst)
{
	lista *aux = lst;
	while (aux) {
		printf("Nome: %s RA: %d\n", aux->nome, aux->RA);
		aux = aux->next;
	}
}

lista* liberar (lista *lst){
    if (lst) {
        lst->next = liberar(lst->next);
        free(lst);
    }
	return NULL;
}

int buscaList (lista* lst, int ra)
{
	int i = 0;
	lista *aux = lst;
	while (aux) {
		i++;
		printf("aux->ra: %d\n", aux->RA);
		if (aux->RA == ra)
			return i;
		aux = aux->next;
	}
	return -1;
}

int main ()
{
	lista *lst = NULL;
	char *teste = "AAA";
	
	for (int i = 0; i < 5; i++) {
		lst = appendList(lst, teste, 111*i);
	}
	printList(lst);
	lst = liberar(lst);
	printList(lst);
	
	printf("%d\n", buscaList(lst, 333));
	
	return 0;
}

















