/*
	Bryan Valeriano: 21061215 
	Daniel Escudero: 11005716
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista {
    char modelo[51];
    int velocidade;
    double eficiencia;
	int capacidade;
	int entrega;
    struct Lista *next;
} lista;

int modoDeComparacao = 0;
/*
Modo:
	10 - Modelo Crescente
	11 - Modelo Decrescente
	20 - Capacidade Crescente
	21 - Capacidade Decrescente
	50 - Velocidade Decrescente -> Eficiencia Decrescente
	51 - Velocidade Decrescente -> Eficiencia Crescente
	60 - Entrega Crescente
	61 - Entrega Decrescente

Retorno:
	>0 -> x > y
	<0 -> x < y
*/
int compara (lista *x, lista *y)
{
	switch (modoDeComparacao) {
		case 10:
			return strcmp(x->modelo, y->modelo);
		case 11:
			return strcmp(y->modelo, x->modelo);
		
		case 20:
			return x->capacidade - y->capacidade;
		case 21:
			return y->capacidade - x->capacidade;
		
		case 50:
			if (x->velocidade != y->velocidade)
				return y->velocidade - x->velocidade;
			else
				return y->eficiencia - x->eficiencia;
		case 51:
			if (x->velocidade != y->velocidade)
				return y->velocidade - x->velocidade;
			else
				return x->eficiencia - y->eficiencia;
		
		case 60:
			return x->entrega - y->entrega;
		case 61:
			return y->entrega - x->entrega;
		
		default:
			return 0;
	}
}

/* Cria nó */
lista *criar (char mod[], int vel, double ef, int c, int ent)
{
    lista *novo = malloc(sizeof(lista));
	if (!novo) return NULL;
	
    strcpy(novo->modelo, mod);
    novo->velocidade = vel;
    novo->eficiencia = ef;
	novo->capacidade = c;
	novo->entrega = ent;
    novo->next = NULL;
	
    return novo;
}

/* Add (append) recursivo */
lista *add(lista *x, char mod[], int vel, double ef, int c, int ent)
{  
    if (x == NULL) //lista vazia
		return criar(mod, vel, ef, c, ent);
	else
	    x->next = add(x->next, mod, vel, ef, c, ent);
	 
    return x;
}

/* Imprime recursivamente */
void imprimir (lista *x)
{
    if (x != NULL) {
        printf("[M=%s V=%d KM-L=%.2lf C=%d E=%d]\n", x->modelo, x->velocidade, x->eficiencia, x->capacidade, x->entrega);
        imprimir(x->next);
    }        
}

/* Libera e retorna NULL, recursivo */
lista *liberar (lista *x)
{
    if (x == NULL)
		return NULL;
	
    if (x->next != NULL)
		x->next = liberar(x->next);
	
    free(x);
    return NULL;
}

/* Retorna o ultimo no da lista */
lista *ultimo (lista *lst)
{
	lista *aux = lst;
	if (!aux) return NULL;
	
	while (aux->next)
		aux = aux->next;
	
	return aux;
}

/* Toma o ultimo elemento como pivo e particiona */
lista *partition (lista *head, lista *last, lista **novoHead, lista **novoLast)
{
	lista *pivo = last;
	lista *prev = NULL;
	lista *cur = head;
	lista *ultimoNo = pivo;
	
	while (cur != pivo) {
		if (compara(cur, pivo) < 0) {
			if (!(*novoHead)) 
				*novoHead = cur;
			
			prev = cur;
			cur = cur->next;
		}
		else { //cur = end->next e muda end
			if (prev)
				prev->next = cur->next;
			lista *tmp = cur->next;
			cur->next = NULL;
			ultimoNo->next = cur;
			ultimoNo = cur;
			cur = tmp;
		}
	}
	
	if (!(*novoHead))
		*novoHead = pivo;
	
	*novoLast = ultimoNo;
	
	return pivo;
}

lista *QuickSort (lista *head, lista *last)
{
	if (!head || head == last) return head;
	
	lista *novoHead = NULL;
	lista *novoLast = NULL;
	lista *pivo = partition (head, last, &novoHead, &novoLast);
	
	if (novoHead != pivo) {		
		//no antes do pivo passa a ser o ultimo (next = NULL)
		lista *tmp = novoHead;
		while (tmp->next != pivo) 
			tmp = tmp->next;
		tmp->next = NULL;
		
		novoHead = QuickSort(novoHead, tmp);
		
		//muda o next do fim da primeira metade para o pivo
		tmp = ultimo(novoHead);
		tmp->next = pivo;
	}
	
	pivo->next = QuickSort(pivo->next, novoLast);
	
	return novoHead;
}

int main() {
	char modelo[51];
    int velocidade, capacidade, entrega, input;
	double eficiencia;
	
    lista *head = NULL;
	scanf("%d", &input);
	while (input != 0) {
        switch (input) {
            case 1:
                scanf("%s %d %lf %d %d", modelo, &velocidade, &eficiencia, &capacidade, &entrega);
                head = add(head, modelo, velocidade, eficiencia, capacidade, entrega);
                break;
			
            case 8:
                scanf("%d", &modoDeComparacao);
                head = QuickSort(head, ultimo(head));
                printf("[O=%d]\n", modoDeComparacao);
                imprimir(head);
                break;
			
            case 2:
				printf("[DISCOS]\n");
                imprimir(head);
                break;
			
			default:
				break;
        }
		scanf("%d\n", &input);
    }
    head = liberar(head);
	
    return 0;
}
