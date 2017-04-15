/* <h4>描述</h4><p><pre>用递归实现标准库函数strlen(s)，并调用该函数计算字符串长度。
输入：第一行为正整数N，表示有N行输入，接下来的N行，每行为一个字符串。
输出：每行输入对应一行输出，输出字符串的长度。</pre></p><h4>样例输入</h4><p><pre>5
hello  world !
hello world
come    on
o
on
</pre></p><h4>样例输出</h4><p><pre>14
15
10
1
2
</pre></p><h4>备注</h4><p><pre>第五章编程题</pre></p>  */


#include <string.h>
#include <stdio.h>
#undef strlen
size_t strlen( const char *s )
{
    int n = 0;

    while ( (s[n]) ) ++n;

    return n;
}

int main(void)
{   int i,j;
  //string r;
    scanf("%d ",&i);

    for(j=1;j<=i;j++)
    {   int t;
        char str[50]={0};

        //scanf("%s ",str);
        scanf(" %[^\n]s", str );//...%*c OR ADD an \n
        fflush(stdin);
        t=strlen(str);
        printf("%d\n",t);
    }




}
