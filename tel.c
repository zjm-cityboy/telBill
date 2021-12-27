#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_NUM  6
#define FDT   1    // �̶���;
#define FLT   2    // �̶�����
#define WDT   4    // ���߳�;
#define WLT   8    // ���ޱ���
#define WAP   16   // ���߽���

char *userTel[USER_NUM] ={"13344558856","13517224220","13339988412","15271766778","13429806441","18062612126"};
char *codeStr[USER_NUM] ={"443sin","89yut1","hgt5r3","yv332a","rrh44c","0dh52m"};
static int login_flag =0 ;

void clear_screen()
{
    system("cls");
}

void welcome_ui(const char *loginUser)
{
    printf("--------------------------------------------------------------------------------\n");
    printf("      ********************************************\n");
    printf("      *                                          *\n");
    printf("      *           ��ӭ������Ų�ѯϵͳ!          *\n");
    if(NULL == loginUser)
    {
        printf("      *           ��ǰ�û�: δ��¼               *\n");
    }
    else
    {
        printf("      *           ��ǰ�û�: %s          *\n",loginUser);
    }
    printf("      ********************************************\n");
    printf("                  1. ��½ϵͳ\n");
    printf("                  2. ��ѯ�绰�˵�\n");
    printf("                  3. �˳���¼״̬\n");
    printf("                  0. �˳�\n");
    printf("      ˵��:  ����1���������ֻ������Ԥ������\n");
    printf("      ˵��:  ����2��ѯ�����µ绰��ϸ���ܷ���\n");
    printf("      ˵��:  ����3�˳���¼\n");
    printf("--------------------------------------------------------------------------------\n");

}

int matchUserAndCode(const char *tel,const char *code)
{
    int ret = -1,i =0,id =-1;
    if(NULL == tel || NULL == code )
        return -1;
    for(i =0 ;i < USER_NUM;i++)
    {
        if( 0 ==strncmp(tel,userTel[i],11) )
        {
            id = i ;
            ret =0 ;
            break;
        }

    }
    if(-1 == ret)
    {
         ret = 1;
         return ret ;
    }

    if( 0 != strncmp(code,codeStr[id],6) )
    {
        ret = 2 ;
    }
    return ret ;
}


void login(char ss[])
{
    char user[12] ="\0",code[7] ="\0";
    int  matchState =0,count =1;
    while(count <= 3)
    {
        if(count >1)
        printf("\n      �ֻ��Ż���������������,����������!\n");
        printf("      ���������ֻ���:\n");
        printf("      �ֻ���:");
        //fgets(user,12,stdin);
        scanf("%s",user);
        printf("      ����  :");
        //fgets(code,7,stdin);
        scanf("%s",code);
        if(11 == strlen(user) && 6 == strlen(code))
            break;
        else
        {
            count++;
        }
    }
    if(count >=4)
    {
        clear_screen();
        printf("      ������Ĵ������̫����!\n\n");
        welcome_ui(NULL);
    }
    else
    {
        matchState = matchUserAndCode(user,code);
        switch(matchState)
        {
            case 0:
                clear_screen();
                printf("      \n��½�ɹ�!\n\n");
                strncpy(ss,user,11);
                ss[11] ='\0';
                login_flag =1 ;
                welcome_ui(user);
                break;

            case 1:
                clear_screen();
                printf("      \nû�д��û�!\n\n");
                welcome_ui(NULL);
                break;

            case 2:
                clear_screen();
                printf("      \n�������!\n\n");
                welcome_ui(NULL);
                break;

            default:
                break;

        }
    }
}

int queryBill(const char *loginUser)
{
    int i = 0,j =0,id =-1;
    int k[6][2] = {0};
    int tel_time[6][5] = {0};
    char *ss[] ={"./FDT.txt","./FLT.txt","./WDT.txt","./WLT.txt","./WAP.txt"};

    for(i =0 ;i < USER_NUM;i++)
    {
        if( 0 == strncmp(loginUser,userTel[i],6) )
        {
            id = i ;
            break;
        }
    }
    if(id <0 || id >5)
        return  -2;
    for(i =0;i < 5; i++)
    {
        FILE *fpRead = fopen(ss[i], "r");
        if (NULL == fpRead)
        {
            return -1;
        }
        j =0 ;
        while ( fscanf(fpRead, "%d|%d",\
                              &k[j][0], &k[j][1]) !=EOF )
        {
           // printf("line=%d,value =%d\n",k[j][0], k[j][1]);
            if(j >5)
                break;
            else
                j++;

        }
        fclose(fpRead);

        for(j =0 ;j < 6;j++)
        {
            if(k[j][0] >=1 && k[j][0] <=6)
            {
                tel_time[k[j][0]-1][i] = k[j][1];
                j++;
            }
            else
            {
                printf("      ��Ϣ���Ƿ��۸�!\n");
                welcome_ui(loginUser);
                break;
            }
        }


     }
     printf("\n      �����˵�����:\n");
     printf("      �û���:%s\n",userTel[id]);
     printf("      �̶���;�绰:%d����,��������Ϊ%.2fԪ\n",tel_time[id][0],0.02*tel_time[id][0]);
     printf("      �̶����ص绰:%d����,��������Ϊ%.2fԪ\n",tel_time[id][1],0.06*tel_time[id][1]);
     printf("      ���߳�;�绰:%d����,��������Ϊ%.2fԪ\n",tel_time[id][2],1.00*tel_time[id][2]);
     printf("      ���߱��ص绰:%d����,��������Ϊ%.2fԪ\n",tel_time[id][3],0.60*tel_time[id][3]);
     printf("      ���߽����绰:%d����,��������Ϊ%.2fԪ\n",tel_time[id][4],0.50*tel_time[id][4]);
     printf("      �ܼƲ�������Ϊ%.2fԪ\n\n",0.02*tel_time[id][0]\
            +0.06*tel_time[id][1]+1.00*tel_time[id][2]\
            +0.60*tel_time[id][3]+0.50*tel_time[id][4]);

}

void loginOut(char *user)
{
    if(NULL == user)
        return;
    //user[0] ='\0';
    login_flag =0 ;
    clear_screen();
    welcome_ui(NULL);
}

int main(void)
{
    char activeUser[12] = {"\0"};
    int user_choice =-1 ,flag =1;

    welcome_ui(NULL);
    while(flag)
    {
        printf("      �����빦�ܺ�:");
        scanf("%d",&user_choice);
        if( 1 == user_choice )
        {
            login(activeUser);
        }
        else if(2 == user_choice)
        {
            if( 0 == login_flag)
            {
                printf("\n      ���ȵ�¼ϵͳ!\n\n");
                welcome_ui(NULL);
            }
            else
            {
                queryBill(activeUser);
            }
        }
        else if(3 == user_choice)
        {
            loginOut(activeUser);
        }
        else if( 0 == user_choice)
        {
            printf("\n      �ټ�!\n");
            flag =0 ;
        }

    }
    system("pause");
    return 0;
}
