#include <stdlib.h>
#include <stdio.h>

typedef struct tree {
    int ra;
	int nota;
    struct tree *left;
    struct tree *right;
} tree;

void *inOrder (tree *arvore)
{
    if(arvore) {
        inOrder(arvore->left);
        printf("(%d, %d) ", arvore->ra, arvore->nota);
        inOrder(arvore->right);
    }
}

tree * minValue (tree *arvore)
{
	if (!arvore) return arvore;
	tree *aux = arvore;
	while (aux->left) aux = aux->left;
	
	return aux;
}

int max (int a, int b)
{
	return a > b ? a : b;
}

tree *insereArvore (tree *arvore, int ra, int nota)
{
    if (!arvore) {
        tree *novo = malloc(sizeof(tree));
        novo->nota = nota;
		novo->ra = ra;
        novo->left = NULL;
        novo->right = NULL;
        return novo;
    }
	
    else if (ra > arvore->ra) {
        arvore->right = insereArvore(arvore->right, ra, nota);
    }
	
    else if (ra < arvore->ra) {
        arvore->left = insereArvore(arvore->left, ra, nota);
    }
	
    else {
        arvore->ra = ra;
		arvore->nota = nota;
    }
	
    return arvore;
}

tree * removeTree (tree *arvore, int x)
{
	if (!arvore) return arvore;
	
	else if (x < arvore->ra)
		arvore->left = removeTree(arvore->left, x);
	
	else if (x > arvore->ra)
		arvore->right = removeTree(arvore->right, x);
	
	//Chega aqui quando arvore->ra == x
	else {
		//caso 1: sem filhos
		if (!arvore->left && !arvore->right) {
			free(arvore);
			arvore = NULL;
		}
		//caso 2.1: filho na direita
		else if (!arvore->left) {
			tree *aux = arvore;
			arvore = arvore->right;
			free(aux);
		}
		//caso 2.2: filho na esquerda
		else if (!arvore->right) {
			tree *aux = arvore;
			arvore = arvore->left;
			free(aux);
		}
		//caso 3: dois filhos
		else {
			tree *aux = minValue(arvore->right);
			arvore->ra = aux->ra;
			arvore->nota = aux->nota;
			arvore->right = removeTree(arvore->right, aux->ra);
		}
	}
	return arvore;
}

int alturaTree (tree *arvore)
{
	if (!arvore) 
		return -1;
	else 
		return max(alturaTree(arvore->left), alturaTree(arvore->right)) + 1;
}

tree *buscaArvore (tree *arvore, int ra, int *comparacoes)
{
    tree *aux = arvore;
	*comparacoes = 0;
    while (aux) {
		(*comparacoes)++;
        if (ra > aux->ra) {
            aux = aux->right;
        }
        else if (ra < aux->ra) {
            aux = aux->left;
        }
        else return aux;
    }
	
    return aux;
}

void freeTree(tree *arvore)
{
    if (!arvore) return;
    freeTree(arvore->right);
    freeTree(arvore->left);
    free(arvore);
}

int main () {
	char input = 0;
	int ra = 0, nota = 0;
	int comp;
	tree *arvore = NULL;
	
	scanf("\n%c", &input);
	
	while (input != 'P' && input != 'p') {
		switch (input) {
			case 'I':
			case 'i':
				scanf ("%d %d", &ra, &nota);
				arvore = insereArvore(arvore, ra, nota);
				break;
			
			case 'R':
			case 'r':
				scanf ("%d", &ra);
				arvore = removeTree(arvore, ra);
				break;
			
			case 'B':
			case 'b':
				scanf("%d", &ra);
				//comp = 0;
				tree *busca = buscaArvore(arvore, ra, &comp);
				if (!busca)	nota = -1;
				else 		nota = busca->nota;
				
				printf("C=%d Nota=%d\n", comp, nota);
				break;
			
			case 'A':
			case 'a':
				printf("A=%d\n", alturaTree(arvore));
				break;
		}
		/*printf("ARVORE:\n");
		inOrder(arvore);
		printf("\n");*/
		scanf("\n%c", &input);
	}
	
	freeTree(arvore);
	
	return 0;
}
