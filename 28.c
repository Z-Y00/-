/*y=3x^3-4x^2-5x+13=0
 e=10^(-8)
 
 */ 
#include<stdio.h>
int main(void)
{double y=-1,x=-1;
  entr: ;
    
    y=x-(x*(x*(3*x-4)-5)+13)/(x*(9*x-8)-5);
   if ((x-y)<0.000000001)
   {x=y;
       goto entr;
   }
else {printf("%lf",y);
    return 0;
      }



}
