#include <stdio.h>
    int main (){
        float n, t, q;
            scanf("%f", &n);
            scanf ("%f", &q);
        if (n == 1){
            t = q*4.00;
        } else if ( n == 2) {
            t = q*4.50;
        }else if ( n == 3) {
            t = q*5.00;
        }else if (n == 4) {
            t = q*2.00;
        }else if (n == 5) {
            t = q*1.50;
        }
    printf("Total: R$ %0.2f\n", t);
    }
