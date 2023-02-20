#include <stdio.h> 
    int main ()
        {
            float a, b, c, p, t;
            scanf("%f", &a);
            scanf("%f", &b);
            scanf("%f", &c);

            if ((a + b) > c && (b + c) > a && (c + a) > b) {
                p = a + b + c;
                printf("Perimetro = %0.1f\n", p);
            }
            else {
                t = (a + b)*c/2;
                printf("Area = %0.1f\n", t);
            }
        }
