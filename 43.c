/*≥…º®¥¶¿Ì*/


#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct student
{
    char name[20];
    int score;
}stu;

stu* in(int N)
{
    stu* stupointer=(stu*)malloc(N*sizeof(stu));
    int i,j,s;
    char c;
    for(i=0;i<N;i++)
    {
        j=0;
        char name[20];
        stu stutemp;
        while((c=getchar())!=' ')
        {
            name[j]=c;
            j++;
        }
        name[j]='\0';
        strcpy(stutemp.name,name);
        scanf("%d",&s); getchar();
        stutemp.score=s;
        stupointer[i]=stutemp;
    }
    return stupointer;
}

void sort(stu* stupointer,int N)
{
	stu stutemp;
	int i,j,k,m;
	for(i=0;i<N;i++)
	{
		m=i;
		for(j=i;j<N;j++)
		{
			if (stupointer[j].score>stupointer[m].score)
			{
				m=j;
			}
		}
		stutemp=stupointer[m];
		for(k=m;k>i;k--)
		{
			stupointer[k]=stupointer[k-1];
		}
		stupointer[i]=stutemp;
    }
}

void output_INFO(stu* stupointer,int N)
{
    int i;
    for(i=0;i<N;i++)
    {
        printf("%-20s %d\n",stupointer[i].name,stupointer[i].score);
    }
}

int BINARY_FIND(stu* stupointer,int target,int begin,int end)
{
    if(begin>end)
    {
        return -1;
    }
	int mid=(begin+end)/2;
    if(stupointer[mid].score==target)
    {
        return mid;
    }
	if(stupointer[mid].score<target)
    {
        return BINARY_FIND(stupointer,target,begin,mid-1);
    }
	if(stupointer[mid].score>target)
    {
        return BINARY_FIND(stupointer,target,mid+1,end);
    }

}

void findresult(stu* stupointer,int* score_to_find,int N,int n)
{
    int i,num;
    for(i=0;i<n;i++)
    {
        num=BINARY_FIND(stupointer,score_to_find[i],0,N-1);
        if(num!=-1)
        {
            printf("%-20s %d\n",stupointer[num].name,stupointer[num].score);
        }
        else
        {
            printf("Not found!\n");
        }
    }
}

int main()
{
    int N,n,i;
    scanf("%d",&N); getchar();
    stu* stupointer=in(N);
    sort(stupointer,N);
    output_INFO(stupointer,N);
    printf("\n");
    scanf("%d",&n); getchar();
    int* score_to_find=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        scanf("%d",score_to_find+i);
    }
    findresult(stupointer,score_to_find,N,n);
    free(score_to_find);
    free(stupointer);
    return 0;
}
