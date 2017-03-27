//描述</h4><p><pre>设计程序，将整数x从第p位开始向左n位（x从右至左编号位0~31）翻转（即1变0,0变1），其余各位保持不变。 &nbsp;输入：三个整数，分别是x,p,n &nbsp;输出：输出分为两行，第一行为整数翻转前的二进制（每八位输出一个空格）&nbsp;<span>第二行为整数翻转后的二进制 &nbsp; &nbsp;注:可参考课本p44的例2.19</span>


#include<stdio.h>
#include<limits.h>
void PrintBit(int x)
{
int i;
int n=sizeof(int) * CHAR_BIT;
int mask=1<<(n-1);
for (i=1; i<=n;++i)
{
putchar (!( x & mask)?'0': '1');
x<<=1;
if(!(i%CHAR_BIT)&&i<n) putchar(' ');
}
printf("\n");
}
int main(void)
{
unsigned x,y,n,p,q;
q=0;
scanf("%d%d%d",&x,&p,&n);
y=(~q<<p)&(~q>>32-n-p)^x;
PrintBit(x);
PrintBit(y);
return 0;
}
