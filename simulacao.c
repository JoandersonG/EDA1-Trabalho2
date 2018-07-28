#include <stdio.h>
#include "avl.h"

int main(){
  int  nn,cod_cli, valor,op,aux;
  char f,ord,lixo;
  //int a,b,c;
  no* n=NULL;
  arv* T=NULL;
  T=criar_arv();

//  scanf("%c",&f);
//scanf("%d",&nn);

//  for (int i = 0; i < nn; i++) {
  while(1){
    //while ((getchar()) != '\n');
    scanf(" %c",&f);

    if(f=='i'){
    //  printf("Entrou em i, %d\n",cod_cli);
    //  while ((getchar()) != '\n');
      scanf(" %d %d %d",&cod_cli,&op,&valor);
    //  printf("Entrou em i, %d\n",cod_cli);
      elaborar_enviar_no(T,cod_cli,valor,op);
    //  printf("Entrou em i, %d\n",cod_cli);
      continue;
    }
    if(f=='c'){
      //printf("Entrou no c\n");
    //  while ((getchar()) != '\n');
      scanf(" %d",&cod_cli);

      aux=consulta_no(T,cod_cli);
      if(aux==0){ //não existe
        printf("nao ");
      }
      printf("existe no com chave: %d\n",cod_cli);
      continue;
    }
    if(f=='p'){
      scanf(" %c %c",&lixo,&ord);
      n=raiz_arv(T);
      if(ord=='c'){
        impressao_crescente(n);
      }
      else{
        impressao_decrescente(n);
      }
      printf("\n");

      //printf("Entrei no p\n");
      continue;
    }
    if(f=='n'){
    //  while ((getchar()) != '\n');
      //printf("Entrei no n\n");
      scanf(" %d",&aux);
    //  printf("Aux: %d\n",aux);
      n=raiz_arv(T);

      impressao_nivel(n,aux);
      printf("\n");
      continue;
    }
    if(f=='h'){

      n=raiz_arv(T);
      aux=altura_no(n);
      printf(" %d\n",aux);

      continue;
    }
    if(f=='r'){
      scanf(" %d",&aux);
      n=raiz_arv(T);
      remover_cliente(T,n,aux);
      continue;
    }
    if(f=='f'){
      imprimir_relatorio(T);
      break;
    }
  while ((getchar()) != '\n');
  //  scanf("%c",&f);
  //  while ((getchar()) != '\n');
  }
  destruir_arv(T);
  n=NULL;
  T=NULL;
  return 0;
  //desalocar tudo!!!
}
