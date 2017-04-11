#include <stdio.h>
int fakestrlen(char str[])
{
        if(*str == '\0')
        {
                return 0;
        }

        return fakestrlen(++str)+1;
}

void get(char str[])
{
    int i=0;
    char c;
    while((c=getchar())!='\n')
    {
       str[i]=c;
       i++;
    }
    str[i]='\0';
}
int main()
{
        int n,i;
        scanf("%d",&n);
        getchar();
        char str[1000];
        for(i=1;i<=n;i++)
        {
            get(str);
            printf("%d\n",fakestrlen(str));
        }
        return 0;
}
