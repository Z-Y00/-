#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LINESIZE 512  //读文件时每行允许读取的字符数
#define VTSIZE 1024
#define CTSIZE  1024

#define IDENTIFY 1
#define KEYWORD 2
#define CONSTANT 3
#define STRING 4
#define OPERATOR 5
#define BORDER 6

typedef struct ConTable_non
{
    int id_non;
    char name_non[100];
    char replace_non[100];
    struct ConTable_non *next_non;
} ConTable_non;  //无参宏结点定义

typedef struct ReplaceNode
{
    int id_flag;
    char string_section[10];
    struct ReplaceNode *next_replace;
}ReplaceNode;  //替代字符串的节点

typedef struct ConTable
{
    int id;
    char name[100];
    int argu_count;
    char argu_list[20];  //默认定义带参宏时，每个参数都是一个字符
    ReplaceNode *replace;
    struct ConTable *next;
} ConTable;  //带参宏结点定义

typedef struct Token
{
    int line;
    int number;
    char name[100];
    int x;  //行号
    int y;  //列号
    int times;
	struct Token *next;
} Token;

typedef struct IdenTable
{
    int id;
    char name[20];
    int times;
} IdenTable;

typedef struct ConTable_token
{
    int id;
    char name[100];
    int times;
} ConTable_token;

typedef struct HashNode
{
	char name[10];
	int times;
	struct HashNode *next;
} HashNode;

char buf[LINESIZE];
int start;  //数组当前位置标记
FILE *in,*out;
char *define_addr;
int flag_def=0;
int flag_ifdef=1;  //通过flag_ifdef来判断是否编译当前语句
char judge[6][20];

/**宏定义链表首指针**/
ConTable_non *head_non,*tail_non;
ConTable *head,*tail;
int keywordtimes[34]={0};
int instructtimes[40]={0};
int bordertimes[4]={0};
int changetimes[12]={0};

char instructList[][4] = { "+","-","*","/","%","{","}",")","(",">","<","=","[","]","?","!","&","|",
                       "++","--","==",":=",">=","<=","!=","&&","||","+=","-=","*=","/=","^",">>","<<","~","#",".","\""
                     };//by order unnecessary notation
char borderList[][3]={";",",",":"};
char keywordList[][10] = {"include","auto","break","case","char","const","continue","default","do","double",
                       "else","enum","extern","float","for","goto","if","int","long","register",
                       "return","short","signed","sizeof","static","struct","switch","typedef",
                       "union","unsigned","volatile","while",""
                      };//by order
char changeList[12] = {'a', 'b', 'f','n','r','t','v','\\','?','"','\'','0'};
int line;
int idenTableNum=0;
int tokenNum=0;
int conTableNum=0;
int flag=1;
char *notation_addr;

/**声明哈希表**/
HashNode *HashList[26];

/**声明链表首指针**/
Token *head_token,*tail_token;  //是带头结点的。。。
IdenTable idenTableArray[VTSIZE];
ConTable_token conTableArray[CTSIZE];

int ClearBlank(void);
void dealinclude(void);
void dealdefine(void);
void dealundef(void);
void dealifdef(void);  //#ifdef
void dealifndef(void);  //#ifndef
void dealelse(void);  //#else
void dealendif(void);  //#endif
void deal_isnot_macro(void);  //不是宏定义
int isargument(void);
int is_define_over(int i);
int count_argu(int i,char *argu_list);
ReplaceNode *creat_replace_string(int i,char *argu_list);
int is_in_list(char ch,char *argu_list);
void add_in(char ch,char *string_section);
int in_contable(char *name);
int in_contable_non(char *name);
int is_in_contable(char *name);
int is_in_contable_non(char *name);
int is_alpha(char ch);
int is_digit(char ch);
int is_space(char ch);

void dealalpha(void);
void dealdigit(void);
void dealNotation(void);
int isBorder(char ch);
int isinstruct(void);
void dealBorder(int ret);
void dealChar(void);
int isin_idenTable(char *word);
int isKeyword(char *word);
int isin_ConTable(char *word);
void dealinstruct(int ret);
void dealstring(void);
void shuchu(void);

