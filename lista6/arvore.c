#include <stdlib.h>
#include <stdio.h>

typedef struct tree {
    int data;
    struct tree *left;
    struct tree *right;
} tree;

void *inOrder (tree *arvore)
{
    if(arvore) {
        inOrder(arvore->left);
        printf("%d ", arvore->data);
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

tree * maxValue (tree *arvore)
{
	if (!arvore) return arvore;
	tree *aux = arvore;
	while (aux->right) aux = aux->right;
	
	return aux;
}

tree *insereArvore (tree *arvore, int valor)
{
    if (arvore == NULL) {
        tree *novo = malloc(sizeof(tree));
        novo->data = valor;
        novo->left = NULL;
        novo->right = NULL;
        return novo;
    }
    else if (valor > arvore->data) {
        arvore->right = insereArvore(arvore->right, valor);
    }
    else if (valor < arvore->data) {
        arvore->left = insereArvore(arvore->left, valor);
    }
    else {
        arvore->data = valor;
    }
    return arvore;
}

tree *buscaArvore (tree *arvore, int x)
{
    tree *aux = arvore;
    while (aux) {
        if (x > aux->data) {
            aux = aux->right;
        }
        else if (x < aux->data) {
            aux = aux->left;
        }
        else return aux;
    }
    return aux;
}

tree * removeTree (tree *arvore, int x)
{
	if (!arvore) return arvore;
	
	else if (x < arvore->data)
		arvore->left = removeTree(arvore->left, x);
	
	else if (x > arvore->data)
		arvore->right = removeTree(arvore->right, x);
	
	//Chega aqui quando o no avaliado eh o no que contem x
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
			arvore->data = aux->data;
			arvore->right = removeTree(arvore->right, aux->data);
		}
	}
	return arvore;
}

tree * antecessor (tree *arvore, int x)
{
	if (!arvore) return NULL;
	
	tree *buscado = buscaArvore(arvore, x);
	if (!buscado) return buscado;
	if (buscado->left)
		return maxValue(buscado->left);
	
	tree *antec = NULL;
	while (arvore) {
		if (x == arvore->data) {
			break;
		}
		else if (x < arvore->data) {
			arvore = arvore->left;
		}
		else if (x > arvore->data) {
			antec = arvore;
			arvore = arvore->right;
		}
	}
	return antec;	
}

tree * sucessor (tree *arvore, int x)
{
	if (!arvore) return NULL;
	
	tree *buscado = buscaArvore(arvore, x);
	if (!buscado) return buscado;
	if (buscado->right)
		return minValue(buscado->right);
	
	tree *suc = NULL;
	while (arvore) {
		if (x == arvore->data) {
			break;
		}
		else if (x < arvore->data) {
			suc = arvore;
			arvore = arvore->left;
		}
		else if (x > arvore->data) {
			arvore = arvore->right;
		}
	}
	return suc;
}

int main () {
    tree *arvore = NULL;
    
    arvore = insereArvore(arvore, 30);
    arvore = insereArvore(arvore, 50);
    arvore = insereArvore(arvore, 30);
    arvore = insereArvore(arvore, 20);
    arvore = insereArvore(arvore, 40);
    arvore = insereArvore(arvore, 70);
    arvore = insereArvore(arvore, 60);
    arvore = insereArvore(arvore, 80);
    
    printf("Arvore:\n");
    inOrder(arvore);
    printf("\n");
    
	printf("==== BUSCA (0 para sair) ====\n");
    int input_busca = 1, valor_busca;
	scanf("%d", &input_busca);
    while (input_busca) {
        printf("buscaArvore(%d): ", input_busca);
        
        tree *buscado = buscaArvore(arvore, input_busca);
        if (buscado)
            printf("%d\n", buscado->data);
        else
            printf("Nao encontrado\n");

		scanf("%d", &input_busca);
    }

	printf("==== REMOCAO (0 para sair) ====\n");
	int input_remocao = 1, valor_remocao;
	scanf("%d", &input_remocao);
    while (input_remocao) {
        printf("remove(%d): ", input_remocao);
        
        arvore = removeTree(arvore, input_remocao);
		inOrder(arvore);
		printf("\n");
		
    	scanf("%d", &input_remocao);
    }
	
	printf("Arvore:\n");
    inOrder(arvore);
    printf("\n");
	
	printf("==== INSERCAO (0 para sair) ====\n");
	int input_insere = 1, valor_insere;
    scanf("%d", &input_insere);
    while (input_insere) {
        printf("insere(%d): ", input_insere);
        
        arvore = insereArvore(arvore, input_insere);
		inOrder(arvore);
		printf("\n");
		
		scanf("%d", &input_insere);
    }

	printf("Arvore:\n");
    inOrder(arvore);
    printf("\n");
	
	printf("==== ANTECESSOR E SUCESSOR (0 para sair) ====\n");
	int input_ant = 1, valor_ant;
    while (input_ant) {
		scanf("%d", &input_ant);
		
		printf("antecessor(%d): ", input_ant);
		tree *no_ant = antecessor(arvore, input_ant);		
		if (no_ant)
			printf ("%d\n", no_ant->data);
		else
			printf ("sem antecessor\n");
		
		printf("sucessor(%d): ", input_ant);
		tree *no_suc = sucessor(arvore, input_ant);
		if (no_suc)
			printf ("%d\n", no_suc->data);
		else
			printf ("sem sucecessor\n");
    }
	
    return 0;
}

