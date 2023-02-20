#include <stdio.h>
int main(){
    int c, n, i;
    float result,s;
      
      scanf("%d",&c);
   while(c > 0){
      scanf("%d",&n);
          result = 0;
          s = 0;
    int media[n];
    for(i = 0; i < n; i++){
      scanf("%d",&media[i]);
          result+=media[i];
  }
          result /= n;
    for(i = 0; i < n; i++){
    if(media[i] > result) s++;
    }
      printf("%.3f%c\n",s/n*100.000,'%');
          c--;
    }
}