int main(int argc,char **argv)
{
	int flag_include;
    int i,j;
    int odd_or_even;
    char in_file_name[40],out_file_name[43];
    char judge_include[15];  //用于装载#include <
	char defines[][10]={"#define","#undef","#ifdef","#ifndef","#else","#endif"};
	
	/**建立无参宏和带参宏的链表**/
    head_non=(ConTable_non *)malloc(sizeof(ConTable_non));
    head=(ConTable *)malloc(sizeof(ConTable));
    tail_non=(ConTable_non *)malloc(sizeof(ConTable_non));
    tail=(ConTable *)malloc(sizeof(ConTable));
    head_non->next_non=(ConTable_non *)malloc(sizeof(ConTable_non));  //带头结点，方便删除
    head->next=(ConTable *)malloc(sizeof(ConTable));
    tail_non=head_non->next_non;
    tail=head->next;
    tail->next=NULL;
    tail_non->next_non=NULL;
	
	strcpy(in_file_name,argv[1]);
    in=fopen(in_file_name,"r");
    if(in==NULL)
	{
        printf("cannot open file %s!\n",in_file_name);
        return -1;
    }
    strcpy(out_file_name,"pre");
    strcat(out_file_name,in_file_name);
    out=fopen(out_file_name,"w");
    if(out==NULL)
	{
        printf("cannot open file %s!\n",out_file_name);
        return -1;
    }
	
    /**开始替换include语句**/
    for(flag_include=1,odd_or_even=0;flag_include;odd_or_even=(odd_or_even+1)%2)  //odd_or_even的值为0或1
	{
		/**通过读入和输出两个文件的角色转换来完成多次扫描**/
        flag_include=0;
        if(!odd_or_even){  //通过odd_or_even来控制从哪个文件中来读取
            in=fopen(in_file_name,"r");
            if(in==NULL){
                printf("cannot open file %s!\n",in_file_name);
                return -1;
            }
            out=fopen(out_file_name,"w");
            if(out==NULL){
                printf("cannot open file %s!\n",out_file_name);
                return -1;
            }
        }
        else{
            in=fopen(out_file_name,"r");
            if(in==NULL){
                printf("cannot open file %s!\n",out_file_name);
                return -1;
            }
            out=fopen(in_file_name,"w");
            if(out==NULL){
                printf("cannot open file %s!\n",in_file_name);
                return -1;
            }
        }

		while(fgets(buf, LINESIZE, in)!=NULL)
		{
			start = 0;  //start赋初值
			if(ClearBlank() == -1){
			/**当前行是空行**/
				fputc('\n', out);  //当前空行处理结束
				continue;
			}
			/**当前行不是空行**/
			strncpy(judge_include,buf+start,10);
			judge_include[10]='\0';
		    if(!(strcmp(judge_include,"#include <")) || !(strcmp(judge_include,"#include \""))){
			 /**是incude语句**/
				flag_include=1;
				dealinclude();
			}
			else{
				 fputs(buf,out);
			}
		}
		fclose(in);
		fclose(out);
    }
    /**include语句替换完成**/
	
    /**当前：pre1.txt中存放include处理之后的文件。。。不过两文件内容一样**/
	/**开始处理宏定义**/
    in=fopen(in_file_name,"r");
    if(in==NULL){
        printf("cannot open file %s!\n",in_file_name);
        return -1;
    }
    out=fopen(out_file_name,"w");
    if(out==NULL){
        printf("cannot open file %s!\n",out_file_name);
        return -1;
    }
	
	while(fgets(buf, LINESIZE, in)!=NULL)
	{  //条件编译不考虑#elif，因为常量表达式比较麻烦。。。
		for(start=0;buf[start] == ' ' || buf[start] == '\t';start++) ;
		strncpy(judge[0],buf+start,7);  //#define
		judge[0][7]='\0';
		strncpy(judge[1],buf+start,6);  //#undef
		judge[1][6]='\0';
		strncpy(judge[2],buf+start,6);  //#ifdef
		judge[2][6]='\0';
		strncpy(judge[3],buf+start,7);  //#ifndef
		judge[3][7]='\0';
		strncpy(judge[4],buf+start,5);  //#else
		judge[4][5]='\0';
		strncpy(judge[5],buf+start,6);  //#endif
		judge[5][6]='\0';
		for(j=0;j<6;j++)
		{
			if(!strcmp(judge[j],defines[j]))
				break;
		}
		switch(j)
		{
			case 0:	dealdefine(); break;  //#define
			case 1:	dealundef(); break;  //#undef
			case 2: dealifdef(); break;  //#ifdef
			case 3: dealifndef(); break; //#ifndef
			case 4: dealelse(); break; //#else
			case 5: dealendif(); break; //#endif
			default: deal_isnot_macro(); break;
		}
	}
    fclose(in);
    fclose(out);
	/**宏处理完毕**/
/**预编译处理完毕**/

	/**建立token链表**/
	head_token=(Token *)malloc(sizeof(Token));
	tail_token=(Token *)malloc(sizeof(Token));
	tail_token=head_token;
	tail_token->next = NULL;

	/**为关键字建立哈希表，采用链地址法解决地址冲突**/
	HashNode *hash_p,*hashtemp,*head_token;
	hash_p=(HashNode *)malloc(sizeof(HashNode));
	for(i=0;i<26;i++)
	{ //初始化为空指针
		HashList[i] = NULL;
	}
	for(i=0;i<32;i++)
	{
		j=keywordList[i][0]-'a';
		if(HashList[j] == NULL)
		{ //建立链表
			head_token=(HashNode *)malloc(sizeof(HashNode));
			head_token->next=NULL;
			strcpy(head_token->name,keywordList[i]);
			head_token->times=0;
			HashList[j]=head_token;
		}
		else
		{
			for(hash_p = HashList[j];hash_p->next != NULL;hash_p=hash_p->next) ;
			hash_p->next=(HashNode *)malloc(sizeof(HashNode));
			strcpy(hash_p->next->name,keywordList[i]);
			hash_p->next->times=0;
			hash_p->next->next=NULL;
		}
	}
	/**哈希表建立完成**/

	line = 1;
    char in_name[30],out_name[30];
    int ret;  //作为函数返回的中介
	strcpy(in_name,out_file_name);
	strcpy(out_name,"out.txt");
    in=fopen(in_name,"r");
    if(in == NULL){
        printf("cannot open file %s!\n",in_name);
        return -1;
    }
    out=fopen(out_name,"w");
    if(out == NULL){
        printf("cannot open file %s!\n",out_name);
        return -1;
    }

    /**开始进行词法分析**/
    char ch;
    while(fgets(buf,LINESIZE,in))
    {
        start=0;
        for(;buf[start]!= '\n' && flag;)  //flag用于判断注释
        {
            while(is_space(buf[start]))
            {
                start++;
            }  //去除中间多余的空白字符
            ch=buf[start];
            if(is_alpha(ch) || ch == '_')  //字母：标识符、关键字
                dealalpha();
            else if(is_digit(ch))  //数字：数字常量
                dealdigit();
            else if(ch== '/')  //疑似注释
            {
                dealNotation();
            }
            else if(ret=isBorder(ch) != -1)  //分隔符
            {
                dealBorder(ret);
            }
            else if(ch=='\'')
            {
                dealChar();  //字符常量
            }
            else if(ch == '"')
            {
                dealstring();  //字符串
            }
            else if((ret=isinstruct()) != -1)  //操作符
            {
                dealinstruct(ret);
            }
            else // not available start
            {
                printf("cannot analyse %c in line %d\n",ch,line);
				start++;
            }
        }
        line++;
		flag = 1;
    }
    shuchu();  //向文件输出
	fclose(in);
	fclose(out);
/**词法分析完成**/

	system("pause");
	return 0;
}

