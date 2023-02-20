#include <stdio.h>
    int main () {
        int a, m, d;
        scanf("%d", &d);

            a = d / 365;
            m = ( d % 365) / 30;
            d = d % 365 % 30;
            
        printf("%d ano(s)\n%d mes(es)\n%d dia(s)\n", a, m, d);
    }
