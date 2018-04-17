/* DUPLA:  11005716 Daniel Escudero
           -------- Caio Cesar      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista {
    char *nome;
    int nota;
    int ra;
    struct Lista *next;
} lista;

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

void printList(lista *lst)
{
    printf("LISTA:\n");
    lista *aux = lst;
    while (aux) {
        printf("[%d %s %d]\n", aux->ra, aux->nome, aux->nota);
        aux = aux->next;
    }
}

/* Libera lst e retorna NULL */
lista* liberar (lista *lst){
    if (lst) {
        lst->next = liberar(lst->next);
        free(lst);
    }
    return NULL;
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
        if ((param == 1 && aux->ra < min->ra) ||                //MINIMO POR RA
            (param == 2 && strcmp(aux->nome, min->nome) < 0))   //MINIMO POR NOME
                min = aux;
        aux = aux->next;
    }
    return min;
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
    liberar(lst);
    return sorted;
}

/* Recebe a lista e retorna ordenada */
/* Retorna a lisa ordenada, param: 1 = ra, 2 = nome */
lista *insertion_sort(lista *lst, int param, int *comparacoes)
{
    //...
}

/* Chama o devido algoritmo de ordenacao e retorna a lista ordenada */
/* 1: selection_sort; 2: insertion_sort */
lista *ordenar (lista *lst, int algoritmo, int param, int *comparacoes)
{
    if (algoritmo == 1)
        lst = selection_sort(lst, param, comparacoes);
    
    else if (algoritmo == 2)
        lst = insertion_sort(lst, param, comparacoes);
    
    return lst;
}

int main ()
{
    char input, *nome;
    int ra = 0, nota = 0, algoritmo = 0, parametro = 0, comparacoes = 0, busca = 0;
    lista *lst = NULL;
    
    scanf("%c\n", &input);
    
    while (input != 'P' && input != 'p') {
        switch(input) {
            case 'I':
            case 'i':
                scanf("%d %s %d", &ra, nome, &nota);
                lst = appendList(lst, nome, ra, nota);
                break;
            
            case 'O':
            case 'o':
                scanf("%d %d", &algoritmo, &parametro);
                lst = ordenar(lst, algoritmo, parametro, &comparacoes);
                printf("Comparacoes=%d\n", comparacoes);
                break;
            
            case 'B':
            case 'b':
                scanf("%d", &ra);
                busca = buscaLista_ra(lst, ra);
                printf("Pos=%d\n");
                break;
            
            case 'M':
            case 'm':
                printList(lst);
                break;
        }
        scanf("\n%c", &input);
    }
    
    
    liberar(lst);
    
    return 0;
}
