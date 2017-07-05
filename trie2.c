//TRIE
#include <time.h>
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
    int teste = 0;
  int i, indice;
  NO *aux = raiz;
  int j = strlen(text);
  for(i = 0; i<strlen(text); i++){
      if(text[i-1] == ' ' && text[i] == 'e' && text[i+1] == 'x' && text[i+2] == ' '){
          teste++;
      }
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

int busca(NO *arv, char *word){
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
        return 0;
        break;
    }
  }
  while(busca->pos){
      printf("%d ", busca->pos->posi);
      busca->pos = busca->pos->prox;
  }
  printf("\n");
  return 1;
}



void main(){



  int num;
  scanf("%d", &num);

  char d[50];

  char txt[10000];
  char word[50];
  while(num > 0){
      NO *arv = (NO*) malloc(sizeof(NO));
      iniciaArv(arv);


      txt[0] = '\0';
      word[0] = '\0';
      scanf("%c", d);
      scanf("%[^\n]%*c", txt);
      scanf("%s", word);
      adicionaTexto(arv, txt);
      busca(arv, word);
      num--;
  }



}
