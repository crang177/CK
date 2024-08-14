#include"stdio.h"
#include"y.h"
#include<windows.h>
#include<time.h>
#include<string.h>
//#include<conio.h>




//  光标定位函数
void gotoxy(int x,int y)
{
    COORD p;//定义结构体变量p
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前函数句柄
	p.X=x;p.Y=y;//将光标的目标移动位置传递给结构体
	SetConsoleCursorPosition(handle,p);//移动光标
}





char **cptr;//指向中文单词的指针的指针数组
char **eptr;//指向英文单词的指针的指针数组
int QNO;//单词数量
//读取单词储存文件
int read()
{
    FILE *fp;
    char filename[30];
    printf("请输入单词储存文件名：\n");
    scanf("%s",filename);
    fp=fopen(filename,"r");
    if(fp==NULL)                return 1;
    fscanf(fp,"%d",&QNO);

    if((cptr=calloc(QNO,sizeof(char*)))==NULL)   return 1;
    if((eptr=calloc(QNO,sizeof(char*)))==NULL)   return 1;

    int i;
    for(i=0;i<QNO;i++)
    {
        char ctemp[1024];
        char etemp[1024];
        fscanf(fp,"%s%s",etemp,ctemp);

        if((eptr[i]=malloc(strlen(etemp)+1))==NULL)   return 1;
        if((cptr[i]=malloc(strlen(ctemp)+1))==NULL)   return 1;
        strcpy(eptr[i],etemp);
        strcpy(cptr[i],ctemp);
    }

    fclose(fp);
    return 0;
}




#define CNO 4//选项数量为4
//make函数随机产生四个答案选项并返回正确答案的下标
int make(int c[],int n)
{
    int i,j,x;
    c[0]=n;//把正确答案放在第一个元素
    for(i=1;i<CNO;i++)
    {
        do{
            x=rand()%QNO;
            for(j=0;j<i;j++)
            {
                if(c[j]==x)   break;
            }
        }while (i!=j);
        c[i]=x;
    }
    int t;
    j=rand()%CNO;
    if(j!=0){
        t=c[0];
        c[0]=c[j];
        c[j]=t;
    }

    return j;
}





void print(const int c[],int sw)//输出四个答案
{
    int i;
    for(i=0;i<CNO;i++)
    {
        printf("(%d)%s",i,sw?cptr[c[i]]:eptr[c[i]]);
        printf(":    ");
    }
}




int score=0;
//第一个功能实现函数
int run()
{
    int i;
    int nq,pq;//题目编号和上一次的题目编号
    int na;//正确答案的编号
    int sw;//题目语言，0为中文，1为英文
    int retry;//是否重新挑战
    int cand[CNO];//选项的编号


    if(read()==1){
        printf("\a单词文件打开失败。\n");
        return 1;
    }

    srand(time(NULL));//设定随机数种子

    pq=QNO;

   do{
       int no;
       do{
            nq=rand()%QNO;
       }while(nq==pq);

       na=make(cand,nq);
       sw=rand()%2;
       printf("哪一个是%s?\n",sw?eptr[nq]:cptr[nq]);

       do{
          print(cand,sw);
          scanf("%d",&no);
          if(no!=na) {
            puts("        对不起，您的回答错误，减掉10分");
            score-=10;
                }
         }while(no!=na);

        puts("        您的回答正确，加10分");
        score+=10;
        pq=nq;
        printf("    是否再来一次?0-否/1-是：");
        scanf("%d",&retry);
   }while(retry==1);

    for(i=0;i<QNO;i++)   {
        free(eptr[i]);
        free(cptr[i]);
   }
    free(eptr);
    free(cptr);
    file_out();
    endgame();
    exit(0);
    return 0;

}










//游戏开始界面函数
void Start()
{
    int i,j;
    gotoxy(23,2);
    printf("英语单词巩固练习");


    for(i=5;i<=11;i++)
    {
        for(j=6;j<=55;j++)
        {
            gotoxy(j,i);
            if(i==5||i==11)                             printf("*");
            else if(j==6||j==55)                      printf("★");
        }
    }

    gotoxy(12,7);                                                  printf("1.开始练习");
    gotoxy(32,7);                                                  printf("2.积分规则");
    gotoxy(12,9);                                                  printf("3.退出练习");
    gotoxy(12,12);                                                 printf("请选择[1 2 3]:[ ]");
    gotoxy(27,12);//使得光标到[ ]之间


    int n;
    scanf("%d", &n);
    switch(n)
    {
    case 1:
        system("cls");//清屏
        run();
        break;
    case 2:
        rule();
        break;
    case 3:
        exit(0);
        break;
    default:
        gotoxy(12,14);
        printf("请输入1~3的数字！");
        getch();//用户输入任意按键,getch函数头文件在conio.h中
        system("cls");//清屏
        Start();//再次显示游戏开始界面
    }
}



void rule()
{
    system("cls");//清屏
    int i,j;
    gotoxy(23,2);                          printf("积分规则");
    for(i=3;i<=19;i++)
    {
        for(j=6;j<=55;j++)
        {
            gotoxy(j,i);
            if(i==3||i==19)            printf("*");
            else if(j==6||j==55)      printf("★");
        }
    }

    gotoxy(12,7);                                                  printf("规则1：从4个选项里选择对应的词义");
    gotoxy(12,9);                                                  printf("规则2：回答正确加10分");
    gotoxy(12,11);                                                printf("规则3：回答错误减掉10分");
    gotoxy(12,13);                                                printf("Esc：退出练习");

    gotoxy(1,20);
    getch();
    system("cls");
    Start();
}



int highscore=0;
void file_out()
{
    FILE *fp;
    fp=fopen("save.txt","a+");
    fscanf(fp,"%d",&highscore);
    fclose(fp);
}

void file_in()
{
    FILE *fp;
    fp=fopen("save.txt","w+");
    fprintf(fp,"%d",score);
    fclose(fp);

}


void lost()
{
    system("cls");
    int i;
    gotoxy(6,3);
    printf("+----------");
    gotoxy(17,3);
    printf("\"★★★");
    gotoxy(21,3);         printf("------------------------------+");
    for(i=4;i<=18;i++)
    {
        gotoxy(6,i)  ;
        printf("|");
        gotoxy(51,i)  ;
        printf("|");
    }

    gotoxy(6,19);
    printf("+----------------------------------------");
    gotoxy(36,19);
    printf("★★★\"");
    gotoxy(40,19);
    printf("-----------+");


}




void endgame()
{
    system("cls");
    lost();
    gotoxy(18,8);
    printf("综合比赛成绩，你的得分是%d",score);
    if(score>=highscore){
        gotoxy(22,9);
        printf("创纪录了！！\n");
        file_in();
    }
    else {
        gotoxy(22,9);
        printf("加油！相差%d分\n",highscore-score);
    }
    gotoxy(61,20);
    choose();
}



void choose()
{
    gotoxy(8,11); printf("1.重新来一次");
    gotoxy(26,11); printf("2.退出练习");

    gotoxy(50,20);printf("( )");
    gotoxy(51,20);
    int n;
    scanf("%d",&n);
    switch(n){
    case 1 :
        system("cls");
        score=0;
        run();
        break;
    case 2:
        exit(0);
        break;
    default:
        printf("请输入正确数字");

    }
}
