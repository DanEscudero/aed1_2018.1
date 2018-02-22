#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

char * hexa(unsigned long long int num)
{
	char *string = malloc(sizeof(char));
	char temp;
	int i = 0;
	while (num) {
		temp = num%16;
		num/=16;
		
		if (temp < 10) temp += 48;
		else temp += 55;
		
		string[i++] = temp;
	}
	string = strrev(string);
	return string;
}

caracter* string_to_caracter (char *string, int len)
{
	caracter *v_car = malloc(len * sizeof(caracter));
	char temp;
	for (int i = 0; i < len; i++) {
		temp = string[i];
		v_car[i].id = temp;
	}
	/*printf("string: %d\n", string[0]);
	printf("v_car[0].id: %d\n", v_car[0].id);*/
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

int main ()
{
	unsigned long long int n1 = 11073303771280;
	char *string;
	caracter *v_car;
	int len;

	string = hexa(n1);
	len = length(string);
	printf("%s\n", string);

	v_car = string_to_caracter(string, len);
	set_caracter(v_car, len);
	print_caracter(v_car, len);
	
	return (0);
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