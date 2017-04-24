/*十进制转换为二进制*/

#include <stdio.h>
#include<malloc.h>
const int len = sizeof(int)*8;

void dectobin(int dec, char* bin)
{
    int i = 0;
    int j;
    int flag;
    flag = (dec>=0)?0:1;
    dec = (dec>=0)?dec:(-dec);
    while(i < len-1)
    {
        bin[i++] = dec%2+48;
        dec = dec/2;
    }
    if(flag == 1)
    {
        j = 0;
        while(bin[j] == 0+48)j++;
        for(i = j+1 ; i < len-1 ; i++)
        {
            bin[i] = (bin[i]==0+48)?1+48:0+48;
        }
    }

    bin[len-1]=flag+48;
}

int main()
{
    int N,i,j;
    int* dec=NULL;
    char* bin=NULL;
    scanf("%d",&N);
    dec=(int*)malloc(N*sizeof(int));
    bin=(char*)malloc(len);
    for(i=0;i<N;i++)
    {
        scanf("%d",dec+i);
    }
    for(i=0;i<N;i++)
    {
        dectobin(*(dec+i),bin);
        for(j=0;j<len;j++)
        {
            printf("%c",bin[len-1-j]);
        }
        printf("\n");
    }
    return 0;
}
