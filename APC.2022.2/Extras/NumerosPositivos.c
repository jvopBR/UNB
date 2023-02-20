#include<stdio.h>
 
int main()
{
    float x;
    int i,test=0;
    
  for(i=1;i<=6;i++){
    scanf("%f",&x);
  if(x>0){
      test=test+1;
   }
   }
    printf("%d valores positivos\n",test);
}
