#include <stdio.h>
#include <math.h>

int c_rafael (int x, int y) {
  x = pow(3*x,2) + pow(y, 2);
  return x;
}

int c_beto ( int x, int y) {
  x = 2*(pow(x,2)) + pow (5*y, 2);
  return x;
}

int c_carlos (int x, int y){
  x = -100*x + pow(y, 3);
  return x;
} 

int main ()
{

	int x, y, Rafael, Beto, Carlos;
	unsigned casos;

	scanf("%u", &casos);

	while (casos--)
	{

		scanf("%d %d", &x, &y);
      
		Rafael = c_rafael(x, y);
  	Beto = c_beto (x, y);  
    Carlos = c_carlos(x, y);

		if (Rafael > Beto && Rafael > Carlos)
			printf("Rafael ganhou\n");
		else if (Beto > Rafael && Beto > Carlos)
			printf("Beto ganhou\n");
		else
			printf("Carlos ganhou\n");


	}
}
