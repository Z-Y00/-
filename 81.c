#include<stdio.h>  
#define swap(x,y) {int temp; temp=x; x=y; y=temp; }
int main()
{
    int x,y,i;
    i=1;
    while(scanf("%d%d",&x,&y)!=EOF)
    {
        
        swap(x,y);
        printf("Case %d:\n",i);
        printf("Before Swap:a=%d b=%d\n",y,x);
        printf("After Swap:a=%d b=%d\n\n",x,y);
        i++;
    }
    return 0;
}