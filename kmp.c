//KMP
#include <stdbool.h>   // variaveis bool assumem valores "true" ou "false"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int* prefixos(char palavra[]){
    int len = strlen(palavra);
    int *prefix = (int*) calloc(len, sizeof(int));
    prefix[0] = 0;

    int j = 0;
    int i;

    for(i = 1; i<len; i++){
        prefix[i] = 0;
        while(j>0 && palavra[j] != palavra[i]){
            j = prefix[j-1];
        }
        if(palavra[j] == palavra[i]){
            prefix[i] = j+1;
            j++;
        }
    }

    int x;
    return prefix;

}





void KMP(char texto[], char palavra[]){
    int *F = prefixos(palavra);
    int i = 0;
    int j = 0;
    int n = strlen(texto);
    int m = strlen(palavra);
    int find = 0;


    while(i < n){
        if(texto[i] == palavra[j]){
            if(j == m-1 && (i - j == 0 || texto[i-j-1] == ' ') && (i == n-1 || texto[i+1] == ' ') ){
                printf("%d ", i-j);
                find++;
                i++;
                j = 0;
            }else{
                i++;
                j++;
             }
        }else{
            if(j>0)
                j = F[j-1];
            else
                i++;
        }
    }
    if(find != 0)printf("\n");
    if(find == 0) printf("-1\n");
}




void main(){

    int num;
    scanf("%d", &num);

    char d[50];

    char txt[10000];
    char word[50];
    while(num > 0){
        txt[0] = '\0';
        word[0] = '\0';
        scanf("%c", d);
        scanf("%[^\n]%*c", txt);
        scanf("%s", word);
        KMP(txt, word);
        num--;
    }

}
