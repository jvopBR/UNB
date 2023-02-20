#include <stdio.h>

void result( int total_coelho, int total_rato, int total_sapo ) {
  const int total = total_coelho + total_rato + total_sapo;

  printf("Total: %d cobaias\n", total);
  printf("Total de coelhos: %d\n", total_coelho);
  printf("Total de ratos: %d\n", total_rato);
  printf("Total de sapos: %d\n", total_sapo);
  printf("Percentual de coelhos: %.2f %%\n", ( (float)total_coelho / total ) * 100);
  printf("Percentual de ratos: %.2f %%\n", ( (float)total_rato / total ) * 100);
  printf("Percentual de sapos: %.2f %%\n", ( (float)total_sapo / total ) * 100);
} 

int main( ) {
  int N;
  scanf("%d", &N);

  int total         = 0,
      total_coelho  = 0,
      total_sapo    = 0,
      total_rato    = 0;

  for (int i = 0; i < N; ++i) {
    int Q;
    char T;
    scanf("%d %c", &Q, &T);

    total += Q;

    switch( T ) {
      case 'C':
        total_coelho += Q;
        break;

      case 'R':
        total_rato += Q;
        break;

      case 'S':
        total_sapo += Q;
        break;

      default:
        break;
    }
  }

  result( total_coelho, total_rato, total_sapo );
  return 0;
}
