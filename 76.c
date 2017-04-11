#include <stdio.h>

int suum(int n)
{
    int s=0;
    while(n>0)
        {
        s+=n%10;
        n/=10;
    }
    return s;
}

int throw(int sum)
{
    return (sum%6)+1;
}

void play(int begin1,int begin2)
{
    int result,j,dot,start1,start2;
    for(j=0;;j++)
    {
        start1=begin1+j;
        start2=begin2+j;
        result=throw(suum(start1))+throw(suum(start2));
        if(j==0&&(result==7||result==11))
        {
            printf("success!\n");
            break;
        }
        if(j==0&&(result==2||result==3||result==12))
        {
            printf("fail!\n");
            break;
        }
        else
        {
            if(j==0)
            {
                dot=result;
                continue;
            }
            else
            {
                if(result==dot)
                {
                   printf("success!\n");
                   break;
                }
                else if(result==7)
                {
                   printf("fail!\n");
                   break;
                }
                else
                {
                    continue;
                }
            }
        }
    }
}
int main()
{
    int i,n;
    int begin1,begin2;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d%d",&begin1,&begin2);
        play(begin1,begin2);
    }
    return 0;
}
