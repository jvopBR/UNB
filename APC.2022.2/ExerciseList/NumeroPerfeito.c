#include <stdio.h>

typedef int bool;

bool is_perfect(int j) {
  int k = 0;
  for(int l = 1; l < j; l++){
    if(j%l == 0) k += l;
  }

  return k == j;
}

int main()
{
    int n, i, j, l,k = 0;

    scanf("%d", &n);

    for(i = 0;i < n;i++){
        scanf("%d", &j);

        if(is_perfect(j))printf("%d eh perfeito\n", j);
        else printf("%d nao eh perfeito\n", j);
    }
}
