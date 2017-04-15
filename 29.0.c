/*歌德巴赫
歌德巴赫猜想：任一个大于等于6的偶数都可以表示为两个素数之和。编写程序，证明对于在正整数begin和end之间的偶数这一猜想成立。
</p>
<p>
	输入：每行为一组输入，每行有两个100以内的正整数，分别为begin和end(begin<span style="line-height:1.5;">≥6，end</span><span style="line-height:1.5;">≥begin</span><span style="line-height:1.5;"></span><span style="line-height:1.5;">)，当begin为0时程序结束运行。</span>
</p>
<p>
	<span style="line-height:1.5;">输出：每组输入对应一组输出，每组输出格式参考样例输出，对于每个偶数，只需输出其第一个成立的式子(即被加数最小的情况)；</span>
</p>
<p>
	<span style="line-height:1.5;">&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;每两组输出用\n
*/
#include<stdio.h>
int main(void)
{   int x[25]={3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
  int i,k,j,r,u,n;
 /* x[0]=3 ;
  x[22]= 89;
  x[23]= 97;
  x[24]= 0;*/
  int flag=0;
  u=0;
  scanf("%d%d",&r,&n);
  while ((r!=0)&&(n!=0))
  {   flag=0;
      for ( u=((r/2)*2+(r%2)*2); u<=n; u+=2)
       {
      for (k=0;flag==0;k++)
      {
      for (j=0;((flag==0)&&(j<=24));j++)
      {(u==x[k]+x[j])?(flag=1):(flag=0);
      }
      }
      //printf("%d%d\n",k,j );
       printf("%d=%d+%d\n",u,x[k-1],x[j-1]);
       flag=0;
    }printf("\n");
      scanf("%d%d",&r,&n);
   }

  return 0;
}
