#include <stdio.h>
    int main () {
        int x, y, x1, y1;
        float z, z1;

        scanf("%d %d %f", &x, &y, &z);
        scanf("%d %d %f", &x1, &y1, &z1);

        printf("VALOR A PAGAR: R$ %0.2f\n", y*z + y1*z1);

    }
