#include <stdlib.h>
#include <stdio.h>

typedef struct avlNode
{
	int ra;
	int nota;
	int height;
	struct avlNode *left;
	struct avlNode *right;
} avlNode;

int max (int a, int b)
{
	return (a > b) ? a : b;
}

int updateHeight (avlNode *node)
{
	if (!node) return -1;
	node->height = max(updateHeight(node->left), updateHeight(node->left)) + 1;
	return node->height;
}

int balanceFactor (avlNode *node)
{
	if (!node) return 0;
	int hleft = (node->left) ? node->left->height : -1;
	int hright = (node->right) ? node->right->height : -1;
	return hleft - hright;
}

void rotateLL (avlNode **root) //SD
{
	avlNode *p = *root;
	avlNode *leftChild = p->left;
	
	p->left = leftChild->right;
	leftChild->right = p;
	
	updateHeight(p);
	
	*root = leftChild;
	
	printf("[No desbalanceado: %d]\n", p->ra);
	printf("[Rotacao: SD]\n");
	printf("[x=%c y=%d z=%d]\n", '?', leftChild->ra, p->ra);
}

void rotateRR (avlNode **root) //SE
{
	avlNode *p = *root;
	avlNode *rightChild = p->right;
	
	p->right = rightChild->left;
	rightChild->left = p;
	
	updateHeight(p);
	
	*root = rightChild;
	
	printf("[No desbalanceado: %d]\n", p->ra);
	printf("[Rotacao: SE]\n");
	printf("[x=%d y=%d z=%c]\n", p->ra, rightChild->ra, '?');
}

void rotateLR (avlNode **root) //DD
{
	avlNode *p = *root;
	avlNode *leftChild = p->left;
	avlNode *rightGrandChild = leftChild->right;
	
	//rotateLeft(leftChild)
	leftChild->right = rightGrandChild->left;
	rightGrandChild->right = leftChild;
	
	//RotateRight(p)
	p->left = rightGrandChild->right;
	rightGrandChild->right = p;
	
	updateHeight(p);
	
	*root = rightGrandChild;
	
	printf("[No desbalanceado: %d]\n", p->ra);
	printf("[Rotacao: DD]\n");
	printf("[x=%d y=%d z=%d]\n", leftChild->ra, rightGrandChild->ra, p->ra);
}

void rotateRL (avlNode **root) //DE
{
	avlNode *p = *root;
	avlNode *rightChild = p->right;
	avlNode *leftGrandChild = rightChild->left;
	
	//rotateRight(rightChild)
	rightChild->left = leftGrandChild->right;
	leftGrandChild->right = rightChild;
	
	//rotateLeft(p)
	p->right = leftGrandChild->left;
	leftGrandChild->left = p;
	
	updateHeight(p);
	
	*root = leftGrandChild;
	
	printf("[No desbalanceado: %d]\n", p->ra);
	printf("[Rotacao: DE]\n");
	printf("[x=%d y=%d z=%d]\n", p->ra, leftGrandChild->ra, rightChild->ra);
}

void avlInsert (avlNode **root, int ra, int nota)
{
	avlNode *tree;
	int rotate = 0;
	if (!(*root)) {
		tree = malloc(sizeof(avlNode));
		if (!tree) return;
		
		tree->ra = ra;
		tree->nota = nota;
		tree->right = NULL;
		tree->left = NULL;
		tree->height = 0;
	}
	else {
		tree = *root;
		if (ra == (*root)->ra) return;
	
	
		if (ra < tree->ra) {
			avlInsert(&tree->left, ra, nota);
		
			if (balanceFactor(tree) == 2) {
				rotate = 1;
				if (ra < tree->left->ra) rotateLL(&tree);
				else					 rotateLR(&tree);
			}
			else {
				updateHeight(tree);
			}
		}
		else {
			avlInsert(&tree->right, ra, nota);
			if (balanceFactor(tree) == -2) {
				rotate = 1;
				if (ra > tree->right->ra) rotateRR(&tree);
				else					  rotateRL(&tree);
			}
			else {
				updateHeight(tree);
			}
		}
	}
	
	if (!rotate) printf("[Ja esta balanceado]\n");
	
	*root = tree;
}

avlNode *buscaArvore (avlNode *arvore, int ra, int *comparacoes)
{
    avlNode *aux = arvore;
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

void inOrder(avlNode *node)
{
	if (!node) return;
	
	inOrder(node->left);
	printf("%d ", node->ra);
	inOrder(node->right);
}

void freeAvl (avlNode *node)
{
	if (!node) return;
	freeAvl(node->right);
	freeAvl(node->left);
	free(node);
}

int main ()
{
	char input;
	int ra, nota, comparacoes;
	avlNode *arvore = NULL;
	avlNode *busca = NULL;
	
	scanf("%c\n", &input);
	while (input != 'P' && input != 'p') {
		switch (input) {
			case 'I':
			case 'i':
				scanf("%d %d", &ra, &nota);
				avlInsert(&arvore, ra, nota);
				break;
			
			case 'R':
			case 'r':
				printf("REMOCAO\n");
				break;
			
			case 'B':
			case 'b':
				busca = buscaArvore(arvore, ra, &comparacoes);
				
				if (!busca) nota = -1;
				else 		nota = busca->nota;
				
				printf("C=%d Nota=%d\n", comparacoes, nota);
				break;
			
			case 'A':
			case 'a':
				if (!arvore) printf("A=-1\n");
				else		 printf("A=%d\n", arvore->height);
				break;
		}
		printf("[");
		inOrder(arvore);
		printf("]\n");
		scanf("%c\n", &input);
	}
	
	return 0;
}




















