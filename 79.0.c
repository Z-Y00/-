/*描述</h4><p><pre>输入正整数n和k，输出n中从右端开始的第k个数字的值（k从1开始）。将求n中右端第k个数字定义成函数，如果k超过了n的位数，则函数返回-1；否则返回n中第k个数字。<br />
本题包含多组测试数据。<br />
输入格式说明：每组测试数据输入占一行，包括两个正整数，依次为n，k，<br />
n在1~4294967293之间（闭区间），遇文件尾测试结束。<br />
输出格式说明：每组测试样例的输出结果占一行，输出函数返回结果。<br /></pre></p><h4>样例输入</h4><p><pre>321 3
421 4
42 12
4294967293 10
4294967293 11</pre></p><h4>样例输出</h4><p><pre>3
-1
-1
4
-1*/


#include <stdio.h>



int getK(long int  x, int k)
{
	int i = 1;
	while(i++ < k)
	{
		x = x/10;
	}
	if(x)
    return x%10;
	else
    return -1;
}

int main(int argc, char const *argv[])
{
	long int x;
	int k;
	do
	{
		scanf("%ld %d", &x , &k);
		printf("%d\n", getK(x, k));
	} while (getchar() !=EOF);
	return 0;
}
