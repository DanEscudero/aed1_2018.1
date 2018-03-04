#include <stdlib.h>
#include <stdio.h>

int len (char * s)
{
	int l;
	for (l = 0; s[l] != '\0'; l++);
	return l;
}

char * converte (char *s, char t, int l)
{
	if (t == 'a') { //para maiuscula
		for (int i = 0; i < l; i++)
			if ((int)s[i] >= 97 && (int)s[i] <= 122)
				s[i] -= 32;
	}
	else if (t == 'b') { // para minuscula
		for (int i = 0; i < l; i++)		
			if (s[i] >= 65 && s[i] <= 90)
				s[i] += 32;
	}
	else if (t == 'c') { // para titulo
		if (s[0] >= 97 && s[0] <= 122)
				s[0] -= 32;
		for (int i = 1; i < l; i++) {
			if (s[i-1] == ' ')
				if (s[i] >= 65 && s[i] <= 90)
					s[i] += 32;
			else
				if (s[i] >= 97 && s[i] <=122)
					s[i] -= 32;
		}
	}
	
	return s;
}

int main ()
{
	char s[] = "Abc ABC abc";	
	printf ("%s\n", s);
	
	converte(s, 'a', len(s));
	printf("%s\n", s);
	
	converte(s, 'b', len(s));
	printf("%s\n", s);
	
	converte(s, 'c', len(s));
	printf("%s\n", s);
	
	return 0;
}