/**定位到当前缓冲区的第一个非空白字符**/
int ClearBlank(void)
{
    char ch;
    ch=buf[start];
    for(;ch ==' ' || ch =='\n' || ch =='\t';){
        if(ch=='\n'){
            return -1;  //当前行是空行
        }
        ch=buf[++start];
    }
    return 0;
}

/**处理include语句**/
void dealinclude(void)
{
/**只考虑标准的头文件，不过用户自定义得头文件也一样**/
    char temp_file_name[20];  //存储头文件名称
    char head_file_name[100];
    char buf_include[LINESIZE];
    int i;
    start=start+10;
    for(i=0;buf[start]!='>' && buf[start]!='\"';start++,i++)
	{
        temp_file_name[i]=buf[start];
    }
    temp_file_name[i]='\0';
    //头文件名已被复制
    if(strstr(temp_file_name,"/")!=NULL)  //在include的子目录下面
	{
        if(strcmp(temp_file_name,"machine/ansi.h")==0 || strcmp(temp_file_name,"sys/_types.h")==0)
		{
            strcpy(head_file_name,"head/");
            strcat(head_file_name,temp_file_name);
        }
        else
		{
            strcpy(head_file_name,"D:/安装的软件/CodeBlocks/MinGW/include/");
            strcat(head_file_name,temp_file_name);
        }
    }
    else
	{
        strcpy(head_file_name,"head/");
        strcat(head_file_name,temp_file_name);
    }
    FILE *op;
    op=fopen(head_file_name,"r");
    if(op==NULL)
	{
        printf("cannot open the head file %s!\n",head_file_name);
    }
    while(fgets(buf_include, LINESIZE, op)!=NULL)
	{
        fputs(buf_include,out);
    }
    fclose(op);
}

/**处理define**/
void dealdefine(void)
{
	define_addr = strstr(buf,"#define ");
    int i,j;
    ConTable_non *temp_non;
    ConTable *temp;
    int a;
    a=isargument();
    if(a==0)  //无参宏
	{
        temp_non=(ConTable_non *)malloc(sizeof(ConTable_non));
        for(i=8,j=0;define_addr[i]!=' ' ;i++,j++)
		{
            temp_non->name_non[j]=define_addr[i];  //宏名复制完成
        }
		temp_non->name_non[j]='\0';
    /**这里为简洁起见，定义宏时define和宏名之间只能隔一个空格**/
        i++;
        for(j=0;;i++,j++)
		{
            if(define_addr[i]!='\n')
			{
                temp_non->replace_non[j]=define_addr[i];
            }
            else if(is_define_over(i) == 1)  //到达define语句的结尾
			{
                temp_non->replace_non[j]='\0';
                break;
            }
            else{
                temp_non->replace_non[j]=define_addr[i];
            }
        }  //宏替代字符串复制完成
        tail_non->next_non=temp_non;
        tail_non=temp_non;
        tail_non->next_non=NULL;
    }  //无参宏链表添加完成
    else  //带参宏
	{
        temp=(ConTable *)malloc(sizeof(ConTable));
        //对参数列表进行初始化
        for(j=0;j<20;j++)
		{
            temp->argu_list[j]='\0';
        }
        for(i=8,j=0;define_addr[i]!='(' ;i++,j++)
		{
            temp->name[j]=define_addr[i];  //宏名复制完成
        }
		temp->name[j]='\0';
        temp->argu_count=count_argu(i,temp->argu_list);
        temp->replace=(ReplaceNode *)malloc(sizeof(ReplaceNode));
        temp->replace=creat_replace_string(i,temp->argu_list);
        tail->next=temp;
        tail=temp;
        tail->next=NULL;
    }  //带参宏链表添加完成
}

