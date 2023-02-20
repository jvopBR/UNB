#include <stdio.h>
#include <math.h>
    int main() {
        double r, x;
            scanf("%lf", &r);

            x = pow(r,2)*3.14159;
            ///without pow : x = r*r*3.14159
        printf("A=%0.4lf\n", x);

    }
