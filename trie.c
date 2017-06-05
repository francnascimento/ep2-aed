#include <stdbool.h>   // variaveis bool assumem valores "true" ou "false"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aux{

  struct aux **lista;
  char letra;
} NO;

void iniciaArv(NO *raiz){
  raiz->lista = (NO **) malloc(26*sizeof(NO));
}

void adicionaNo(NO *raiz, char letraN[]){
  int i, indice;
  NO *aux = raiz;
  for(i = 0; i<strlen(letraN); i++){
    indice = letraN[i] - 97;
    if( !(aux->lista[indice]) ){
      aux->lista[indice] = (NO*) malloc(sizeof(NO));
      aux->lista[indice]->letra = letraN[i];
      aux->lista[indice]->lista = (NO **) malloc(26*sizeof(NO));
    }
    aux = aux->lista[indice];
  }
}

void imprime(NO *arv){
  int i;
  for(i = 0; i<26; i++){
    if(arv->lista[i]) {
      printf("%c", arv->lista[i]->letra);
      imprime(arv->lista[i]);
    }
  }
}

void main(){
  NO *arv = (NO*) malloc(sizeof(NO));
  iniciaArv(arv);
  adicionaNo(arv, "foi");
  adicionaNo(arv, "fodasse");
  adicionaNo(arv, "gabriel");

  printf("impressao\n");
  imprime(arv);
  printf("\n");
}
