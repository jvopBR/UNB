#include <stdio.h> 
    int main () {
        int i, f;
            scanf("%d", &i);
            scanf("%d", &f);

            if (i == f){
                printf("O JOGO DUROU %d HORA(S)\n", 24-i+f);
            }
            else if (i <= f){
                printf("O JOGO DUROU %d HORA(S)\n", f-i);
            }
            else 
                printf("O JOGO DUROU %d HORA(S)\n", 24-i+f);
    } 
