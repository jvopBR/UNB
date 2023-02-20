#include <stdio.h> 
    int main() {
        float r;
            scanf("%f", &r);
        
        if(r <= 2000){
           printf("Isento\n");     
        }
        else if (r <= 3000.00){
            printf("R$ %.2f\n", (r - 2000.00)*0.08);
        }
        else if (r <= 4500){
            printf("R$ %.2f\n", ((r - 3000.00)*0.18 + 1000.00*0.08));
        }
        else if (r >= 4500.01){
            printf("R$ %.2f\n", ((r - 4500.00)*0.28 + 1500.00*0.18 + 1000.00*0.08));
        }
    }