/**处理undef语句**/
void dealundef(void)
{
	define_addr = strstr(buf,"#undef ");
    char temp_name[100];  //宏名
    int i,j;
    for(i=7,j=0;!(isspace(define_addr[i]));i++,j++){
        temp_name[j]=define_addr[i];
    }
    temp_name[j]='\0';
    //宏名复制完成
    if(in_contable_non(temp_name) == 0){  //不是无参宏，不进行删除
        if(in_contable(temp_name) == 0){  //也不是带参宏，也不进行删除
            printf("undefined HONG!\n");  //即不作处理，只输出提示
        }
    }
}

/**处理#ifdef**/
void dealifdef(void)
{
	int i;
	ConTable *pre,*now;  //用于判断宏是否已定义
	ConTable_non *pre_non,*now_non;
	flag_def++;
	start=start+6;
	for(;isspace(buf[start]);start++) ;
	for(i=0;!isspace(buf[start]);start++,i++)
	{
		judge[2][i]=buf[start];
	}
	judge[2][i]='\0';
	
	/**开始检查是否是已经定义的无参宏**/
	pre_non=head_non;
	now_non=head_non->next_non;
	for(;now_non!= NULL; pre_non=now_non,now_non=now_non->next_non){
		if(strcmp(judge[2],now_non->name_non)!= 0) ;
		else{
			break;
		}
	}
	pre=head;
	now=head->next;
	for(;now!= NULL; pre=now,now=now->next){
		if(strcmp(judge[2],now->name)!= 0) ;
		else{
			break;
		}
	}
	if(now_non!= NULL || now!= NULL)
	{  //是已经定义的宏
		flag_ifdef=1;
	}
	else  //未考虑到#elif
	{  //当前宏未被定义
		flag_ifdef=0;
	}
}

/**处理#ifndef**/
void dealifndef(void)
{
	int i;
	ConTable *pre,*now;  //用于判断宏是否已定义
	ConTable_non *pre_non,*now_non;
	flag_def++;
	start=start+7;
	for(;isspace(buf[start]);start++) ;
	for(i=0;!isspace(buf[start]);start++,i++)
	{
		judge[3][i]=buf[start];
	}
	judge[3][i]='\0';
	
	/**开始检查是否是已经定义的宏**/
	pre_non=head_non;
	now_non=head_non->next_non;
	for(;now_non!= NULL; pre_non=now_non,now_non=now_non->next_non){
		if(strcmp(judge[3],now_non->name_non)!= 0) ;
		else{
			break;
		}
	}
	pre=head;
	now=head->next;
	for(;now!= NULL; pre=now,now=now->next){
		if(strcmp(judge[3],now->name)!= 0) ;
		else{
			break;
		}
	}
	/**检查完毕**/
	
	if(now_non== NULL && now== NULL)
	{  //当前宏未被定义
		flag_ifdef=1;
	}
	else  //未考虑到#elif
	{  //是被定义的宏
		flag_ifdef=0;
	}
}

/**处理#else**/
void dealelse(void)
{
	flag_ifdef=(flag_ifdef+1)%2;  //把flag_ifdef 0变为1,1变为0
}

/**处理#endif**/
void dealendif(void)
{
	flag_def--;
	flag_ifdef = 1;
}

/**处理不是宏定义的情况**/
void deal_isnot_macro(void)
{
	if(flag_ifdef == 0)  //直接忽略当前语句
	{
			return;
	}
  //进入处理程序，也就是下面的处理程序
	start = 0;
	if(ClearBlank() == -1)  //当前行是空行
	{
		/**在这里把空行删除掉了**/
		return;
	}
	if(buf[start] == '/' && buf[start+1] == '/')  //如果是注释
	{
		fputs(buf+start,out);
		return ;
	}
	char string_temp[100];  //替换define时，存放从buf中读取的单个字符串
	int j;
	while(buf[start] != '\0')
	{
		for(j=0;is_alpha(buf[start]) || is_digit(buf[start]) || buf[start] == '_';j++,start++){  /**注意！！！！：这里关于跳出循环的方式还需要商榷**/
			string_temp[j]=buf[start];
		}  //一个字符串复制完成
		/**当前buf[start] == '('**/
		string_temp[j]='\0';
		if(is_in_contable_non(string_temp)){  //无参宏替换
			fputc(buf[start],out);
			start++;
		}
		else if(is_in_contable(string_temp)){  //带参宏替换
			start++;
			fputc(buf[start],out);
			start++;
		}
		else
		{
			fputs(string_temp,out);  //原样输出
			fputc(buf[start],out);
			start++;
		}
	}
}

