#include <stdlib.h>
#include <stdio.h>

int len (char *s)
{
	int l;
	for (l = 0; s[l] != '\0'; l++);
	return l;
}

char * concat (char *s1, char *s2)
{
	int n1 = len(s1);
	int n2 = len(s2);
	char *s = malloc ((n1 + n2) * sizeof(char));
	for (int i = 0; i < n1 + n2; i++) {
		if (i < n1) s[i] = s1[i];
		else s[i] = s2[i-n1];
	}
	return s;
}

int main ()
{
	char *s1 = malloc(255), *s2 = malloc(255);
	scanf("%s", s1);
	scanf("%s", s2);
	
	printf ("%s\n", concat(s1, s2));
	
}

