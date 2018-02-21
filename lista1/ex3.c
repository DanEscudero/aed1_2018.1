#include <stdlib.h>
#include <stdio.h>

char * strrev (char *s)
{
	int len = 0;
	char temp;
	
	while (s[len] != '\0')
		len++;
	
	for (int i = 0; i < len; i++) {
		temp = s[i];
		s[i] = s[len-1-i];
		s[len-1-i] = temp;
	}
	return s;	
}

void hexa(unsigned long long int num, char **p_s)
{
	unsigned long long int resto;
	int i = 1, j, temp;
	char string[100];
	
	while (num) {
		temp = num%16;
		
		if (temp < 10) temp += 48;
		else temp += 55;
		
		string[i++] = temp;
		num /= 16;
	}
	p_s = &string;
	//return string;
}

int main ()
{
	char **p_string;
	unsigned long long int n1 = 11073303771280;
	
	hexa(n1, p_string);
	printf ("%llx\n", n1);
	printf ("%s\n", *p_string);
	return (0);
}















