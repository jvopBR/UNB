#include <stdio.h>
    int main () {
        int n, d;
            scanf(" %d %d", &n, &d);

            
        if ( n % d == 0 || d % n  == 0) {
            printf("Sao Multiplos\n");
        } 
        else
         { 
             printf("Nao sao Multiplos\n");
         }
        
    }
