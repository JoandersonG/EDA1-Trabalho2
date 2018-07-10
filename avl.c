#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

struct node{
  struct node *pai;
  struct node *dir;
  struct node *esq;
  int cod_cli;
  int saldo;
  int qtd_op;
  int altura;
};
struct arvore{
  struct node* raiz;
  //int tamanho;//quantidade de nós
  int alt;//altura
};

arv* criar_arv(){
  arv *T=(arv*)malloc(sizeof(arv));
  if(T==NULL){
    printf("Erro 1 em criar_arv\n");
  }
  return T;
}
int elaborar_enviar_no(arv* T,int cod_cli,int valor,int op){
  if(T==NULL){
    printf("Erro 1 em criar_no\n");
    return -1;
  }
  no* aux=busca(T->raiz,cod_cli);
  if(aux!=NULL){
    aux->qtd_op++;
    if(op==1){//saque
      aux->saldo-=valor;
    }
    else{
      aux->saldo+=valor;
    }
    return 1;
  }
  no* n=(no*)malloc(sizeof(no));
  n->cod_cli=cod_cli;
  if(op==1){//saque
    n->saldo=0-valor;
  }
  else{//depósito
    //0800 727 9096 advocacia Elinatti
    n->saldo=valor;
  }
  n->qtd_op=1;
  n->pai=NULL;
  n->esq=NULL;
  n->dir=NULL;
  n->altura=1;
  inserir_no(T,T->raiz,n);
  return 1;
}
no* busca(no* raiz,int cod_cli){
  if(raiz->cod_cli==cod_cli){
    return raiz;
  }
  if(cod_cli>raiz->cod_cli){
    return busca(raiz->dir,cod_cli);
  }
  else{
    return busca(raiz->esq,cod_cli);
  }
}
no* inserir_no(arv *T, no*x, no*z){
  if(T=NULL){
    printf("erro 1 em inserir_no\n");
    no* erro=NULL;
    return erro;
  }
  if(x==NULL){
    //significa que a arv está vazia
    T->raiz=z;
    return x;
  }
  if(z->cod_cli < x->cod_cli){
    if(x->esq==NULL){
      x->esq=z;
      z->pai=x;
      z->altura=1;
    }
    else{
      x->esq=inserir_no(T,x->esq,z);
    }
  }
  else{
    if(x->dir==NULL){
      x->dir=z;
      z->pai=x;
      z->altura=1;
    }
    else{
      x->dir=inserir_no(T,x->dir,z);
    }
  }
  atualiza_altura(T,x);
  if(balanco(x)==2 || balanco(x)==-2){
    balanceamento(T,x);
  }
  return x;
}
int balanceamento(arv *T,no *x){
  if(T==NULL){
    printf("Erro 1 em balanceamento\n");
    return -1;
  }
  if(x==NULL){
    printf("Erro 2 em balanceamento\n");
    return -1;
  }
  if(balanco(x)==-2){
    no* y=x->dir;
    if(balanco(y)==1){
      x=rot_dupla_esq(T,x);
    }
    else{
      x=rot_simples_esq(T,x);
    }
  }
  else{
    no* y=x->esq;
    if(balanco(y)==-1){
      x=rot_dupla_dir(T,x);
    }
    else{
      x=rot_simples_dir(T,x);
    }
  }
  return 1;
}
no* rot_dupla_esq(arv *T, no* x){
  if(T==NULL){
    printf("Erro 1 em rot_dupla_esq\n");
  }
  no* y=x->dir;
  y=rot_simples_dir(T,y);
  x=rot_simples_esq(T,x);
  return x;
}
no* rot_dupla_dir(arv *T, no* x){
  if(T==NULL){
    printf("Erro 1 em rot_dupla_dir\n");
  }
  no* y=x->esq;
  y=rot_simples_esq(T,y);
  x=rot_simples_dir(T,x);
  return x;
}
no* rot_simples_esq(arv* T, no*x){
  no* y=NULL;
  if(T==NULL){
    printf("Erro 1 em rot_simples_esq\n");
    return y;
  }
  y=x->dir;
  x->dir=y->esq;
  if(y->esq!=NULL){
    y->esq->pai=x;
  }
  y->pai=x->pai;
  if(x->pai==NULL){
    T->raiz=y;
  }
  else{
    if(x==x->pai->esq){
      x->pai->esq=x;
    }
    else{
      x->pai->dir=x;
    }
  }
  y->esq=x;
  x->pai=y;//?????
  atualiza_altura(T,x);
  atualiza_altura(T,y);
  return x;//ou y?????
}
no* rot_simples_dir(arv* T, no*x){
  no* y=NULL;
  if(T==NULL){
    printf("Erro 1 em rot_simples_dir\n");
    return y;
  }
  y=x->esq;
  x->esq=y->dir;
  if(y->dir!=NULL){
    y->dir->pai=x;
  }
  y->pai=x->pai;
  if(x->pai==NULL){
    T->raiz=y;
  }
  else{
    if(x==x->pai->dir){
      x->pai->dir=x;
    }
    else{
      x->pai->esq=x;
    }
  }
  y->dir=x;
  x->pai=y;//?????
  atualiza_altura(T,x);
  atualiza_altura(T,y);
  return x;//ou y???
}
int atualiza_altura(arv* T,no* x){
  if(T==NULL){
    printf("Erro 1 em atualiza_altura\n");
    return 0;
  }
  x->altura=altura_no(x);
  return 1;
}
int altura_no(no* raiz){
  if(raiz==NULL){
    return 0;
  }
  int altEsq=altura_no(raiz->esq);
  int altDir=altura_no(raiz->dir);
  if(altEsq>altDir){
    return altEsq+1;
  }
  return altDir+1;
}
int balanco(no* x){
  if(x==NULL){
    return 0;
  }
  int altEsq=0,altDir=0;
  if(x->esq!=NULL){
    altEsq=x->esq->altura;
  }
  if(x->dir!=NULL){
    altDir=x->dir->altura;
  }
  return altDir-altEsq;
}
int consulta_no(arv* T,int cod_cli){
  if(T==NULL){
    printf("Erro 1 em consulta_no\n");
    return -1;
  }
  no* aux=busca(T->raiz,cod_cli);
  if(aux==NULL){
    //não existe
    return 0;
  }
}
int impressao_nivel(no* raiz,int nivel){
  if(raiz==NULL){
    return 1;
  }
  if(caminho_para_raiz(raiz)==nivel-1){//-1??????
    printf("%d\n",raiz->cod_cli);
    return 1;
  }
  impressao_nivel(raiz->esq,nivel);
  impressao_nivel(raiz->dir,nivel);
  return 1;
}
int caminho_para_raiz(no* raiz){
  if(raiz==NULL){
    return 0;
  }
  int cont=1;
  while(raiz->pai!=NULL){
    cont++;
  }
  return cont;
}
int impressao_crescente(no* raiz){
  if(raiz==NULL){
    return 1;
  }
  impressao_crescente(raiz->esq);
  printf("%d\n",raiz->cod_cli);
  impressao_crescente(raiz->dir);
  return 1;
}
int impressao_decrescente(no* raiz){
  if(raiz==NULL){
    return 1;
  }
  impressao_decrescente(raiz->dir);
  printf("%d\n",raiz->cod_cli);
  impressao_decrescente(raiz->esq);
  return 1;
}
no* raiz_arv(arv* T){
  //necessária pois não posso usar T->raiz no main
  if(T==NULL){
    return  NULL;
  }
  return T->raiz;
}
int total_nos(no* raiz){
  if(raiz==NULL){
    return 0;
  }
  int dir=total_nos(raiz->dir);
  int esq=total_nos(raiz->esq);
  return dir+esq+1;
}
int remover_no(arv *T,no *z){
  if(T==NULL){
    printf("Erro 1 em remover_no\n");
    return -1;
  }
  if(z->esq==NULL){
    transplante(T,z,z->dir);
  }
  else if(z->dir==NULL){
    transplante(T,z,z->esq);
  }
  else{
    no* y;
    y=minimo(z->dir);
    if(y->pai!=z){
      transplante(T,y,y->dir);
      y->dir=z->dir;
      y->dir->pai=y;
    }
    transplante(T,z,y);
    y->esq=z->esq;
    y->esq->pai=y;
  }
  free(z);
  return 1;
}
no* minimo(no *x){
  if(x==NULL){
    no* n=NULL;
    return n;
  }
  while(x->esq!=NULL){
    x=x->esq;
  }
  return x;
}
int transplante(arv* T,no* z, no* y){
  if(z->pai==NULL){
    T->raiz=y;
  }
  else if(z==z->pai->esq){
    z->pai->esq=y;
  }
  else{
    z->pai->dir=y;
  }
  if(y!=NULL){
    y->pai=z->pai;
  }
  return 1;
}
int imprimir_relatorio(arv *T){
  if(T==NULL){
    printf("Erro 1 em imprimir_relatorio\n");
    return 1;
  }
  printf("“-+- Inicio relatorio -+-\n");
  int aux=total_nos(T->raiz);
  printf("%d\n",aux);
  for (int i = 0; i < aux; i++) {
    printf("%d %d %d\n",T->raiz->cod_cli,T->raiz->qtd_op,T->raiz->saldo);
    remover_no(T,T->raiz);
  }
  printf("-+- Fim relatorio -+-\n");
}
int destruir_arv(arv* T){
  if(T==NULL){
    return 1;
  }
  while(total_nos(T->raiz)){
    remover_no(T,T->raiz);
  }
  free(T);
  return 1;
}