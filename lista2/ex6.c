#include <stdlib.h>
#include <stdio.h>

int len (char * s)
{
	int l;
	for (l = 0; s[l] != '\0'; l++);
	return l;
}

int busca (char *s, int * posicoes, int len, char t)
{
	int j = 0;
	for (int i = 0; i < len; i++)
		if (s[i] == t) posicoes[j++] = i;
	
	return j;
}

int main () {
	char s[] = "ABCDEFGHIJabcdefghij";
	int *posicoes = malloc(len(s));
	
	int tamanho_pos = busca(s, posicoes, len(s), 'a');
	
	printf ("posicoes: ");
	for (int i = 0; i < tamanho_pos; i++)
		printf ("%d ", posicoes[i]);
	printf ("\n");
	
	free(posicoes);
	
	return 0;
}
