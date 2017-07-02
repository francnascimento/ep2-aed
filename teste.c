#include <stdbool.h>   // variaveis bool assumem valores "true" ou "false"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int* prefixos(char palavra[]){
    int len = strlen(palavra);
    int *prefix = (int*) calloc(len, sizeof(int));
    //printf(palavra);
    prefix[0] = 0;

    int j = 0;
    int i;

    for(i = 1; i<len; i++){
        prefix[i] = 0;
        while(j>0 && palavra[j] != palavra[i]){
            j = prefix[j-1];
            //printf("%d %d\n", i, j);
            //while(j>0 && palavra[j] != palavra[i])
            //    j--;
        }
        if(palavra[j] == palavra[i]){
            //printf("\nentrou no j %d %d\n", i, j+1);
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
            if(j == m-1 && (i - j == 0 || texto[i-j-1] == ' ') ){
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
    printf("\n");
    if(find == 0) printf("-1\n");
}



void main(){



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


    char* token;
    char* string;
    char* tofree;

    string = strdup(a[2]);

    if (string != NULL) {
        tofree = string;
        while ((token = strsep(&string, " ")) != NULL){
          KMP(a[0], token);
        }
        free(tofree);
    }




}
