#include<stdio.h>
int gys(int m,int n)
 {
    int temp;
    temp=m%n;
    if(temp!=0)
    {
        return gys(n,temp);
    }
      else
    {
        return n;
    }
 }
 int main()
 {
    int m,n,swaap;
    while(1)
    {
         scanf("%d%d",&m,&n);
         if(m!=0)
         {
            if(m<n)
            {
                swaap=m;
                m=n;
                n=swaap;
            }
            printf("%d\n",gys(m,n));
            continue;
         }
         else
         {
             break;
         }

    }
    return 0;
 }
