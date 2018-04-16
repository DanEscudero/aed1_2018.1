#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista {
	char *nome;
	int nota;
	int ra;
	struct Lista *next;
} lista;

/* Libera lst e retorna NULL */
lista* liberar (lista *lst){
    if (lst) {
        lst->next = liberar(lst->next);
        free(lst);
    }
	return NULL;
}

/* Remove o no que contem ra */
lista *removeList (lista *lst, int ra)
{
	lista *aux = lst;
	if (aux->ra == ra) {
		free(aux);
		return lst->next;
	}
	while (aux->next) {
		if (aux->next->ra == ra) {
			lista *tmp = aux->next;
			
			if (!aux->next->next)
				aux->next = NULL;
			
			else
				aux->next = aux->next->next;
			
			free(tmp);
			return lst;
		}
		aux = aux->next;
	}
	return lst;
}

/* Retorna o indice de ra presente em lst, -1 caso nao encontre */
int buscaLista_ra (lista* lst, int ra)
{
	int i = 0;
	lista *aux = lst;
	while (aux) {
		if (aux->ra == ra)
			return i;
		i++;
		aux = aux->next;
	}
	return -1;
}

/* Retorna o menor no da lista lst, baseado em param */
/* param: 1 = ra, 2 = nome */
lista *minList (lista *lst, int param, int *comparacoes)
{
	if (!lst) return NULL;
	
	lista *aux = lst;
	lista *min = aux;
	
	while (aux->next) {
		(*comparacoes)++;
		if ((param == 1 && aux->ra < min->ra) || 				//MINIMO POR RA
			(param == 2 && strcmp(aux->nome, min->nome) < 0))	//MINIMO POR NOME
				min = aux;
		aux = aux->next;
	}
	return min;
}

/* Coloca no com nome e ra no fim da lista lst e retorna a nova lista */
lista* appendList (lista *lst, char *nome, int ra, int nota)
{	
	lista *novo = malloc(sizeof(lista));
	novo->nome = nome;
	novo->ra = ra;
	novo->nota = nota;
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

void printList(lista *lst)
{
	printf("LISTA:\n");
	lista *aux = lst;
	while (aux) {
		printf("Nome: %s ra: %d nota: %d\n", aux->nome, aux->ra, aux->nota);
		aux = aux->next;
	}
}

/* ta pronta ESTA MERDA */
/* Recebe uma lista a ser ordenada, um parametro e o ponteiro para comparacoes */
/* Retorna a lista ordenada */
/* param: 1 = ra, 2 = nome */
lista *selection_sort (lista *lst, int param, int *comparacoes)
{
	lista *sorted = NULL;
	lista *min = NULL;
	
	while (lst) {
		min = minList(lst, param, comparacoes);
		sorted = appendList(sorted, min->nome, min->ra, min->nota);
		lst = removeList(lst, min->ra);
	}
	lst = liberar(lst);
	return sorted;
}

int main ()
{
	lista *lst = NULL;
	char *teste = "aaa";
	int comparacoes;
	
	lst = appendList(lst, "aaa", 10, 10);
	lst = appendList(lst, "ccc", 18, 18);
	lst = appendList(lst, "bbb", 15, 15);
	lst = appendList(lst, "ddd", 60, 60);
	printList(lst);
	printf("\n");
	
	lst = selection_sort(lst, 1, &comparacoes);
	printf("\nSORTED ");
	printList(lst);
	printf("C=%d\n", comparacoes);
	
	liberar(lst);
	
	return 0;
}

















