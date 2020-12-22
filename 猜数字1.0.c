#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h> 

void loading();//加载动画 
void menu();//菜单
int game();//游戏 
int rank();//读取玩家信息并写入文件 
int list();//读取文件并排序 
int score = 0 ; //定义分数

typedef struct data //定义数据结构{姓名,次数} 
{
    char name[20];//名字,字符类型 
	int score; 
}player;

void loading()//加载动画 
{
	int i;
	printf("请耐心等待,正在加载中.....\n\n");
	//同过调整i<= ??  可以改变加载速度  i*x=100即可 
	for(i=1;i<=25;i++)
	{
        printf("");
        printf("%d%%",4*i);//50%x2=100%
        Sleep(101-1*i);//减慢程序执行时间 
        printf("\b\b\b");//删除之前的xx% 
	}
	printf("\b\n\n加载完成！进入菜单.....\n");
	Sleep(3); 
	system("cls");//清除 
}

void menu()
{	
	//1-23#,23-37空格,38-63# sleep()防止瞬间输出 
	int i; 
	for(i=0;i<=63;i++)  
	{
		if(i>=1){printf("#");Sleep(7);} 
		else {printf("");Sleep(8);}
	}
	printf("\n");
	for(i=0;i<63;i++) 
	{
		if(i>=1&& i<23){printf("#");Sleep(9);}
		else if(i>=23&&i<37) {printf(" ");Sleep(10);} 
		else {printf("#");Sleep(9);}
	}
	printf("\n");
	printf("#######################    1. 开始   ##########################\n");
    	printf("#######################              ##########################\n");
    	printf("#######################    2. 退出   ##########################\n");
	printf("#######################              ##########################\n");    
    	printf("#######################    3. 排行   ##########################\n");
    	printf("#######################              ##########################\n");
    	printf("#######################    4. 重置   ##########################\n");
	//菜单可全用for循环实现,美观但占用空间复杂度和内存 
		for(i=0;i<63;i++) 
	{
		if(i>=1&& i<23){printf("#");Sleep(8);}
		else if(i>=23&&i<37) {printf(" ");Sleep(7);}
		else {printf("#");Sleep(8);}
	}
	printf("\n");
		for(i=0;i<=63;i++) 
	{
		if(i>=1){printf("#");Sleep(9);}
		else {printf("");Sleep(10);}
	}
	printf("\n");
	//菜单动画,用for循环输出实现 
} 

int game()
{	
	int i=0;//定义范围
	printf("请输入你想要的范围的最大值：");
	scanf("%d",&i);
	if (i<=0)
	{
		printf("太小了不可以哦,大一点吧\n");
		game();
		return 0; 
		//重新执行游戏
	}
	
    int random_num = rand() % i + 1; //生成随机数 
    int guess = 0;//定义猜的数
    int times = 1;//存储次数,第一次也算,所以time = 1 
     
    while(1)
    {
        printf("请输入你猜的数: ");
        scanf("%d", & guess );
	        if ( guess  > random_num)
	        {
	            printf("猜大了\n");
	            times++; 
	            Sleep(1);
	        }
	        else if ( guess  < random_num)
	        {
	            printf("猜小了\n");
	            times++; 
	            Sleep(1);
	        }
	        else
	        {	
				if (times == 1)//判断次数,一次给予表扬 
				{
	 			   printf("厉害哦,一次就对呐!\n");
				}
				else
				{
				 	printf("恭喜你猜对了,正确答案是%d,你猜了%d次\n",random_num,times);
				} 
	        	score = times; //将次数赋值给score 分数 
    			break;
	        }
		}
		return score; //返回分数 供rank() 和 list() 使用  
	//rank();	
}
    
int rank()//读取玩家信息并写入文件 
{
	//printf("\n rank:%d!\n",score);
	player tmp;//临时储存结构体 
	FILE *fp;
	printf("请输入你的名字：");
	scanf("%s",&tmp.name);
	printf("谢谢,欢迎下次再玩!\n\n");
	tmp.score = score;
	fp=fopen("rank.txt","a"); 
	if(fp==NULL)
	        { 
	         printf("打不开文件!\n");  
	         system("pause");  
	         return -1;//如果文件出现错误返回-1  
			}
	fprintf(fp,"%s %d",tmp.name,tmp.score);
	fclose(fp);
	return 0;
} 

int list()
{
	//printf("list!\n");
	printf("####################    排行榜   #############################\n\n");
	player tmp[10];//临时变量,储存name,score
	player temp;//中间变量，用于排序的变量值交换
	int i = 0,n = 0,j = 0,k = 0;
	FILE *fp;
	fp = fopen("rank.txt","rb");//读写方式打开文件 
	if(fp==NULL)              
	{  	
		
        printf("错误!!!没有数据!!!\n"); 
		printf("请游戏后再查看排行榜!\n");
        system("pause");  
        return -1;
    }
	for(i=0;i<n-1;i++)//采用冒泡法进行排序 
    {  
        k=i;  
		for(j=i+1;j<n;j++)  
	    if(tmp[j].score>tmp[k].score)//排序比较大小 
        k=j;
		temp=tmp[k];
		tmp[k]=tmp[i];
		tmp[i]=temp;//当符合条件时进行数据交换
	} 
	i = 0;
	printf("名次:        名字:         次数:\n"); 
	while(i <= 10&&fscanf(fp,"%s%d",tmp[i].name,&tmp[i].score)!=EOF)//判断文件是否为空 
	{
	printf("%3d  %15s  %10d\n",i+1,tmp[i].name,tmp[i].score);//输出排行 
	i++;
	}
	fclose(fp);
	return 0;
} 

void delete()//删除文件 
{
	remove("rank.txt");
	printf("\n删除成功!\n");
}

int main()
{	
	int i;
	printf("#######################    猜数游戏   ##########################\n\n");
	printf("请耐心等待,正在加载中.....\n\n"); 
	printf("当前进度:\n"); 
	for(i=1;i<=25;i++)
	{
        printf("");
        printf("%d%%",4*i);//25%x4=100%
        Sleep(101-1*i);//减慢程序执行时间 测试时注释掉 
        printf("\b\b\b");//删除之前的xx% 
	}
	printf("\b\n\n加载完成！跳转菜单中.....\n");
	sleep(3);
	system("cls");
	
    int input = 0;//定义选择 
    srand((unsigned)time(NULL));
	//srand()函数用来设置算法的种子，time(NULL)返回当前的时间，把当前的时间作为种子产生不同的随机数序列
    do
    {	
        menu();
        printf("开始体验吧!\n请选择序号：");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            game();
            rank();
            break;
        case 2:
            return 0;
    		break;
        case 3:  
    	 	list();//排行
    	case 4:
			delete();
			break;
        default:
            printf("选择错误！\n");
        }
    }
    while (input);//do while 循环
return 0;
}
