/*
冰雹数——改编自习题5.11<span class="pull-right">#作业：21，归档：20170405213427 &nbsp;&nbsp;&nbsp;
                                <a href="javascript:window.opener=null;window.open('','_self');window.close();">关闭当前页面</a>
                            </span></div>
                        <div class="panel-body" onselectstart="return false;" style="-moz-user-select:none;">
                          <h4>描述</h4><p><pre>编写产生一些冰雹的程序，程序应该使用函数 void hailstone(int n)来计算冰雹并显示由n产生的序列。参考课本习题5.11。
输入：有多组输入数据，每行输入一个整数n（n≥1），当输入的n为零时程序结束运行。
输出：对于每个输入的n，输出其产生的冰雹序列，每行输出6个整数，每个整数宽度为5（右对齐，空格补齐）。两组输出用空行隔开。</pre></p><h4>样例输入</h4><p><pre>1
2
3
15
77
100
0
</pre></p><h4>样例输出</h4><p><pre>    1

    2    1

    3   10    5   16    8    4
    2    1

   15   46   23   70   35  106
   53  160   80   40   20   10
    5   16    8    4    2    1

   77  232  116   58   29   88
   44   22   11   34   17   52
   26   13   40   20   10    5
   16    8    4    2    1

  100   50   25   76   38   19
   58   29   88   44   22   11
   34   17   52   26   13   40
   20   10    5   16    8    4
    2    1

*/#include <stdio.h>
void hailstone(int n)
{
	if (n == 1) n=1;
	if (n%2) n=3*n+1;
	else n=n/2;
}
int he(int n)
{
	if (n == 1) n=1;
	if (n%2) n=3*n+1;
	else n=n/2;
  return n;
}


 int main(void)
  {int x,t;
    scanf("%d",&x);
    //getchar();
  //  printf("%5.d ll",x);
    while (x!=0)
     { t=0;
       while (x!=1)
       {
         printf("%5.d",x);
         x=he(x);
         t++;
         if((t%6)==0)printf("\n");
       }
       if(x=1) printf("    1\n");
       printf("\n");
       scanf("%d",&x);
      }



  return 0;
  }
