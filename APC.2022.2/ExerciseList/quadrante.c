#include <stdio.h>
    int coordenadas (int x, int y);

    int main (){
        int x, y;
        while (x != 0 || y != 0 ) {
            scanf ("%d %d", &x, &y);
            coordenadas(x,y);
        if (x == 0 || y == 0 )
        break;

        }
    }

    int coordenadas (int x, int y){

    if (x>0 && y>0) 
        printf("primeiro\n");
    else if (x<0 && y>0)
        printf("segundo\n");
    else if (x<0 && y<0) 
        printf("terceiro\n");
    else if (x>0 && y<0) 
        printf("quarto\n");
    return 0;
    }
