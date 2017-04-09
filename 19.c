 /*描述</h4><p><pre>将输入的一行字符复制到输出，复制过程中将一个以上的空格字符用一个空格代替。
输入：第一行为正整数N，表示输入数据组数。接下来的为N行字符串。
输出：每行输入对应一行输出。</pre></p><h4>样例输入</h4><p><pre>3
Hello     world    !
    Hello   world!   
Romance   is the glamour    which turns     the dust of everyday   life into a golden haze.
</pre></p><h4>样例输出</h4><p><pre>Hello world !
 Hello world! 
Romance is the glamour which turns the dust of everyday life into a golden haze.
  空格处理*/
#include<stdio.h>
#include <stdbool.h>

int main(void)
{
    int i,x;
    
    
    scanf("%d",&x);
    i=getchar();
    for(i=1;i<=x;i++)
    {
         int c;
         
    bool flag = true;
    while ( (c=getchar()) !='\n')
    {
        if (c!=' ')
        {
            flag = true;
            putchar(c);
        }
        else if (flag==true)
        {
            flag = false;
            putchar(' ');
        }
    }   printf("\n");
        }
      
    
    return 0;
}
 
