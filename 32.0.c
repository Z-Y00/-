/*两数交换<span class="pull-right">#作业：32，归档：20170410183837 &nbsp;&nbsp;&nbsp;
                                <a href="javascript:window.opener=null;window.open('','_self');window.close();">关闭当前页面</a>
                            </span></div>
                        <div class="panel-body" onselectstart="return false;" style="-moz-user-select:none;">
                          <h4>描述</h4><p><pre><pre>定义宏swap(x,y)用于交换两个参数x和y的值，并编写程序测试。
输入：第一行为正整数N，表示有N组输入，接下来的N行，每行包含两个待交换的整数。
输出：每组输出，对应输出交换结果。</pre>
<pre><img src="/CTest2/ex/kindeditor/attached/image/20150525/20150525131405_12506.png" alt="" /> </pre></pre></p><h4>样例输入</h4><p><pre>5
1 2
0 0
5 9
25 32
88 89</pre></p><h4>样例输出</h4><p><pre>2 1
0 0
9 5
32 25
89 88
</pre></p><h4>备注</h4><p><pre>第六章作业题</pre></p> */

#include <stdio.h>

#define swap(a,b) {a^=b; b^=a; a^=b;}

int main(void )
{
	int n,i;
	int a,b;
	scanf("%d", &n);
	for (i = 0; i < n; ++i)
	{
		scanf("%d %d",&a, &b);

		printf("%d %d\n", b, a);swap(a,b);
	}
	return 0;
}
