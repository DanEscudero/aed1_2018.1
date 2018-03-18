#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
	int data;
	struct node *next;
} node;

typedef struct stack {
	node *list;
} stack;

typedef struct caracter
{
	char id;
	char *l1;
	char *l2;
	char *l3;
} caracter;

void set_caracter (caracter * v_car, int len);

int length (char *s)
{
	int len;
	for (len = 0; s[len] != '\0'; len++);
	return len;
}

char * strrev (char *s)
{
	int len = 0;
	char temp;
	
	while (s[len] != '\0')
		len++;
	
	for (int i = 0; i < len/2; i++) {
		temp = s[i];
		s[i] = s[len-1-i];
		s[len-1-i] = temp;
	}
	return s;	
}

void hexa(unsigned long long int num, char* string)
{
	char temp;
	int i = 0;
	while (num) {
		temp = num%16;
		num /= 16;
		
		if (temp < 10) temp += 48;
		else temp += 55;

		string[i++] = temp;
	}
	string = strrev(string);
}

caracter* string_to_caracter (char *string, int len)
{
	caracter *v_car = malloc(len * sizeof(caracter));
	char temp;
	for (int i = 0; i < len; i++) {
		temp = string[i];
		v_car[i].id = temp;
	}
	return v_car;
}

void setup_vetor (caracter *v_car, int len)
{
	for (int i = 0; i < len; i++) {
		v_car[i].l1 = malloc(sizeof(char) * 1);
		v_car[i].l2 = malloc(sizeof(char) * 4);
		v_car[i].l3 = malloc(sizeof(char) * 4);
	}
}

void print_caracter (caracter *v_car, int len)
{		
	for (int i = 0; i < len; i++)
		printf("%s", v_car[i].l1);
	printf ("\n");

	for (int i = 0; i < len; i++)
		printf("%s", v_car[i].l2);
	printf ("\n");

	for (int i = 0; i < len; i++)
		printf("%s", v_car[i].l3);
	printf ("\n");
}

/* Aloca a lista, e retorna o ponteiro */
stack * createStack ()
{
	stack *novo = malloc(sizeof(stack));
	
	if (!novo) return 0;
	return novo;
}

/* Libera a memoria da pilha, e fica NULL */
void freeStack (stack *pilha)
{
	node *aux = pilha->list->next;
	while (aux) {
		aux = aux->next;
		free(pilha->list);
		pilha->list = aux;
	}
	pilha = NULL;
}

/* Imprime a lista */
void printStack (stack *pilha)
{
	node *aux;
	printf("PILHA:\t");
	for (aux = pilha->list; aux; aux = aux->next)
		printf("%d  ", aux->data);
	printf("\n");
	
}

/* Push data para a lista, 1 se bem sucedido */
int push (stack *pilha, int data)
{
	node *aux = malloc(sizeof(node));
	if (!aux) return 0;
	
	aux->data = data;
	aux->next = pilha->list;
	pilha->list = aux;
	
	return 1;
}

/* Pop o elemento da lista para *elem, retorna 1 se or sucedido */
int pop (stack *pilha, int *elem)
{
	if (!pilha->list) return 0;
	
	*elem = pilha->list->data;
	
	node *aux;
	aux = pilha->list;
	pilha->list = pilha->list->next;
	free(aux);
	return 1;
}

int main ()
{
	int len, popped;
	unsigned long long int num = 0, potencia = 1;
	char s_input[255], *string;
	caracter *v_car;
	stack *pilha = createStack();
	
	string = malloc(sizeof(char));
	
	scanf("%s", s_input);
	for (int i = 0; s_input[i] != 'b'; i++)
		push(pilha, s_input[i]-48);
	
	while (pop(pilha, &popped)) {
		num += potencia*popped;
		potencia *= 2;
	}
	
	printf("num: %lld\n", num);
	
	hexa(num, string);
	len = length(string);
	printf("%s\n", string);
	
	v_car = string_to_caracter(string, len);
	set_caracter(v_car, len);
	print_caracter(v_car, len);
	
	return 0;
}

void set_caracter (caracter * v_car, int len)
{
	caracter *temp;
	for (int i = 0; i < len; i++) {
		temp = &v_car[i];
		switch ((int)temp->id) {
			case 48:
				temp->l1 = " _ ";
				temp->l2 = "| |";
				temp->l3 = "|_|";
				break;
			
			case 49:
				temp->l1 = "   ";
				temp->l2 = "  |";
				temp->l3 = "  |";
				break;
			
			case 50:
				temp->l1 = " _ ";
				temp->l2 = " _|";
				temp->l3 = "|_ ";
				break;
			
			case 51:
				temp->l1 = " _ ";
				temp->l2 = " _|";
				temp->l3 = " _|";
				break;
			
			case 52:
				temp->l1 = "   ";
				temp->l2 = "|_|";
				temp->l3 = "  |";
				break;
			
			case 53:
				temp->l1 = " _ ";
				temp->l2 = "|_ ";
				temp->l3 = " _|";
				break;
			
			case 54:
				temp->l1 = " _ ";
				temp->l2 = "|_ ";
				temp->l3 = "|_|";
				break;
			
			case 55:
				temp->l1 = " _ ";
				temp->l2 = "  |";
				temp->l3 = "  |";
				break;
			
			case 56:
				temp->l1 = " _ ";
				temp->l2 = "|_|";
				temp->l3 = "|_|";
				break;
			
			case 57:
				temp->l1 = " _ ";
				temp->l2 = "|_|";
				temp->l3 = " _|";
				break;
			
			case 65:
				temp->l1 = " _ ";
				temp->l2 = "|_|";
				temp->l3 = "| |";
				break;
			
			case 66:
				temp->l1 = "   ";
				temp->l2 = "|_ ";
				temp->l3 = "|_|";
				break;
			
			case 67:
				temp->l1 = " _ ";
				temp->l2 = "|  ";
				temp->l3 = "|_ ";
				break;
			
			case 68:
				temp->l1 = "   ";
				temp->l2 = " _|";
				temp->l3 = "|_|";
				break;
			
			case 69:
				temp->l1 = " _ ";
				temp->l2 = "|_ ";
				temp->l3 = "|_ ";
				break;
			
			case 70:
				temp->l1 = " _ \0";
				temp->l2 = "|_ ";
				temp->l3 = "|  ";
				break;
			
		}
	}	
}














