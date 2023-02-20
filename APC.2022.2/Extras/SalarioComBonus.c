#include <stdio.h>
    int main () {
        char nome[20];
        double a, b, t;
        scanf("%s %lf %lf", &nome, &a, &b);

        t = a + b*0.15;

        printf("TOTAL = R$ %0.2lf\n", t);
    }
