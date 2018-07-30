
//  Joanderson Gonçalves Santos
//  Tayná Valverde Rosa
//  Rafael Baretto Serejo Farias

#include <stdio.h>
#include "avl.h"

int main(){
  int  cod_cli, valor,op,aux;
  char f,ord;
  //int a,b,c;
  no* n=NULL;
  arv* T=NULL;
  T=criar_arv();
  while(1){
    scanf(" %c",&f);

    if(f=='i'){
      scanf(" %d %d %d",&cod_cli,&op,&valor);
      elaborar_enviar_no(T,cod_cli,valor,op);
      continue;
    }
    if(f=='c'){
      scanf(" %d",&cod_cli);
      aux=consulta_no(T,cod_cli);
      if(aux==0){ //não existe
        printf("nao ");
      }
      printf("existe no com chave: %d\n",cod_cli);
      continue;
    }
    if(f=='p'){
      scanf(" %c",&ord);
      n=raiz_arv(T);
      if(ord=='c'){
        impressao_crescente(n);
      }
      else{
        impressao_decrescente(n);
      }
      continue;
    }
    if(f=='n'){
      scanf(" %d",&aux);
      n=raiz_arv(T);

      impressao_nivel(n,aux);
      continue;
    }
    if(f=='h'){
      n=raiz_arv(T);
      aux=altura_no(n);
      printf("%d\n",aux);
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
  }
  destruir_arv(T);
  n=NULL;
  T=NULL;
  return 0;
}
