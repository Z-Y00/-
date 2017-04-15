/*掷骰子游戏——改编自习题5.1<span class="pull-right">#作业：76，归档：20170405213427 &nbsp;&nbsp;&nbsp;
                                <a href="javascript:window.opener=null;window.open('','_self');window.close();">关闭当前页面</a>
                            </span></div>
                        <div class="panel-body" onselectstart="return false;" style="-moz-user-select:none;">
                          <h4>描述</h4><p><pre><span>编写一个模拟“投掷双骰子”的游戏程序。游戏规则：每轮投两次，取两次的和，第一轮若和为7或11则获胜，游戏结束；若和为2,3，或12则输了，失败结束；若和为其他数字，则将此值作为自己的点数，继续第二轮，第三轮……直到某轮的和等于该点数则获胜，若出现和为7，则输掉游戏。模拟每掷一次骰子的随机取数规则：输入一个非负整数，称为启动数，你需要计算得到启动数各位数之和记为sum，现将1~6这6张数字卡片按顺时钟方向摆放一个环，一只蚂蚁每次从数字为1的卡片摆放的位置出发，这时你告诉蚂蚁按顺时钟方向走sum步，蚂蚁最终停留位置上的卡片数字即视为本次掷骰子得到的点数。</span><br />
<span>本题包含多组测试数据。</span><br />
<span>输入格式说明：第一行输入n表示测试样例的个数，后面紧接着有n行输入，每行输入包含两个非负整数记为a，b，整数范围在0~10000之间（闭区间），视为第一轮两次投掷的启动数，若进行到了第n轮时，则第n轮两次投掷的启动数分别看作是a+n-1,b+n-1；</span><br />
<p>
	<span>输出格式说明：每组测试样例的输出结果占一行，输出本次游戏的最终结果。</span>
</p>
<p>
	<span>注意：测试数据有100多组</span>
</p></pre></p><h4>样例输入</h4><p><pre>8
1234 1
1 42
0 422
3728 4892
4646 2481
7806 2421
4309 6617
2811 9514</pre></p><h4>样例输出</h4><p><pre>success!
fail!
success!
success!
success!
fail!
fail!
fail!
</pre></p><h4>备注</h4><p><pre>第五章编程题</pre*/
#include <stdio.h>
int sum(int x)
{ //printf("%d\nx",x );
	int sum = 0;
	while(x!=0){
		sum=sum+(x%10);
  //  printf("%d\n%d ;",sum,x );
		x /= 10;
	}
	sum=sum%6+1;
//printf("\n%d\n",sum );
	return sum;
}

int main(void )
{
	int n,i,a,b;
	int r = -1;
	scanf("%d", &n);
	for (i = 0; i < n; ++i)
	{
		scanf("%d %d", &a, &b);

  int an,bn;
	int c;
	int time = 1;
	//while( ){
		if (time == 1)
		  {
				c = sum(a)+sum(b);

				if (c == 7 || c == 11)
				{printf("success!\n");continue;
					}

				if (c == 2 || c == 3 || c == 12)
				{printf("fail!\n");continue;
					}

		  }

		 time=2;
			ui:;
			an=sum(a+time-1);
			bn=sum(b+time-1);
			if (an+bn == c)
			{
				printf("success!\n");continue;time=1;

			}
			else if (an+bn == 7)
			{
				printf("fail!\n");continue;time=1;

			}
			else {time++;//printf("!\n");
							goto ui;}



	}


}
