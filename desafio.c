/*
Código de https://github.com/carrafo
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Matriz matriz;

struct Matriz{
	int num;
	int linha;
	int coluna;
	matriz *right;
	matriz *down;
};

matriz *setupMatriz ()
{
	matriz *m = malloc(sizeof(matriz));
	m->right = NULL;
	m->down = NULL;
	m->linha = -1;
	return m;
}

void insere2 (matriz *lin, matriz *col, matriz *v)
{
	if((!lin->right || lin->right->coluna > v->coluna) && (!col->down || col->down->linha > v->linha)){
		v->right = lin->right;
		v->down = col->down;
		lin->right = v;
		col->down = v;
	}
	else if (lin->right != NULL && lin->right->coluna < v->coluna)
		insere2(lin->right, col, v);
	else if (col->down != NULL && col->down->linha < v->linha)
		insere2(lin, col->down, v);
}

void insere (matriz *lin, matriz *col, int l, int c, int n)
{
	if(lin->linha == l){
	    if(col->coluna == c){
			matriz *aux = malloc(sizeof(matriz));
			aux->num=n;
			aux->linha=l;
			aux->coluna=c;
			aux->right=NULL;
			aux->down=NULL;
			insere2(lin,col,aux);
		}
		else if(col->right == NULL || col->right->coluna > c){
			matriz *aux = malloc(sizeof(matriz));
			aux->coluna = c;
			aux->down = NULL;
			aux->right = col->right;
			col->right = aux;
			insere(lin, aux, l, c, n);
		}
		else{
		    insere(lin, col->right, l, c, n);
		}
	}
	else if (lin->down == NULL || lin->down->linha > l) {
		matriz *aux = malloc(sizeof(matriz));
		aux->linha = l;
		aux->right = NULL;
		aux->down = lin->down;
		lin->down = aux;
		insere(aux, col, l, c, n);
	}
	else {
	    insere(lin->down, col, l, c, n);
	}
}

void imprime (matriz *linha, int l, int c)
{
	matriz *aux = linha;
	for (int i = 0; i < l ; i++) {
		if (aux->linha < i && aux->down)
			aux = aux->down;
		if (aux->linha == i) {
			matriz *aux2 = aux->right;
			printf("[ ");
			
			for (int j = 0; j < c ; j++) {
				if (aux2->coluna == j) {
					printf("%d ",aux2->num);
					if(aux2->right)
						aux2 = aux2->right;
				}
				else printf("%d ",0);
			}
			printf("]\n");
		}

		else {
			printf("[ ");
			for (int j = 0; j < c ; j++)
				printf("%d ",0);
			printf("]\n");
		}
	}
	printf("\n");
}

int soma (matriz *A, matriz *B)
{
	int sum = 0;
	matriz *auxA = A;
	matriz *auxB = B;
	
	if (auxA->coluna > auxB->linha && auxB->down) 
		sum += soma(auxA,auxB->down);
	
	else if (auxA->coluna < auxB->linha && auxA->right) 
		sum += soma(auxA->right,auxB);
	
	else if (auxA->coluna == auxB->linha && auxB->down && auxA->right)
		sum += soma(auxA->right,auxB->down) + auxA->num * auxB->num;
	
	else if (auxA->coluna == auxB->linha)
		sum += auxA->num * auxB->num;
	
	return sum;
}

void multiplica (matriz *linA, int la, int ca, matriz *colB, int lb, int cb)
{
	if (ca != lb) {
		printf("ERRO\n");
		return;
	}
	
	matriz *auxA = linA;
	for(int i=0; i<la; i++) {
		if(auxA->linha < i && auxA->down != NULL)
			auxA = auxA->down;
		
		if(auxA->linha == i){
			matriz *auxB = colB;
			printf("[ ");
			for (int j=0; j<cb; j++) {
				if(auxB->coluna < j && auxB->right != NULL) 
					auxB = auxB->right;
				if(auxB->coluna == j)
					printf("%d ",soma(auxA->right,auxB->down));
				else printf("%d ",0);
			}
			printf("]\n");
		}

		else {
			printf("[ ");
			for(int j = 0; j < cb ; j++)
				printf("%d ",0);
			printf("]\n");
		}
	}
	printf("\n");
}

void liberar (matriz *x)
{
	if(x->down) liberar(x->down);
	if(x->right) liberar(x->right);
	free(x);
}


int main (void){
	int la, ca, na, lb, cb, nb, l, c, num;
	char input;

	matriz *linA = setupMatriz();
	matriz *colA = setupMatriz();
	matriz *linB = setupMatriz();
	matriz *colB = setupMatriz();

	scanf("%d %d %d %d %d %d", &la, &ca, &na, &lb, &cb, &nb);

	for (int i = 0 ; i < na ; i++){
		scanf("%d %d %d", &l, &c, &num);
		insere(linA, colA, l, c, num);
	}
	
	for (int i=0; i < nb; i++){
		scanf("%d %d %d", &l, &c, &num);
		insere(linB, colB, l, c, num);
	}
	
	scanf("%c", &input);
	
	while (input != 'S'){
		switch (input) {
			case 'A':
			case 'a':
				imprime(linA, la, ca);
				break;
			case 'B':
			case 'b':
				imprime(linB, lb, cb);
				break;
			case 'M':
			case 'm':
				multiplica(linA, la, ca, colB, lb, cb);
				break;
		}
		scanf("%c", &input);
	}

	liberar(linA);
	liberar(colA);
	liberar(linB);
	liberar(colB);

	return 0;
}