/*输出中间数
 
 
 
 描述</h4><p><pre>输入A,B,C三个学生的考试分数（皆为正整数，范围0~100），输出分数居中的那个学生的名字（A、B或C）以及考试分数。<br />
注：当A,B,C中存在分数相等的情况时，只需输出一个结果，按照A、B、C的优先顺序输出唯一结果。<br />
本题包含多组测试数据。<br />
输入格式说明：每组测试数据输入占一行，包括三个正整数，分别代表A、B、C的考试分数，遇文件尾测试结束。<br />
输出格式说明：每组测试样例的输出结果占一行。<br /></pre></p><h4>样例输入</h4><p><pre>90 90 90
 
 
 */ 
#include<stdio.h>
int main (void)
{
    int x,y,z=0;
    while (scanf("%d %d %d",&x,&y,&z)!=EOF)
    {   
        if (((x<=y)&&(x>=z))||((x<=z)&&(x>=y)))
           printf("A:%d\n",x); 
        else if(((y>=x)&&(y<=z))||((y>=z)&&(y<=x)))
            printf("B:%d\n",y);
        else 
            printf("C:%d\n",z);
     }
     return 0;
    
}
