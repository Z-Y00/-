#include<stdio.h>  
#define swap(a,b) {int temp; temp=a; a=b; b=temp; }
int main() 
{  
    int a,b,n,i;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&a,&b);
        swap(a,b);
        printf("%d %d\n",a,b);  
    }
    
    return 0;
}