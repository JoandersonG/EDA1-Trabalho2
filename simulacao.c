#include <stdio.h>
#include "avl.h"

int main(){
  int nn, cod_cli, valor,op,aux;
  char f,ord;
  //int a,b,c;
  no* n=NULL;
  arv* T=NULL;
  T=criar_arv();
  scanf("%d",&nn);
  //while ((getchar()) != '\n');
  for (int i = 0; i < nn; i++) {
    while ((getchar()) != '\n');
    scanf("%c",&f);

/*
    switch(f){
      case 'i':
        scanf("%d%d%d",&cod_cli,&op,&valor);
        elaborar_enviar_no(T,cod_cli,valor,op);
        break;

      case 'c':
        scanf("%d",&cod_cli);
        aux=consulta_no(T,cod_cli);
        if(aux==0){ //não existe
          printf("nao ");
        }
        printf("existe no com chave: %d\n",cod_cli);
        break;
      case 'p':
        scanf("%c",&ord);
        n=raiz_arv(T);
        if(ord=='c'){
          impressao_crescente(n);
        }
        else{
          impressao_decrescente(n);
        }
        break;
      case 'n':
        scanf("%d",&aux);
        printf("Teste n, ok\n");
        n=raiz_arv(T);
        impressao_nivel(n,aux);
        break;
      case 'h':
        n=raiz_arv(T);
        aux=altura_no(n);
        printf("%d\n",aux);
        break;
      case 'f':
        imprimir_relatorio(T);
    }
*/

    if(f=='i'){
    //  printf("Entrou em i\n");
    //  while ((getchar()) != '\n');
      scanf("%d%d%d",&cod_cli,&op,&valor);
    //  printf("Entrou em i\n");
      elaborar_enviar_no(T,cod_cli,valor,op);

      continue;
    }
    if(f=='c'){
      //printf("Entrou no c\n");
    //  while ((getchar()) != '\n');
      scanf("%d",&cod_cli);

      aux=consulta_no(T,cod_cli);
      if(aux==0){ //não existe
        printf("nao ");
      }
      printf("existe no com chave: %d\n",cod_cli);
      continue;
    }
    if(f=='p'){
    //  while ((getchar()) != '\n');
      scanf("%c",&ord);

      n=raiz_arv(T);
      if(ord=='c'){
        impressao_crescente(n);
      }
      else{
        impressao_decrescente(n);
      }
      //printf("Entrei no p\n");
      continue;
    }
    if(f=='n'){
    //  while ((getchar()) != '\n');
      //printf("Entrei no n\n");
      scanf("%d",&aux);
      //printf("Entrei no n\n");
      n=raiz_arv(T);
      //printf("Entrei no n\n");
      impressao_nivel(n,aux);
      //printf("Entrei no n\n");
      continue;
    }
    if(f=='h'){
      n=raiz_arv(T);
      aux=altura_no(n);
      printf("%d\n",aux);
      continue;
    }
    if(f=='f'){
      imprimir_relatorio(T);
    }


  }
  n=NULL;
  T=NULL;
  return 0;
  //desalocar tudo!!!
}
