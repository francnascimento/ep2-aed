//TRIE
#include <stdbool.h>   // variaveis bool assumem valores "true" ou "false"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 typedef struct listaPosicoes{
  int posi;
  struct listaPosicoes *prox;
} position;

typedef struct auxi{
  char **palavras;
} TEXTO;

typedef struct aux{
  position *pos;
  struct aux **lista;
  char letra;
} NO;


void iniciaArv(NO *raiz){
  raiz->lista = (NO **) malloc(26*sizeof(NO));
}



void adicionaTexto(NO *raiz, char *text){
  int i, indice;
  NO *aux = raiz;
  int j = strlen(text);
  for(i = 0; i<strlen(text); i++){
    if(text[i] == ' '){   //Pula os espaços, para adicionar apenas palavras sem espaços na árvore
      aux = raiz;
      continue;
    }

    indice = text[i] - 97;

    if( !(aux->lista[indice]) ){ //Ve se a letra já foi inserida
      aux->lista[indice] = (NO*) malloc(sizeof(NO)); //Cria um novo nó
      aux->lista[indice]->pos = (position*) malloc(sizeof(position)); //Cria uma nova lista ligada que guarda todas as posições da letra
      aux->lista[indice]->pos->prox = NULL;
      aux->lista[indice]->letra = text[i];
      aux->lista[indice]->lista = (NO **) malloc(26*sizeof(NO)); //Atribuições ao nó

      if(text[i+1] == ' ' || i == strlen(text)-1 ){
        position *auxiliar = aux->lista[indice]->pos;
        int ini = i;

        while(text[ini-1] != ' ' && ini != 0){ //ini guarda o começo da palavra
          ini--;
        }
        auxiliar->posi = ini; //Guarda o começo da palavra no nó
      }

      else{
        aux->lista[indice]->pos->posi = -1; //Se a letra não for o final de uma palavra, recebe -1
      }

    }
    else if( text[i+1] == ' ' || i == strlen(text)-1 ){ //Se a letra já foi inserida, porém ela é a última de uma palavra, insira a posição no final da lista
        position *auxiliar = aux->lista[indice]->pos;

        while(auxiliar->prox){ //Para ir até o final da lista
          auxiliar = auxiliar->prox;
        }
        int ini = i;

        while(text[ini-1] != ' ' && ini != 0){
          ini--;
        }
        auxiliar->prox = (position*) malloc(sizeof(position)); //Cria um novo elemnto no final da lista para guardar a posição
        auxiliar->prox->prox = NULL;
        auxiliar->prox->posi = ini;
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

void busca(NO *arv, char *word){
  int um = -1;
  NO *busca = arv;
  int i;
  for(i = 0; i<strlen(word); i++){
    if(word[i] == ' ') break;
    if(busca->lista[word[i] - 97]){
        busca = busca->lista[word[i] - 97];
    }
    else{
        printf("%d\n", um);
        break;
    }
  }
  while(busca->pos){
      printf("%d ", busca->pos->posi);
      busca->pos = busca->pos->prox;
  }
  printf("\n");
}



void main(){
  NO *arv = (NO*) malloc(sizeof(NO));
  iniciaArv(arv);



  int i;
  char text[10000];
  char a[3][10000];
  int j = 0;
  int blank = 1;
  while(fgets(text, sizeof(text), stdin) != NULL){
      int x;
      for(x = 0; x<strlen(text)-1; x++){
          a[j][x] = text[x];
      }
      if(j==2 && text[x]) blank++;
      j++;
  }

  adicionaTexto(arv, a[0]);

  char* token;
  char* string;
  char* tofree;

  string = strdup(a[2]);

  if (string != NULL) {
  tofree = string;
  while ((token = strsep(&string, " ")) != NULL){
    busca(arv, token);
  }
  free(tofree);
  }

}
