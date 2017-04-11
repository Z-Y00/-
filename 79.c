#include <stdio.h>
#include <string.h>

int process(char n[],int k )
{
    if(k<=strlen(n))
    {
        return n[strlen(n)-k]-'0';
    }
    else
    {
        return -1;
    }
}

int main()
{
    char n[10];
    int k;
    while(scanf("%s%d",n,&k)!=EOF)
    {
        printf("%d\n",process(n,k));
    }
    return 0;
}