/**判断define语句是否结束**/
int is_define_over(int i)
{
    /**当前状态：define_addr[i]==' '**/
    char temp;
    temp=define_addr[i];
    for(;temp!= '\n';)
	{
        if(temp == ' ') ;
        else if(temp != '/')
            return 0;
        else if(define_addr[i+1] == '*' || define_addr[i+1] == '/')  //是注释
            return 1;
        else
            return 0;
        temp=define_addr[++i];
    }
    if(temp == '\n')
        return 1;
    else
        return 0;
}

/**判断是否是无参宏**/
int isargument(void)
{
    char temp[100];
    int i;
    for(i=0;;i++)
	{
        temp[i]=define_addr[i+8];
        if(temp[i]==' ' || temp[i]=='('){
            if(temp[i]=='(')
                return 1;
            else
                return 0;
        }
    }
}

/**计算带参宏参数的个数，并对参数列表进行赋值**/
/**参数列表从[1]开始**/
int count_argu(int i,char *argu_list)
{
    int a;
    /**当前状态：define_addr[i]== '('**/
    i++;
    for(a=0;define_addr[i]!= ')';i++){
        if(define_addr[i]!= ','){
            a++;
            argu_list[a]=define_addr[i];
        }
    }
    return a;
}

/**建立带参宏的替代字符串**/
ReplaceNode *creat_replace_string(int i,char *argu_list)
{
    int ret;
    int j,k;
    char temp[10][10];
    /**当前状态：define_addr[i] == '('**/
    ReplaceNode *loc_head,*loc_tail;
    i++;
    for(;define_addr[i]!= ')';i++) ;
    /**当前状态：define_addr[i] == ')'**/
    i++;
    for(;define_addr[i] == ' ';i++) ;
    loc_head=(ReplaceNode *)malloc(sizeof(ReplaceNode));  //建立替代字符串的首指针，不需要头结点
    loc_tail=loc_head;
    j=0;
	k=0;
    for(;;i++)
    {
        if(define_addr[i] == '\n')
		{
				temp[k][j]='\0';
				strcpy(loc_tail->string_section,temp[k]);
				loc_tail->next_replace=NULL;
                break;
        }
        if(define_addr[i]>='a' && define_addr[i]<= 'z' || define_addr[i]>='A' && define_addr[i]<= 'Z')
		{
            ret=is_in_list(define_addr[i],argu_list);
            if(ret){  //在参数列表里
                temp[k][j]='\0';
				strcpy(loc_tail->string_section,temp[k]);
				k++;
                j=0;
                loc_tail->next_replace=(ReplaceNode *)malloc(sizeof(ReplaceNode));
                loc_tail=loc_tail->next_replace;  //先结束非参数子串数组
                loc_tail->id_flag=ret;
				strcpy(loc_tail->string_section,"");
                loc_tail->next_replace=(ReplaceNode *)malloc(sizeof(ReplaceNode));
                loc_tail=loc_tail->next_replace;
                continue;
            }
            else
            {
                loc_tail->id_flag=0;
                temp[k][j]=define_addr[i];
                j++;
            }
        }
		else
		{
			//不在参数列表里
			loc_tail->id_flag=0;
			temp[k][j]=define_addr[i];
			j++;
		}
    }
    return loc_head;
}

/**判断字母是否在当前带参宏的参数列表里**/
int is_in_list(char ch,char *argu_list)
{
    int i;
    for(i=1;argu_list[i]!= '\0';i++){
        if(ch == argu_list[i]){
            return i;
        }
    }
    return 0;
}

/**是否属于无参宏，并进行删除**/
int in_contable_non(char *name)
{
    ConTable_non *pre,*now;
    pre=head_non;
    now=head_non->next_non;
    for(;now!= NULL; pre=now,now=now->next_non){
        if(strcmp(name,now->name_non)!= 0) ;
        else{
            pre->next_non=now->next_non;
            free(now);
            return 1;
        }
    }
    return 0;
}

/**是否属于带参宏,并进行删除**/
int in_contable(char *name)
{
    ConTable *pre,*now;
    pre=head;
    now=head->next;
    for(;now!= NULL; pre=now,now=now->next){
        if(strcmp(name,now->name)!= 0) ;
        else{
            pre->next=now->next;
            free(now);
            return 1;
        }
    }
    return 0;
}

/**判断是否在无参宏列表中，并进行替换**/
int is_in_contable_non(char *name)
{
    ConTable_non *pre,*now;
    pre=head_non;
    now=head_non->next_non;
    for(;now!= NULL; pre=now,now=now->next_non){
        if(strcmp(name,now->name_non)!= 0) ;
        else{
            fputs(now->replace_non,out);  //输出替换的字符串
            //fprintf(out," ");  //输出空格
            return 1;
        }
    }
    return 0;
}

