#include <stdbool.h>   // variaveis bool assumem valores "true" ou "false"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct auxi{
  char **palavras;
} TEXTO;

typedef struct aux{

  struct aux **lista;
  char letra;
} NO;


void iniciaArv(NO *raiz){
  raiz->lista = (NO **) malloc(26*sizeof(NO));
}


void adicionaTexto(NO *raiz, char *text){
  int i, indice;
  NO *aux = raiz;

  for(i = 0; i<strlen(text); i++){
    if(text[i] == ' '){
      aux = raiz;
      continue;
    }
    indice = text[i] - 97;
    if( !(aux->lista[indice]) ){
      aux->lista[indice] = (NO*) malloc(sizeof(NO));
      aux->lista[indice]->letra = text[i];
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

void visu(NO *arv){
  int i;
  for(i = 0; i<26; i++){
    if(arv->lista[i]){
      printf("%c", arv->lista[i]->letra);
    }
  }
  printf("\n");
  for(i = 0; i<26; i++){
    if(arv->lista[i]){
      visu(arv->lista[i]);
    }
  }
}





void main(){
  NO *arv = (NO*) malloc(sizeof(NO));
  iniciaArv(arv);


  char *text = "forget your lust and the rich men gold";
  char *text2 = "all that you need is in your soul";
  adicionaTexto(arv, text);
  adicionaTexto(arv, text2);
  imprime(arv);
  printf("\n");
  //visu(arv);

}
