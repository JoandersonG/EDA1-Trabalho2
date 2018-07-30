
//  Joanderson Gonçalves Santos
//  Tayná Valverde Rosa
//  Rafael Baretto Serejo Farias


#ifndef avl_h
#define avl_h
#include "avl.h"

typedef struct arvore arv;
typedef struct node no;

arv* criar_arv();
int elaborar_enviar_no(arv* T,int cod_cli,int valor,int op);
no* busca(no* raiz,int cod_cli);
no* inserir_no(arv *T, no*x, no*z);
no* balanceamento(arv *T,no *x);
no* rot_dupla_esq(arv *T, no* x);
no* rot_dupla_dir(arv *T, no* x);
no* rot_simples_esq(arv* T, no*x);
no* rot_simples_dir(arv* T, no*x);
int atualiza_altura(arv* T,no* x);
int altura_no(no* raiz);
int balanco(no* x);
int consulta_no(arv* T,int cod_cli);
int impressao_nivel(no* raiz,int nivel);
int caminho_para_raiz(no* raiz);
int impressao_crescente(no* raiz);
int impressao_decrescente(no* raiz);
no* raiz_arv(arv* T);
int remover_cliente(arv* T,no* x,int cod_cli);
no* remover_avl(arv* T,no* x,int cod_cli);
int total_nos(no* raiz);
no* minimo(no *x);
int transplante(arv* T,no* z, no* y);
int imprimir_relatorio(arv *T);
int destruir_arv(arv* T);
#endif