/**判断是否在带参宏列表中，并进行替换**/
int is_in_contable(char *name)
{   
    /**需要注意，调用带参宏时，参数可能被括号扩为一个整体**/
    ConTable *pre,*now;
    char charge[100];
	char **temp;
    charge[0]='\0';
    ReplaceNode *tempnode;
    int count;
    int i,j,flag_temp;
    flag_temp=1;  //用来计算括号的对应关系
    pre=head;
    now=head->next;
    for(;now!= NULL; pre=now,now=now->next)
    {
        if(strcmp(name,now->name)!= 0) ;
        else  //是带参宏
        {
            count=now->argu_count;
			//count = 2;
			temp=(char **)malloc(sizeof(char *)*count);
			for(i=0;i<count;i++)
			{
				temp[i]=(char *)malloc(sizeof(char)*20);
			}
			/**当前buf[start] == '('**/
            for(i=0;i < count;i++)  //i用于判断当前是第几个参数
            { //循环取多个参数
                start++;
                for(j=0;buf[start]!= ',';start++,j++)
                { //循环取一个参数的多个字符
                    if(i == count-1)  //如果是最后一个参数的话，在此处break
                    {
                        if(flag_temp == 1 && buf[start] == ')')
                            break;
                    }
					if(buf[start] == '(')
                        flag_temp++;
                    if(buf[start] == ')')
                        flag_temp--;
					temp[i][j]=buf[start];
                }
				temp[i][j]='\0';
            }
            /**参数获得完毕，开始替换代入**/
            tempnode = now->replace;
            for(;tempnode != NULL;tempnode=tempnode->next_replace)
            {
                if(tempnode->id_flag == 0)
                {
                    strcat(charge,tempnode->string_section);
                }
                else
                {
                    strcat(charge,temp[tempnode->id_flag-1]);
                }
            }
            /**替换代入完毕，准备向文件中输出**/
            fputs(charge,out);  //输出替换的字符串
            return 1;
        }
    }
    return 0;
}

/**判断是否是字母**/
int is_alpha(char ch)
{
	if(ch>='a' && ch<= 'z' || ch>= 'A' && ch<= 'Z')
		return 1;
	else
		return 0;
}

/**判断是否是数字**/
int is_digit(char ch)
{
	if(ch>='0' && ch<= '9')
		return 1;
	else
		return 0;
}

/**判断是否是空白符**/
int is_space(char ch)
{ //只考虑到空格和制表符，因为暂时只用到这两个。。。
	if(ch == ' ' || ch == '\t')
		return 1;
	else
		return 0;
}

/**处理标识符、关键字**/
void dealalpha(void)
{
    int symbol;
    int id;
    char word[100];
    Token *token;
	token=(Token *)malloc(sizeof(Token));
    IdenTable idenTable;
    int i;
    token->x=line;
    token->y=start;
	for(i=0;is_digit(buf[start]) || is_alpha(buf[start]) || buf[start] == '_' || buf[start] == '#';i++,start++)
    {
        word[i]=buf[start];
    }  //此时，buf[start] == ' '
    word[i] = '\0';

    strcpy(token->name,word);
    symbol = isKeyword(word);
    /**不是关键字，是标识符**/
    if(symbol == -1)
    {
        token->number = IDENTIFY;
        id=isin_idenTable(word);
        if(id== -1)
        {
            idenTable.id=idenTableNum;
            strcpy(idenTable.name,word);
            idenTable.times=1;
            idenTableArray[idenTableNum] = idenTable;
            token->times=idenTableArray[idenTableNum].times;
            idenTableNum++;
        }
        else
        {
            idenTableArray[id].times++;
            token->times=idenTableArray[id].times;
        }
    }
    /**是关键字**/
    else
    {
        token->number= KEYWORD;
		token->times= symbol;
    }
	tail_token->next=token;
	tail_token=tail_token->next;
	tail_token->next=NULL;
    tokenNum++;
}

/**判断是否已经在标识符的表中**/
int isin_idenTable(char *word)
{
    int i;
    for(i=0;i<idenTableNum;i++)
    {
        if(!strcmp(idenTableArray[i].name,word))
        {
            return i;
        }
    }
    return -1;
}

/**判断是否是关键字，若是，返回出现的次数**/
int isKeyword(char *word)
{
	int j;
	HashNode *hashp;
	j=word[0]-'a';
	for(hashp=HashList[j];hashp!= NULL; hashp=hashp->next)
    {
		if(!strcmp(hashp->name,word))
        {
			hashp->times++;
			return hashp->times;
        }
    }
    return -1;
}

