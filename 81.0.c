/*
 
 
 定义宏交换参数——改编自习题6.4<span class="pull-right">#作业：81，归档：20170410183837 &nbsp;&nbsp;&nbsp;
                                <a href="javascript:window.opener=null;window.open('','_self');window.close();">关闭当前页面</a>
                            </span></div>
                        <div class="panel-body" onselectstart="return false;" style="-moz-user-select:none;">
                          <h4>描述</h4><p><pre>定义宏Swap(x,y)，用于交换两个参数x和y的值，并编写测试程序。<br />
本题包含多组测试数据,组数小于10000组。<br />
输入格式说明：每组测试数据输入占一行，包括两个整数，依次为x，y，整数范围皆在-10000~10000之间（闭区间），遇文件尾测试结束。<br />
输出格式说明：对于每组测试数据，输出交换前x、y的值和交换后x、y的值。需要在第i组测试数据结果输出前添加一行提示信息:“CASE i:”，表示是第i组测试数据对应的结果，相邻两组测试样例的输出结果之间空一行。</pre></p><h4>样例输入</h4><p><pre>10 20
45 145</pre></p><h4>样例输出</h4><p><pre>Case 1:
Before Swap:a=10 b=20
After Swap:a=20 b=10

Case 2:
Before Swap:a=45 b=145
After Swap:a=145 b=45
 
 
 */
 #include <stdio.h>

#define swap(x,y) {x^=y; y^=x; x^=y;}

int main()
{

	int x,y;
	int i = 1;
	do
	{
		scanf("%d %d",&x, &y);
		printf("Case %d:\n", i++);
		printf("Before Swap:a=%d b=%d\n", x, y);
		printf("After Swap:a=%d b=%d\n", y, x);
		printf("\n");
    swap(x,y)
	}while(getchar()!=EOF);
	return 0;
}
