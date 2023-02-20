#include <stdio.h>
int main () {

  char x[14];

  while (scanf("%s", x) != EOF)
  {
    printf("%c%c%c\n", x[0], x[1], x[2]);
    printf("%c%c%c\n", x[4], x[5], x[6]);
    printf("%c%c%c\n", x[8], x[9], x[10]);
    printf("%c%c\n", x[12], x[13]);
  }
  return 0;
}
