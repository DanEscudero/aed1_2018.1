#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define infinity INT_MAX

typedef struct Lista
{
    int nota;
    int ra;
    struct Lista *next;
} lista;

int flag = 1;

/* Troca os campos ra, nota do jeito mais idiota possivel */
void swapNode (lista *node1, lista *node2)
{
	int temp;
	char tempChar[51];
	
	temp = node1->ra;
	node1->ra = node2->ra;
	node2->ra = temp;
	
	temp = node1->nota;
	node1->nota = node2->nota;
	node2->nota = temp;
}

/* Cria nó */
lista *criar (int ra, int nota)
{
    lista *novo = malloc(sizeof(lista));
    novo->ra = ra;
    novo->nota = nota;
    novo->next = NULL;
    return novo;
}

/* Append recursivo */
lista *append(lista *x, int ra, int nota)
{  
    if (x == NULL)
		return criar(ra, nota);
	
    x->next = append(x->next, ra, nota);
	 
    return x;
}

/* Busca Recursivo */
int busca(lista *x, int ra, int C)
{
    if (x == NULL)
		return -1;
	
    if (x->ra == ra)
		return C;
	
    return busca(x->next, ra, ++C);
}

/* Imprime recursivo */
void imprimir (lista *x)
{
    if (x != NULL) {
        printf("[%d %d]\n", x->ra, x->nota);
        imprimir(x->next);
    }        
}

/* Libera e retorna NULL, recursivo */
lista *liberar (lista *x)
{
    if (!x)
		return NULL;
	
    if (x->next)
		x->next = liberar(x->next);
	
    free(x);
    return NULL;
}

int length (lista *lst)
{
	lista *aux = lst;
	int cont = 0;
	
	if (!aux)
		return cont;
	
	while (aux) {
		cont ++;
		aux = aux->next;
	}
	return cont;
}

/* Compara de acordo com flag e retorna:
0, se x==y
>0, se x>y
<0, se x<y */
int comparar (lista *x, lista *y)
{
	if (!x && !y)
		return 0;
	
	if (!x)
		return flag*(+1);
	
	if (!y)
		return flag*(-1);
	
	if (x && y)
		return flag*(x->ra - y->ra);
}

lista *access(lista *head, int pos)
{
	lista *aux = head;
	
	if (!aux) return NULL;
	
	for (int i = 0; i < pos; i++)
		if (aux->next) aux = aux->next;
	
	return aux;
}

void merge (lista **ptr_head, int inicio, int meio, int fim)
{
	printf("[MERGE]inicio: %d meio: %d fim: %d\n", inicio, meio, fim);
	lista *head = *ptr_head;
	lista *novo = NULL;

	int index1 = inicio;
	lista *aux1 = access(head, index1);
	
	int index2 = meio+1;
	lista *aux2 = access(head, index2);
	printf("aux1->ra: %d aux2->ra: %d\n", aux1->ra, aux2->ra);
	while (index1 <= meio && index2 <= fim) {
		if (aux1->ra < aux2->ra) {
			novo = append(novo, aux1->ra, aux1->nota);
			aux1 = aux1->next;
			index1++;
		}
		else {
			novo = append(novo, aux2->ra, aux2->nota);
			aux2 = aux2->next;
			index2++;
		}
	}
	printf("done main\n");
	while (index1 <= meio) {
		novo = append(novo, aux1->ra, aux1->nota);
		aux1 = aux1->next;
		index1++;
	}
	printf("done1\n");	
	while (index2 <= fim) {
		novo = append(novo, aux2->ra, aux2->nota);
		aux2 = aux2->next;
		index2++;
	}
	printf("done2\n");
	*ptr_head = novo;
}

void mergesort (lista **head, int inicio, int fim)
{
	if (inicio < fim) {
		int meio = (fim+inicio)/2;
		printf("[SORT]inicio: %d meio: %d fim: %d\n", inicio, meio, fim);
		mergesort(head, inicio, meio);
		mergesort(head, meio+1, fim);
		merge(head, inicio, meio, fim);
	}
}

int main() {
	int ra, nota, len = 0, input;
    lista *head = NULL;
	
	while (scanf("\n%d", &input), input) {
        switch (input) {
            case 1:
                scanf("%d %d", &ra, &nota);
                head = append(head, ra, nota);
				len++;
                break;
			
            case 2:
                printf("[LISTA]\n");
                imprimir(head);
                break;
            
            case 6:
				flag = +1;
				
                mergesort(&head, 0, len-1);
				
                printf("[LISTA]\n");
                imprimir(head);
                break;
			
            case 9:
				flag = -1;
				
                mergesort(&head, 0, len-1);
				
                printf("[LISTA]\n");
                imprimir(head);
                break;
			
			case 5:
			scanf("%d", &ra);
			printf("access: %d\n", (access(head, ra))->ra);
        }
    }
	
    head = liberar(head);
	
	/*lista *lst = NULL;
	lst = append(lst, 11, 11);
	lst = append(lst, 22, 22);
	lst = append(lst, 33, 33);
	lst = append(lst, 44, 44);
	
	printf("[LISTA]\n");
	imprimir(lst);
	int a = (access(lst, 4))->ra;
	printf("%d\n", a);*/
		
    return 0;
}