/**处理数字常量**/
void dealdigit(void)
{
    int id;
	int flag_f=0;
    char word[100];
    Token *token;
	token=(Token *)malloc(sizeof(Token));
    ConTable_token conTable;
    int i;
    token->x=line;
    token->y=start;											//+  -  只能在E的后面
	i=0;
	if(buf[start] == '0' && (buf[start+1] == 'X' || buf[start+1] == 'x'))  //十六进制
	{
		word[i++]=buf[start++];
		word[i++]=buf[start++];
		for(;is_digit(buf[start]) || (buf[start]>='A' && buf[start]<='F') || (buf[start]>='a' && buf[start]<='f');i++,start++)
		{
			word[i]=buf[start];
		}
	}
	else if(buf[start] == '0') //八进制
	{
		word[i++]=buf[start++];
		for(;is_digit(buf[start]);i++,start++)
		{
			word[i]=buf[start];
		}
	}
	else
	{
		for(;is_digit(buf[start]) || buf[start] == '.' || buf[start] == 'E' || buf[start] == 'e' || (buf[start] == '+' && (buf[start-1] == 'E' || buf[start-1] == 'e')) || (buf[start] == '-' && (buf[start-1] == 'E' || buf[start-1] == 'e'));i++,start++)
		{
			if(buf[start] == '.')
				flag_f = 0;
			 word[i]=buf[start];
		}
		if(buf[start] == 'f' || buf[start] == 'F'){  //有F 或f后缀
			word[i]=buf[start];
			i++;
			start++;
		}
	}
    word[i] = '\0';
    strcpy(token->name,word);
    token->number=CONSTANT;
    id = isin_ConTable(word);
    if(id==-1)
    { /**不在常量表里，新加项**/
        conTable.id = conTableNum;  //？？刚开始怎么就变成1了。。。不应该是0吗。。。。
        strcpy(conTable.name, word);
        conTable.times=1;
        conTableArray[conTableNum] = conTable;
        token->times=conTableArray[conTableNum].times;
        conTableNum++;
    }
    else
    {
        conTableArray[id].times++;
        token->times=conTableArray[id].times;
    }
    tail_token->next=token;
	tail_token=tail_token->next;
	tail_token->next=NULL;
    tokenNum++;
}

/**判断是否在常量表中**/
int isin_ConTable(char *word)
{
    int i;
    for(i=0;i<conTableNum;i++)
    {
        if(!strcmp(conTableArray[i].name,word))
        {
            return i;
        }
    }
    return -1;
}

/**处理疑似注释**/
void dealNotation(void)
{ /**当前：buf[start] == '/'**/
    char ch;
    int i;
    int notationLen=0;
    Token *token;
	token=(Token *)malloc(sizeof(Token));
    ch = buf[start+1];
    /**除号处理**/
    if(ch!='/'&&ch!='*')
    {
        strcpy(token->name,"/");
        token->number = OPERATOR;
        instructtimes[3]++;
        token->times = instructtimes[3];
        token->x = line;
        token->y = start;
        tail_token->next=token;
		tail_token=tail_token->next;
		tail_token->next=NULL;
        tokenNum++;
        start++;
        return ;
    }
    else if(ch=='/')
    {
        flag=0;  //需要重新开始一行
        return ;
    }
    else
    {
        for(i=start+2;; i++)
        { /**当前：buf[i] == 注释后的第一个字符**/

			if((notation_addr = strstr(buf,"*/"))!= NULL)  //当前行有注释的结尾标记
			{
				if(notation_addr <= buf+start+1)
				{  //并不是当前注释的结尾，所以还要继续执行下去

				}
				else
				{
					for(;;start++)
					{
						if(buf[start] == '*' && buf[start+1] == '/')
						{ //此时：buf[start] == '*'
							start = start+2;
							return ;  //注释处理完毕，返回
						//当前：buf[start] == 注释结束后的第一个字符**/
						}
						else ;
					}
				}
			}
			fgets(buf, LINESIZE, in);
            line++;  //虽然注释被忽略了，但是注释引起的行数的变化仍然被记录着
            start = 0;
        }
    }
}

/**判断是否是分隔符**/
int isBorder(char ch)
{
    int i;
    for(i=0; borderList[i][0]; i++)
    {
        if(ch==borderList[i][0])
        {
            return i;
        }
    }
    return -1;
}

/**处理分隔符**/
void dealBorder(int ret)
{
    Token *token;
	token=(Token *)malloc(sizeof(Token));
    token->name[0]=buf[start];
    token->name[1]='\0';
    token->number=BORDER;
    bordertimes[ret]++;
    token->times=bordertimes[ret];
    token->x = line;
    token->y = start;
    tail_token->next=token;
	tail_token=tail_token->next;
	tail_token->next=NULL;
    tokenNum++;
    start++;
}

/**判断是否是操作符**/
int isinstruct(void)
{
    char s[3];
    int ret;
    int i;
    s[0] = buf[start];
    s[1] = buf[start+1];
    s[2] = '\0';
    if (s[1]=='+' || s[1]=='-' || s[1]=='=' || s[1]=='&' || s[1]=='|' || s[1]=='>' || s[1]=='<')
    { /**处理双界符**/
        switch(s[1]){
            case  '+':  ret=18; break;
            case  '-':  ret=19; break;
            case  '&':  ret=25; break;
            case  '|':  ret=26; break;
            case  '=':  ret=0; break;
            case  '>':  ret=32; break;
            case  '<':  ret=33; break;
        }
        if(!ret)  //以等号结尾的操作符
        {
            switch(s[0]){
                case  '=':  ret=20;
                case  ':':  ret=21;
                case  '>':  ret=22;
                case  '<':  ret=23;
                case  '!':  ret=24;
                case  '+':  ret=27;
                case  '-':  ret=28;
                case  '*':  ret=29;
                case  '/':  ret=30;
            }
        }
        return ret;
    }
    /**判断单界符**/
    for(i=0; instructList[i][0]; i++)
    {
        if(buf[start]==instructList[i][0])
        {
            return i;
        }
    }
    return -1;
}

