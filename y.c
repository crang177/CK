#include"stdio.h"
#include"y.h"
#include<windows.h>
#include<time.h>
#include<string.h>
//#include<conio.h>




//  ��궨λ����
void gotoxy(int x,int y)
{
    COORD p;//����ṹ�����p
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��ǰ�������
	p.X=x;p.Y=y;//������Ŀ���ƶ�λ�ô��ݸ��ṹ��
	SetConsoleCursorPosition(handle,p);//�ƶ����
}





char **cptr;//ָ�����ĵ��ʵ�ָ���ָ������
char **eptr;//ָ��Ӣ�ĵ��ʵ�ָ���ָ������
int QNO;//��������
//��ȡ���ʴ����ļ�
int read()
{
    FILE *fp;
    char filename[30];
    printf("�����뵥�ʴ����ļ�����\n");
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




#define CNO 4//ѡ������Ϊ4
//make������������ĸ���ѡ�������ȷ�𰸵��±�
int make(int c[],int n)
{
    int i,j,x;
    c[0]=n;//����ȷ�𰸷��ڵ�һ��Ԫ��
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





void print(const int c[],int sw)//����ĸ���
{
    int i;
    for(i=0;i<CNO;i++)
    {
        printf("(%d)%s",i,sw?cptr[c[i]]:eptr[c[i]]);
        printf(":    ");
    }
}




int score=0;
//��һ������ʵ�ֺ���
int run()
{
    int i;
    int nq,pq;//��Ŀ��ź���һ�ε���Ŀ���
    int na;//��ȷ�𰸵ı��
    int sw;//��Ŀ���ԣ�0Ϊ���ģ�1ΪӢ��
    int retry;//�Ƿ�������ս
    int cand[CNO];//ѡ��ı��


    if(read()==1){
        printf("\a�����ļ���ʧ�ܡ�\n");
        return 1;
    }

    srand(time(NULL));//�趨���������

    pq=QNO;

   do{
       int no;
       do{
            nq=rand()%QNO;
       }while(nq==pq);

       na=make(cand,nq);
       sw=rand()%2;
       printf("��һ����%s?\n",sw?eptr[nq]:cptr[nq]);

       do{
          print(cand,sw);
          scanf("%d",&no);
          if(no!=na) {
            puts("        �Բ������Ļش���󣬼���10��");
            score-=10;
                }
         }while(no!=na);

        puts("        ���Ļش���ȷ����10��");
        score+=10;
        pq=nq;
        printf("    �Ƿ�����һ��?0-��/1-�ǣ�");
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










//��Ϸ��ʼ���溯��
void Start()
{
    int i,j;
    gotoxy(23,2);
    printf("Ӣ�ﵥ�ʹ�����ϰ");


    for(i=5;i<=11;i++)
    {
        for(j=6;j<=55;j++)
        {
            gotoxy(j,i);
            if(i==5||i==11)                             printf("*");
            else if(j==6||j==55)                      printf("��");
        }
    }

    gotoxy(12,7);                                                  printf("1.��ʼ��ϰ");
    gotoxy(32,7);                                                  printf("2.���ֹ���");
    gotoxy(12,9);                                                  printf("3.�˳���ϰ");
    gotoxy(12,12);                                                 printf("��ѡ��[1 2 3]:[ ]");
    gotoxy(27,12);//ʹ�ù�굽[ ]֮��


    int n;
    scanf("%d", &n);
    switch(n)
    {
    case 1:
        system("cls");//����
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
        printf("������1~3�����֣�");
        getch();//�û��������ⰴ��,getch����ͷ�ļ���conio.h��
        system("cls");//����
        Start();//�ٴ���ʾ��Ϸ��ʼ����
    }
}



void rule()
{
    system("cls");//����
    int i,j;
    gotoxy(23,2);                          printf("���ֹ���");
    for(i=3;i<=19;i++)
    {
        for(j=6;j<=55;j++)
        {
            gotoxy(j,i);
            if(i==3||i==19)            printf("*");
            else if(j==6||j==55)      printf("��");
        }
    }

    gotoxy(12,7);                                                  printf("����1����4��ѡ����ѡ���Ӧ�Ĵ���");
    gotoxy(12,9);                                                  printf("����2���ش���ȷ��10��");
    gotoxy(12,11);                                                printf("����3���ش�������10��");
    gotoxy(12,13);                                                printf("Esc���˳���ϰ");

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
    printf("\"����");
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
    printf("����\"");
    gotoxy(40,19);
    printf("-----------+");


}




void endgame()
{
    system("cls");
    lost();
    gotoxy(18,8);
    printf("�ۺϱ����ɼ�����ĵ÷���%d",score);
    if(score>=highscore){
        gotoxy(22,9);
        printf("����¼�ˣ���\n");
        file_in();
    }
    else {
        gotoxy(22,9);
        printf("���ͣ����%d��\n",highscore-score);
    }
    gotoxy(61,20);
    choose();
}



void choose()
{
    gotoxy(8,11); printf("1.������һ��");
    gotoxy(26,11); printf("2.�˳���ϰ");

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
        printf("��������ȷ����");

    }
}
