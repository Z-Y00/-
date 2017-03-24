 
 #include <stdio.h>
int main(void)
{int k,a,sum,i;
    i=0;
    scanf("%d",&k);
    while(i<k)
    {

    scanf("%d. ",&a);
    sum=a&0x000000ff;
    printf("%d.",sum);
       
      
    
    sum=a&0x0000ff00;
    sum>>=8;
    printf("%d.",sum);
    sum=a&0x00ff0000;
    sum>>=16;
    printf("%d.",sum);
    sum=a>>24 ;  
    printf("%d\n",sum); 
    ++i;
    }
    return 0;
} 
