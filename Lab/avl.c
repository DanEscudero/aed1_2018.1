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

int height (avlNode *node)
{
	if (!node) return -1;
	return max(height(node->left), height(node->right))+1;
}

void updateHeight(avlNode *n) {
	if (!n) return;
	int hl = (n->left)  ? n->left->height  : -1;
	int hr = (n->right) ? n->right->height : -1;
	n->height =  (hl > hr ? hl : hr) + 1 ;
}

int balanceFactor (avlNode *node)
{
	if (!node) return 0;
	int hleft = (node->left) ? node->left->height : -1;
	int hright = (node->right) ? node->right->height : -1;
	return hleft - hright;
}

avlNode *minValue (avlNode *tree)
{
	avlNode *aux = tree;
	while (aux->left)
		aux = aux->left;
	
	return aux;
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
	printf("[x=%d y=%d z=%d]\n", leftChild->left->ra, leftChild->ra, p->ra);
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
	printf("[x=%d y=%d z=%d]\n", p->ra, rightChild->ra, rightChild->right->ra);
}

void rotateLR (avlNode **root) //DD
{
	avlNode *p = *root;
	avlNode *leftChild = p->left;
	avlNode *rightGrandChild = leftChild->right;
	
	//rotateLeft(leftChild)
	leftChild->right = rightGrandChild->left;
	rightGrandChild->left = leftChild;
	
	//rotateRight(p)
	p->left = rightGrandChild->right;
	rightGrandChild->right = p;
	
	updateHeight(p);
	updateHeight(leftChild);
	updateHeight(rightGrandChild);
	
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
	updateHeight(rightChild);
	updateHeight(leftGrandChild);
	
	*root = leftGrandChild;
	
	printf("[No desbalanceado: %d]\n", p->ra);
	printf("[Rotacao: DE]\n");
	printf("[x=%d y=%d z=%d]\n", p->ra, leftGrandChild->ra, rightChild->ra);
}

/* Retorna 1 se houve rotacao, 0 se nao */
int avlInsert (avlNode **root, int ra, int nota)
{
	avlNode *tree;
	int rotate = 0;
	if (!(*root)) {
		tree = malloc(sizeof(avlNode));
		if (!tree) return 0;
		
		tree->ra = ra;
		tree->nota = nota;
		tree->right = NULL;
		tree->left = NULL;
		tree->height = 0;
	}
	else {
		tree = *root;
		if (ra == (*root)->ra) return 0;
	
	
		if (ra < tree->ra) {
			rotate = avlInsert(&tree->left, ra, nota);
		
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
			rotate = avlInsert(&tree->right, ra, nota);
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
	
	*root = tree;
	return rotate;
}

avlNode *buscaArvore (avlNode *arvore, int ra, int *comparacoes)
{
    avlNode *aux = arvore;
	*comparacoes = 0;
	
    while (aux) {
		(*comparacoes)++;
        if (ra > aux->ra)
            aux = aux->right;
		
        else if (ra < aux->ra)
            aux = aux->left;
		
        else return aux;
    }
	
    return aux;
}

void postOrder(avlNode *node)
{
	if (!node) return;
	
	postOrder(node->left);
	postOrder(node->right);
	printf("%d ", node->ra);
}

void inOrder(avlNode *node)
{
	if (!node) return;
	
	inOrder(node->left);
	printf("%d ", node->ra);
	inOrder(node->right);
}

void printAvl (avlNode *node)
{
	printf("(");
	if (node) {
		printf("%d ", node->ra);
		printAvl(node->left);
		printAvl(node->right);
	}
	printf(")");
}

void freeAvl (avlNode *node)
{
	if (!node) return;
	freeAvl(node->right);
	freeAvl(node->left);
	free(node);
}

/* NAO FUNCIONA EM TODOS OS TESTES, REVER */
avlNode* deleteNode(avlNode *root, int ra, int *rotacoes)
{
	*rotacoes = 0;
	if (!root) return root;
	
	else if (ra < root->ra)
		root->left = deleteNode(root->left, ra, rotacoes);
	
	else if (ra > root->ra)
		root->right = deleteNode(root->right, ra, rotacoes);
	
	//Chega aqui quando root->ra == ra
	else {
		//caso 1: sem filhos
		if (!root->left && !root->right) {
			free(root);
			root = NULL;
		}
		//caso 2.1: filho na direita
		else if (!root->left) {
			avlNode *aux = root;
			root = root->right;
			free(aux);
		}
		//caso 2.2: filho na esquerda
		else if (!root->right) {
			avlNode *aux = root;
			root = root->left;
			free(aux);
		}
		//caso 3: dois filhos
		else {
			avlNode *aux = minValue(root->right);
			root->ra = aux->ra;
			root->nota = aux->nota;
			root->right = deleteNode(root->right, aux->ra, rotacoes);
		}
	}
	if (!root) return root;
	
	updateHeight(root);
	
	int balance = balanceFactor(root);
	
	if (balance > 1 && balanceFactor(root->left) >= 0) {
		*rotacoes = 1;
		rotateLL(&root);
	}
	
	else if (balance > 1 && balanceFactor(root->left) < 0) {
		*rotacoes = 1;
		rotateLR(&root);
	}
	
	else if (balance < -1 && balanceFactor(root->right) <= 0) {
		*rotacoes = 1;
		rotateRR(&root);
	}
	
	else if (balance < -1 && balanceFactor(root->right) > 0) {
		*rotacoes = 1;
		rotateRL(&root);
	}
	
	return root;
}

int main ()
{
	int i = 0;
	char input;
	int ra, nota, comparacoes, rotacoes = 0;
	avlNode *arvore = NULL;
	avlNode *busca = NULL;
	
	scanf("%c", &input);
	while (input != 'P' && input != 'p') {
		switch (input) {
			case 'I':
			case 'i':
				scanf("%d %d", &ra, &nota);
				if (!avlInsert(&arvore, ra, nota))
					printf("[Ja esta balanceado]\n");
				break;
			
			case 'R':
			case 'r':
				scanf ("%d", &ra);
				arvore = deleteNode(arvore, ra, &rotacoes);
				if (!rotacoes)
					printf("[Ja esta balanceado]\n");
				break;
			
			case 'B':
			case 'b':
				scanf ("%d", &ra);
				busca = buscaArvore(arvore, ra, &comparacoes);
				
				if (!busca) nota = -1;
				else {
					nota = busca->nota;
					ra = busca->ra;
				}
				
				printf("C=%d Nota=%d\n", comparacoes, nota);
				busca = NULL;
				break;
			
			case 'A':
			case 'a':
				if (!arvore) printf("A=-1\n");
				else		 printf("A=%d\n", arvore->height);
				break;
		}
		scanf("\n%c", &input);
	}
	printf("[");
	postOrder(arvore);
	printf("]\n");
	freeAvl(arvore);
	
	return 0;
}