/**处理操作符**/
void dealinstruct(int ret)
{
    Token *token;
	token=(Token *)malloc(sizeof(Token));
    token->y = start;
    if((ret>=18 && ret<=30) || ret == 32 || ret == 33)
    {
        token->name[0]=buf[start];
        token->name[1]=buf[start+1];
        token->name[2]='\0';
        start=start+2;
    }
    else
    {
        token->name[0]=buf[start];
        token->name[1]='\0';
        start++;
    }
    token->number=OPERATOR;
    instructtimes[ret]++;
    token->times=instructtimes[ret];
    token->x = line;
	tail_token->next=token;
	tail_token=tail_token->next;
	tail_token->next=NULL;
    tokenNum++;
}

/**处理字符串和字符常量**/
void dealChar(void)
{
    Token *token;
	token=(Token *)malloc(sizeof(Token));
    ConTable_token conTable;
    int id;
    int j;
    char word[100];
    word[0] = buf[start];
    if(buf[start+1]=='\\')//转义字符
    {
        for(j=0; j<12; j++)
        {
            if(buf[start+2]==changeList[j])
            {
                word[1] = '\\';
                word[2] = buf[start+2];
                word[3] = '\'';
                word[4] = '\0';
                strcpy(token->name, word);
                token->number=CONSTANT;
                changetimes[j]++;
                token->times=changetimes[j];
                token->x=line;
                token->y=start;
                tail_token->next=token;
				tail_token=tail_token->next;
				tail_token->next=NULL;
                tokenNum++;
                start = start+4;
                return;
            }
        }
        /**error: 转义字符不合法**/
        if(j==12)
        {
            printf("wrong change char in line %d!\n", line);
        }
    }
    else if(buf[start+2] != '\'')
    {
        printf("wrong const char in line %d!\n", line);
        for(start = start+2; buf[start]!='\''; start++);
        start++ ;
        return;
    }
    else
    {
        word[1] = buf[start+1];
        word[2] = '\'';
        word[3] = '\0';
        strcpy(token->name,word);
        token->number=CONSTANT;
        token->x=line;
        token->y=start;
        id = isin_ConTable(word);
        /**不在常量表里，新加项**/
        if(id==-1)
        {
            conTable.id = conTableNum;
            strcpy(conTable.name, word);
            conTable.times=1;
            conTableArray[conTableNum] = conTable;
            token->times=conTableArray[conTableNum].times;
            conTableNum++;
        }
        else
        {
            conTableArray[id].times++;
            token->times=idenTableArray[id].times;
        }
        tail_token->next=token;
		tail_token=tail_token->next;
		tail_token->next=NULL;
        tokenNum++;
        start = start+3;
        return;
    }
}

/**处理字符串文字**/
void dealstring(void)
{
    int j;
    Token *token1,*token2,*token3;
	token1=(Token *)malloc(sizeof(Token));
	token2=(Token *)malloc(sizeof(Token));
	token3=(Token *)malloc(sizeof(Token));
    ConTable_token conTable;
    int id;
    char word[100];

	token1->name[0]='"';
	token1->name[1]='\0';
	token1->number=OPERATOR;
	instructtimes[37]++;
	token1->times=instructtimes[37];
	token1->x=line;
	token1->y=start;
	tail_token->next=token1;
	tail_token=tail_token->next;
	tail_token->next=NULL;
    tokenNum++;
	start++;

	/**从字符串中第一个不是 " 的字符开始**/
    word[0]=buf[start];
    token2->y=start;
    start++;
        for(j=1; !(buf[start]=='"' && buf[start-1] !='\\'); start++,j++)
        {
            word[j] = buf[start];
        }
		word[j]='\0';
        strcpy(token2->name,word);
        token2->number=STRING;
        token2->x=line;
        id = isin_ConTable(word);
        /**不在常量表里**/
        if(id==-1)
        {
            conTable.id = conTableNum;
            strcpy(conTable.name, word);
            conTable.times=1;
            conTableArray[conTableNum] = conTable;
            token2->times=conTableArray[conTableNum].times;
            conTableNum++;
        }
    else
    {
        conTableArray[id].times++;
        token2->times=conTableArray[id].times;
    }
        tail_token->next=token2;
		tail_token=tail_token->next;
		tail_token->next=NULL;
        tokenNum++;

	/**处理结尾的 " **/
	token3->name[0]='"';
	token3->name[1]='\0';
	token3->number=OPERATOR;
	instructtimes[37]++;
	token3->times=instructtimes[37];
	token3->x=line;
	token3->y=start;
	tail_token->next=token3;
	tail_token=tail_token->next;
	tail_token->next=NULL;
    tokenNum++;
	start++;
}

/**向out.txt文件输出**/
void shuchu(void)
{
	int i;
	Token *tp;
	tp=head_token->next;
    for(i=1;tp!=NULL;tp=tp->next,i++)
    { /**注意：因为在数组中是以[0]开始的，所以在输出列号时需要+1**/
        fprintf(out,"%-4d  %-4d  %-30s  %-4d  %-4d  %-4d\n",i,tp->number,tp->name,tp->x,tp->y+1,tp->times);
    }
}




