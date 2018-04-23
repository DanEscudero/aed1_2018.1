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
	if (!x)
		return -1;
	
	if (!y)
		return +1;
	
	else
		return flag * (x->ra - y->ra);
}

lista *access(lista *head, int pos)
{
	lista *aux = head;
	
	if (!aux) return NULL;
	
	for (int i = 0; i <= pos; i++) {
		aux = aux->next;
	}
	return aux;
}

lista *merge (lista *head, int inicio, int meio, int fim)
{
	lista *novo = NULL;
	
	lista *aux1 = access(head, meio - inicio + 1);
	int index1 = meio - inicio + 1;
	
	lista *aux2 = access(head, fim - meio);
	int index2 = fim - meio;
	
	while (aux1 && aux2 && index1 <= meio && index2 <= fim) {
		if (comparar(aux1, aux2) >= 0) {
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
	
	return novo;
}

void mergesort (lista *head, int inicio, int fim)
{
	if (inicio < fim) {
		int meio = inicio + (fim-inicio)/2;
		
		mergesort(head, inicio, meio);
		mergesort(head, meio+1, fim);
		head = merge(head, inicio, meio, fim);
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
				
                mergesort(head, 0, len-1);
				
                printf("[LISTA]\n");
                imprimir(head);
                break;
			
            case '9':
				flag = -1;
				
                mergesort(head, 0, len-1);
				
                printf("[LISTA]\n");
                imprimir(head);
                break;
			
			case 5:
				printf("len: %d\n", len-1);
        }
    }
	
    head = liberar(head);
	
    return 0;
}








