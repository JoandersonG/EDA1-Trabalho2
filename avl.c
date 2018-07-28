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
  T->raiz=NULL;
  T->alt=0;
  return T;
}
int elaborar_enviar_no(arv* T,int cod_cli,int valor,int op){
  if(T==NULL){
    printf("Erro 1 em criar_no\n");
    return -1;
  }
  no* aux=busca(T->raiz,cod_cli);
  if(aux!=NULL){
    //se já existe tal nó na árvore:
    aux->qtd_op++;
    if(op==1){//saque
      aux->saldo-=valor;
    }
    else{
      aux->saldo+=valor;
    }
    return 1;
  }
  //se não existe o nó ainda:
  no* n=(no*)malloc(sizeof(no));
  n->cod_cli=cod_cli;
  if(op==1){//saque
    n->saldo=0-valor;
  }
  else{//depósito
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
  if(raiz==NULL){
    return raiz;
  }
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


no* remover_avl(arv* T,no* x,int cod_cli){
  if(x==NULL){
    return x;
  }
  no* reg=NULL;
  no* aux=NULL;
  if(T->raiz->cod_cli==cod_cli && T->raiz->esq==NULL && T->raiz->dir==NULL){
    //só há a raiz e é ela q quero remover;
  //  printf("entrou aqui\n");
    reg=T->raiz;
    T->raiz=NULL;
    return reg;
  }
  if(x->cod_cli  >  cod_cli){
  //  printf("%d é maior que %d\n",x->cod_cli,cod_cli);
    reg=remover_avl(T,x->esq,cod_cli);
  }
  else if(x->cod_cli  <  cod_cli){
  //  printf("%d é menor que %d\n",x->cod_cli,cod_cli);
    reg=remover_avl(T,x->dir,cod_cli);
  }
  else{// encontrei
    reg=x;
  //  printf("encontrei %d\n",x->cod_cli);
    if(x->dir==NULL){
      if(x->esq==NULL){//folha
    //    printf("É uma folha\n");
        if(x->pai->esq==x){
          x->pai->esq=NULL;
        }
        else{
          x->pai->dir=NULL;
        }
        x->pai=NULL;
      }
      else{
        //sustitui x por x->esq:
    //    printf("Esquerda de %d não é NULL\n",x->cod_cli);
        x->esq->pai=x->pai;
        if(x->pai!=NULL){
          if(x->pai->esq==x){
            x->pai->esq=x->esq;
          }
          else{
            x->pai->dir=x->esq;
          }
        }
        else{
          //é raiz
          T->raiz=x->esq;
        }
        x->esq=NULL;
        x->pai=NULL;
      }

      /////////////////////////////////////////////////////
  /*    else if(x->pai->esq==x){//sem filhos à direita
        x->pai->esq=x->esq;
      }
      else{
        x->pai->dir=x->esq;
      }
      printf("Não tem filhos à direita\n");
      x->esq->pai=x->pai;
      x->esq=NULL;
      x->pai=NULL;
  */    //==================================================
    }
    else if(x->esq==NULL){
      //sem filhos à esquerda e tem à dir
    //  printf("%d Sem filhos à esq e possui à direita\n",x->cod_cli);
      if(x->pai!=NULL){
        if(x->pai->esq==x){
          x->pai->esq=x->dir;
        }
        else{
          x->pai->dir=x->dir;
        }
      }
      else{
        T->raiz=x->dir;
      }
      x->dir->pai=x->pai;
      x->dir=NULL;
      x->pai=NULL;
    }
    else{//possui dois filhos:
  //    printf("%d Possui dois filhos\n",x->cod_cli);
      x=x->dir;

      while(x->esq!=NULL){
        x=x->esq;
      }//tenho o endereço do sucessor de x em x e endereço de x em reg;

      if(reg->pai!=NULL){
        if(reg->pai->esq==reg){
          reg->pai->esq=x;
        }
        else{
          reg->pai->dir=x;
        }
      }
      //dois casos:
      //1:
      if(x==reg->dir){//x é elemento à direita de reg
        x->pai=reg->pai;
        x->esq=reg->esq;
        if(x->esq!=NULL) x->esq->pai=x;
      }
      //2:
      else{//x é elemento de reg, com mais de um nível de diferença
        aux=x->pai;
        x->pai->esq=x->dir;
        if(x->dir!=NULL) x->dir->pai=x->pai;
        x->pai=reg->pai;
        x->esq=reg->esq;
        if(x->esq!=NULL) x->esq->pai=x;
        x->dir=reg->dir;
        reg->dir->pai=x;
        reg->esq->pai=x;
      }
      if(x->pai==NULL){
        //é raiz
        T->raiz=x;
      }
      reg->esq=NULL;
      reg->dir=NULL;
      reg->pai=NULL;

      while (aux!=NULL && aux->pai!=NULL && aux==aux->pai->esq) {
      //  printf("Entrou no while\n");
        atualiza_altura(T,aux);
        if(balanco(aux)==2 || balanco(aux)==-2){
          aux=balanceamento(T,aux);
        }
        aux=aux->pai;
      }//saio no antigo filho do nó removido
      atualiza_altura(T,aux);
      if(balanco(aux)==2 || balanco(aux)==-2){
        aux=balanceamento(T,aux);
      }
/*
*/
      ////////////////////////////////////////////////////
/*      aux=x->pai;
      if(x->pai->esq==x){
        x->pai->esq=x->dir;
        if(x->dir!=NULL)   x->dir->pai=x->pai;
      }

      //coloco o sucessor no lugar do reg:
      if(reg->dir!=x){
        x->dir=reg->dir;
        reg->dir->pai=x;
      }
      x->pai=reg->pai;
      if(reg->pai!=NULL){
        if(reg->pai->esq==reg){
          reg->pai->esq=x;
        }
        else{
          reg->pai->dir=x;
        }
      }
      x->esq=reg->esq;
      reg->esq->pai=x;
      reg->esq=NULL;
      reg->dir=NULL;
      reg->pai=NULL;
*/
      //balancear... e altura e tals
    }
  }
  //printf("Altura de %d: %d\n",x->cod_cli,x->altura);
  atualiza_altura(T,x);
  //printf("Altura de %d: %d\n",x->cod_cli,x->altura);
  //printf("Altura de %d: %d\n",x->cod_cli,x->altura);
  if(balanco(x)==2 || balanco(x)==-2){
  //  printf("entrou em balanceamento com %d\n",x->cod_cli);
    x=balanceamento(T,x);
  }
  return reg;
}


no* inserir_no(arv *T, no*x, no*z){
  if(T==NULL){
    printf("erro 1 em inserir_no\n");
    no* erro=NULL;
    return erro;
  }
  //printf("Entrou aqui antes de dar erro\n");
  if(T->raiz==NULL){
    //significa que a arv está vazia
    //printf("árvore estava vazia, inseri %d\n",z->cod_cli);
    T->raiz=z;
    return x;
  }
  if(z->cod_cli < x->cod_cli){
    if(x->esq==NULL){
    //  printf("Entrou aqui com cod_cli: %d\n",z->cod_cli);
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
    x=balanceamento(T,x);
  }
  return x;
}
no* balanceamento(arv* T,no *x){
  if(x==NULL){
    printf("Erro 2 em balanceamento\n");
    return x;
  }
  no* y;
  if(balanco(x)==-2){
    y=x->dir;
    if(balanco(y)==1){
      x=rot_dupla_esq(T,x);
    }
    else{
      x=rot_simples_esq(T,x);
    }
  }
  else if(balanco(x)==2){
    y=x->esq;
    if(balanco(y)==-1){
      x=rot_dupla_dir(T,x);
    }
    else{
      x=rot_simples_dir(T,x);
    }
  }
  return x;//ou x?????


  //////////////////////////
  /*
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
  */
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
  else if(x==x->pai->esq){
      x->pai->esq=y;
    }
  else{
      x->pai->dir=y;
    }
  y->esq=x;
  x->pai=y;
  atualiza_altura(T,x);
  atualiza_altura(T,y);
  return y;
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
  else if(x==x->pai->dir){
      x->pai->dir=y;
    }
  else{
      x->pai->esq=y;
    }
  y->dir=x;
  x->pai=y;
  atualiza_altura(T,x);
  atualiza_altura(T,y);
  return y;
}
int atualiza_altura(arv* T,no* x){
  if(T==NULL){
    printf("Erro 1 em atualiza_altura\n");
    return 0;
  }
  if(x==NULL) return 0;
//  int alt=1;
  x->altura=altura_no(x);
/*  if(x->esq!=NULL)
    alt=x->esq->altura+1;
  if(x->dir!=NULL && x->dir->altura > alt){
    alt=x->dir->altura+1;
  }
  x->altura=alt;
  */
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
  return altEsq-altDir;
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

  return 1;
}
int impressao_nivel(no* raiz,int nivel){
  if(raiz==NULL){
    return 0;
  }
  int cont=0;
  if(caminho_para_raiz(raiz)==nivel){
    printf("%d ",raiz->cod_cli);
    cont++;
    return cont;
  }
  cont+=impressao_nivel(raiz->esq,nivel);
  cont+=impressao_nivel(raiz->dir,nivel);
  return cont;
}
int caminho_para_raiz(no* raiz){
  if(raiz==NULL){
    return 0;
  }
  int cont=1;
  while(raiz->pai!=NULL){
    raiz = raiz->pai;
    cont++;
  }
  return cont;
}
int impressao_crescente(no* raiz){
  if(raiz==NULL){
    return 1;
  }
  impressao_crescente(raiz->esq);
  printf("%d %d %d\n",raiz->cod_cli,raiz->qtd_op,raiz->saldo);
  impressao_crescente(raiz->dir);
  return 1;
}
int impressao_decrescente(no* raiz){
  if(raiz==NULL){
    return 1;
  }
  impressao_decrescente(raiz->dir);
  printf("%d %d %d\n",raiz->cod_cli,raiz->qtd_op,raiz->saldo);
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
/*
no* remover_avl(arv* T,no* x,int cod_cli){
  no* aux=NULL;
  if(x==NULL){
    return x;
  }
  if(cod_cli<x->cod_cli){
    x->esq=remover_avl(T,x->esq,cod_cli);
  }
  else if(cod_cli>x->cod_cli){
    x->dir=remover_avl(T,x->dir,cod_cli);
  }
  else{
    if(x->esq==NULL){
      aux=x;
      x=x->dir;
    }
    else if(x->dir==NULL){
      aux=x;
      x=x->esq;
    }
    else{
      no* y=minimo(x->dir);
      x->cod_cli=y->cod_cli;
      x->dir=remover_avl(T,x->dir,y->cod_cli);
    }
  }
  if(x==NULL){
    return x;
  }
  x->altura=x->esq->altura+1;
  if(x->dir->altura+1  >  x->altura){
    x->altura=x->dir->altura+1;
  }
  if(altura_no(x->esq)-altura_no(x->dir)==2 || altura_no(x->esq)-altura_no(x->dir)==-2){
    balanceamento(T,x);
  }
  return aux;
}
*/
int remover_cliente(arv* T,no* x,int cod_cli){
  if(T==NULL){
    printf("Erro 1 em remover_cliente\n");
    return -1;
  }
//  if(T->raiz->cod_cli==cod_cli)
  no* aux=busca(x,cod_cli);
  if(x==NULL){
    return 1;
  }
  aux = remover_avl(T,x,cod_cli);
  //if(x==T->raiz)
//  printf("removendo: %d\n",x->cod_cli);
  free(aux);
  aux = NULL;
  return 1;
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
  printf("-+- Inicio relatorio -+-\n");
  int aux=total_nos(T->raiz);
  printf("%d\n",aux);
  for (int i = 0; i < aux; i++) {
    printf("%d %d %d\n",T->raiz->cod_cli,T->raiz->qtd_op,T->raiz->saldo);
    remover_cliente(T,T->raiz,T->raiz->cod_cli);
  }
  printf("-+- Fim relatorio -+-\n");
  return 1;
}
int destruir_arv(arv* T){
  if(T==NULL){
    return 1;
  }
  while(total_nos(T->raiz)){
    remover_cliente(T,T->raiz,T->raiz->cod_cli);
  }
  free(T);
  return 1;
}
