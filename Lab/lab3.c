#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node{
  int RA;
  node *next;
};

typedef struct tree tree;
struct tree{
  int value;
  tree *pLeft, *pRight;
};

// Funcoes para a arvore de busca binaria
tree *buscaArvore(tree *t, int value, int *count){
  if(!t) return NULL;
  (*count)++;
  if(value == t->value) return t;
  if(value < t->value) buscaArvore(t->pLeft, value, count);
  else buscaArvore(t->pRight, value, count);
}

tree *insereArvore(tree *t, int value){
  if(!t){   // cria o nodo inicial na ABB
    tree *tmp = malloc(sizeof(tree));
    if(tmp){
      tmp->value = value;
      tmp->pRight = tmp->pLeft = NULL;
    }
    return tmp;
  }
  if(value < t->value)
    t->pLeft = insereArvore(t->pLeft, value);
  else if(value > t->value)
    t->pRight = insereArvore(t->pRight, value);
  else
    t->value = value;
  return t;
}

// Funcoes para a lista ligada em ORDEM CRESCENTE
node *insereLista(node *seq, int RA){
  node *cur = seq, *prev = NULL;
  node *tmp = malloc(sizeof(node));
  if(!tmp) return NULL;

  if(!cur){
    tmp->RA = RA;
    tmp->next = NULL;
    return tmp;
  }
  while(cur && cur->RA < RA){
    prev = cur;
    cur = cur->next;
  }

  if(!cur){  // Chegou no ultimo elemento
    prev->next = tmp;
    tmp->next = NULL;
    tmp->RA = RA;
    return seq;
  }
  else if (!prev){ // parou no primeiro elemento
    tmp->next = cur;
    tmp->RA = RA;
    return tmp;
  }
  else{
    prev->next = tmp;
    tmp->RA = RA;
    tmp->next = cur;
    return seq;
  }
}

node *buscaLista(node *seq, int RA, int *count){
  while(seq){
    (*count)++;
    if(!seq || seq->RA >= RA) break;
    seq = seq->next;
  }
  //if(!seq)  (*count)--;
  return NULL;
}

void printList(node *seq){
  printf("Sequencia: ");
  while(seq){
    printf("%d ", seq->RA);
    seq = seq->next;
  }
  printf("\n");
}

int main(){
  char inst = 'A';
  int RA = '1', c_ln = 0, c_tn = 0;
  tree *t = NULL;
  node *seq = NULL;

  while(inst!='P' || RA !=0){
    scanf("%c %d", &inst, &RA);
    if(inst == 'I'){
      t = insereArvore(t, RA);
      seq = insereLista(seq, RA);
    }
    else if(inst == 'B'){
      buscaArvore(t, RA, &c_tn);
      buscaLista(seq, RA, &c_ln);
      printf("L=%d A=%d\n", c_ln, c_tn);
      c_tn = c_ln = 0;
    }
  }

  return 0;
}
