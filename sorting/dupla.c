/* DUPLA:  11005716 Daniel Escudero
           11016916 Caio Cesar      */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista {
    char nome[51];
    int nota;
    int ra;
    struct Lista *next;
}lista;

int comparacoes = 0;

/* Troca os campos ra, nota e nome do jeito mais idiota possivel */
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
	
	strcpy(tempChar, node1->nome);
	strcpy(node1->nome, node2->nome);
	strcpy(node2->nome, tempChar);
}

/* Compara e retorna, similar a strcmp, mas funciona para nos e recebe chave */
int comparar(lista *x, lista *y, int chave) {
    if (chave == 1)
		return x->ra-y->ra;
    else
		return strcmp(x->nome,y->nome);
}

/* Retorna o menor no da lista lst, baseado na chave, iterativo */
lista *minList (lista *lst, int chave)
{
    if (!lst) return NULL;
    
    lista *aux = lst;
    lista *min = aux;
    
    while (aux) {
        if (aux->next) comparacoes++;
        if ((chave == 1 && aux->ra < min->ra)	                //MINIMO POR RA
         || (chave == 2 && strcmp(aux->nome, min->nome) < 0))   //MINIMO POR NOME
                min = aux;
        aux = aux->next;
    }
    return min;
}

/* Recursivo, na main: lst = menor = lst */
lista *min (lista *lst, lista *menor, int chave) {
    if (lst == NULL)
        return menor;
	
    if (chave == 1) {
        if(lst->ra < menor->ra)
            return min(lst->next, lst, chave);
        else
            return min(lst->next, menor, chave);
    }
	
    if (chave == 2) {
        if(strcmp(lst->nome, menor->nome) < 0)
            return min(lst->next, lst, chave);
        else
            return min(lst->next, menor, chave);
    }
}

/* Cria nó */
lista *criar (int ra, char nome[], int nota) {
    lista *novo = malloc(sizeof(lista));
    strcpy(novo->nome,nome);
    novo->ra = ra;
    novo->nota = nota;
    novo->next = NULL;
    return novo;
}

/* Add (append) recursivo */
lista *add(lista *x, char nome[], int ra, int nota){  
    if (x == NULL)
		return criar(ra, nome, nota);
	
    x->next = add(x->next, nome, ra, nota);
	 
    return x;
}

/* Busca Recursivo */
int busca(lista *x, int ra, int C){
    if (x == NULL)
		return -1;
	
    if (x->ra == ra)
		return C;
	
    return busca(x->next, ra, ++C);
}

/* Imprime recursivo */
void imprimir (lista *x) {
    if (x != NULL) {
        printf("[%d %s %d]\n", x->ra, x->nome, x->nota);
        imprimir(x->next);
    }        
}

/* Libera e retorna NULL, recursivo */
lista *liberar (lista *x) {
    if (x == NULL)
		return NULL;
	
    if (x->next != NULL)
		x->next = liberar(x->next);
	
    free(x);
    return NULL;
}

/* chave: 1 = ra 2 = nome */
lista *selection_sort (lista *lst, int chave){
    lista *aux = lst;
    lista *minimo = NULL;
	
    while (aux) {
        minimo = minList(aux, chave);
        swapNode(aux, minimo);
        aux = aux->next;
    }
    return lst;
}

lista *inserir(lista *tmp, lista *head, int chave){
    if(head->next == NULL) return head;
    if(head->next->ra != tmp->ra) head->next = inserir(tmp, head->next, chave);
    int k = comparar(head, tmp, chave);
    if(k > 0){
        comparacoes++;
        return head;
    }
    else{
        tmp->next = head;
        return tmp;
    }
}

lista *insertion_sort(lista *head, lista *x, int chave){
    if(x == NULL) return NULL;
    lista *tmp = criar(x->ra, x->nome, x->nota);
    head = inserir(tmp,head,chave);
    comparacoes++;
    x = x->next;
    x->next = insertion_sort(head, x->next, chave);
    return x;
}

/* Chama o algoritmo de ordenacao adequado */
lista *ordenar (lista *x, int algoritmo, int chave) {
    if (algoritmo == 1)
		return selection_sort(x, chave);
	
    if (algoritmo == 2)
		return insertion_sort(x, x, chave);
}

int main() {
	char input, nome[51];
    int ra, nota, algoritmo, chave;
    lista *head = NULL;
    while (scanf("\n%c", &input), input != 'P' && input != 'p') {
        switch (input) {
            case 'I':
            case 'i':
                scanf("%d %s %d", &ra, nome, &nota);
                head = add(head, nome, ra, nota);
                break;
			
            case 'O':
            case 'o':
                comparacoes = 0;
                scanf("%d %d", &algoritmo, &chave);
                head = ordenar(head, algoritmo, chave);
                printf("Comparacoes=%d\n", comparacoes);
                break;
			
            case 'B':
            case 'b':
                scanf("%d", &ra);
                printf("Pos=%d\n", busca(head, ra, 0));
                break;
			
            case 'M':
            case 'm':
                imprimir(head);
                break;
        }
    }
    head = liberar(head);
	
    return 0;
}








