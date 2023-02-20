#include <stdio.h>
#include <math.h>
    int main(){
        double a, b, c;
            scanf("%lf %lf %lf", &a, &b, &c);
            printf("TRIANGULO: %0.3lf\n", (a*c)/2);
            printf("CIRCULO: %0.3lf\n", 3.14159*pow(c,2));
            printf("TRAPEZIO: %0.3lf\n", (a + b)*c/2);
            printf("QUADRADO: %0.3lf\n", pow(b,2));
            printf("RETANGULO: %0.3lf\n", a*b);

    }
