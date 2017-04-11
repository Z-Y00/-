#include<stdio.h>
#include<stdbool.h>
bool isprime(int c)
{
    int j,a;
    a=0;
    for(j=2;j<=c-1;j++)
    {
        if(c%j==0)
        {
           a+=1;
        }
    }
    if(a==0) {return true;}
    else {return false;}
}

int number(int begin,int end)
{
    return (end-begin)/2+1;
}

void out(int x)
{
        int c;
        c=2;
        while((isprime(c)==false||isprime(x-c)==false)&&c<=(x-2))
        {
            c+=1;
        }
        printf("%d=%d+%d\n",x,c,x-c);
}

int processbegin(int begin)
{
    if(begin%2!=0)
    {
        return begin+1;
    }
    else
    {
        return begin;
    }
}

int processend(int end)
{
    if(end%2!=0)
    {
        return end-1;
    }
    else
    {
        return end;
    }
}
int main()
{
    int begin,end,num,i;
    while(1)
    {
        scanf("%d%d",&begin,&end);
        if(begin!=0)
        {
            begin=processbegin(begin);
            end=processend(end);
            num=number(begin,end);
            for(i=1;i<=num;i++)
            {
                out(begin+2*(i-1));
            }
            printf("\n");
            continue;
        }
        else
        {
            break;
        }
    }
    return 0;
}
