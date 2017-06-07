#include <stdbool.h>   // variaveis bool assumem valores "true" ou "false"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct auxi{
  char **palavras;
} TEXTO;

typedef struct aux{
  int pos;
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

    if(text[i] == ' '){   //Pula os espaços, para adicionar apenas palavras sem espaços na árvore
      aux = raiz;
      continue;
    }

    indice = text[i] - 97;

    if( !(aux->lista[indice]) ){ //Ve se a letra já foi inserida
      aux->lista[indice] = (NO*) malloc(sizeof(NO)); //Cria um novo nó

      if(text[i+1] == ' '){  //Se o próximo caractere for um espaço, então está no final de uma palavra, então deve-se registrar o seu início
        int ini = i;

        while(text[ini-1] != ' ' && ini != 0){ //ini guarda o começo da palavra
          ini--;
        }

        aux->lista[indice]->pos = ini; //Guarda o começo da palavra no nó
      }else{
        aux->lista[indice]->pos = -1; //Se a letra não for o final de uma palavra, recebe -1
      }

      aux->lista[indice]->letra = text[i];
      aux->lista[indice]->lista = (NO **) malloc(26*sizeof(NO)); //Atribuições ao nó
    }

    aux = aux->lista[indice]; //aux aponta para a letra que acabou de ser inserida para continuar a inserção da palavra
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

int busca(NO *arv, char *word){
  NO *busca = arv;
  int i;
  for(i = 0; i<strlen(word); i++){
    busca = busca->lista[word[i] - 97];
  }
  return busca->pos;
}



void main(){
  NO *arv = (NO*) malloc(sizeof(NO));
  iniciaArv(arv);


  char *text = "forget your lust and the rich men gold";
  char *text2 = "all that you need is in your soul";
  adicionaTexto(arv, text);
  //adicionaTexto(arv, text2);
  imprime(arv);
  printf("\n");
  printf("Posicao: %d\n", busca(arv, "me"));
  //visu(arv);

}
