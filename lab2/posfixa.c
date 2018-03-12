 #include <stdlib.h>
#include <stdio.h>

#define MINCAPACITY 15

typedef struct node
{
	double data;
	struct node *next;
} node;

typedef struct arrStack
{
	node *data;
} arrStack;

arrStack* criaPilha ()
{
	arrStack *novo = malloc(sizeof(arrStack));
	if (!novo) return NULL;
	
	novo->data = NULL;
	/*if (!novo->data) {
		free(novo);
		return NULL;
	}*/
	
	return novo;
}

int isEmpty (arrStack *pilha) { return !pilha->data; }

int erro ()
{
	printf("ERRO\n");
}

/* Empilha, retorna o novo tamanho, e 0 se cheio */
void push (arrStack *pilha, double elem)
{
	node *novo = malloc(sizeof(node));
	novo->data = elem;
	novo->next = pilha->data;
	pilha->data = novo;
}

/* Desempilha, retorna o novo tamanho, e -1 se vazio. O elemento fica em *elem */
int pop (arrStack *pilha, double *elem)
{
	if (isEmpty(pilha)) {
//		erro();
		return 0;
	}
	
	*elem = pilha->data->data;
	
	node *aux = pilha->data;
	pilha->data = pilha->data->next;
	free(aux);
	
	return 1;
}

double h (double a) { return 3*a; }
double mais (double a, double b) { return a+b; }
double menos (double a, double b) { return a-b; }
double f (double a, double b, double c) { return (a*a)-((b)/2) + c; }
double g (double a, double b, double c) { return (a*b) + c; }

int len (char *s)
{
	int len;
	for (len = 0; s[len] != '\0'; len++);
	return len;
}

void printPilha (arrStack* pilha)
{
	printf("Pilha:\n");
	for(node *aux = pilha->data; aux; aux = aux->next) {
		printf("%.2lf\t", aux->data);
	}
	printf("\n\n");
}

int main ()
{
	char expressao[100], t;
	scanf("%s", expressao);
	
	double n1, n2, n3, resultado;
	
	int j = 0;
	arrStack *pilha = criaPilha();
		
	for (int i = 0; i < len(expressao); i++) {
		t = expressao[i];
		if (t >= 48 && t <= 57) {
			push (pilha, t-48);
		}
		else {
			if (t == 'h') {
				if (pop (pilha, &n1))
					push (pilha, h(n1));
				else {
					erro();
					return 0;
				}
			}
			else if (t == '+') {
				if (pop (pilha, &n2) &&
					pop (pilha, &n1))
					push (pilha, mais(n1, n2));
				else {
					erro();
					return 0;
				}
			}
			else if (t == '-') {
				if (pop (pilha, &n2) &&
					pop (pilha, &n1))
					push (pilha, menos(n1, n2));
				else {
					erro();
					return 0;
				}
			}
			else if (t == 'f') {
				if (pop (pilha, &n3) &&
					pop (pilha, &n2) &&
					pop (pilha, &n1))
					push (pilha, f(n1, n2, n3));
				else {
					erro();
					return 0;
				}
			}
			else if (t == 'g') {
				if (pop (pilha, &n3) &&
					pop (pilha, &n2) &&
					pop (pilha, &n1))
					push (pilha, g(n1, n2, n3));
				else {
					erro();
					return 0;
				}	
			}
		}
	}
	
	if (pop(pilha, &resultado) && isEmpty(pilha)) printf("%.2lf\n", resultado);
	else printf("ERRO\n");

	return 0;
}
























