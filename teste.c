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
    printf("Prefixos:\n");
    for (x = 0; x < len; x++) {
        printf("%d ", prefix[x]);
    }
    printf("\n");
    return prefix;

}





int KMP(char texto[], char palavra[]){
    int *F = prefixos(palavra);
    int i = 0;
    int j = 0;
    int n = strlen(texto);
    int m = strlen(palavra);

    while(i < n){
        if(texto[i] == palavra[j]){
            if(j == m-1){
                return i-j;
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
    return -1;
}



void main(){
    char text[] = "abchabykabcdabcdabcyeabcdeklj";
    char word[] = "abcdabcy";
    printf("A palavra comeca em: %d\n", KMP(text, word) );

    //prefixos(word);
}
