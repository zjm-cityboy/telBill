#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_NUM  6
#define FDT   1    // 固定长途
#define FLT   2    // 固定本地
#define WDT   4    // 无线长途
#define WLT   8    // 无限本地
#define WAP   16   // 无线接听

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
    printf("      *           欢迎进入电信查询系统!          *\n");
    if(NULL == loginUser)
    {
        printf("      *           当前用户: 未登录               *\n");
    }
    else
    {
        printf("      *           当前用户: %s          *\n",loginUser);
    }
    printf("      ********************************************\n");
    printf("                  1. 登陆系统\n");
    printf("                  2. 查询电话账单\n");
    printf("                  3. 退出登录状态\n");
    printf("                  0. 退出\n");
    printf("      说明:  功能1输入您的手机号码和预设密码\n");
    printf("      说明:  功能2查询您本月电话明细和总费用\n");
    printf("      说明:  功能3退出登录\n");
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
        printf("\n      手机号或者密码输入有误,请重新输入!\n");
        printf("      输入您的手机号:\n");
        printf("      手机号:");
        //fgets(user,12,stdin);
        scanf("%s",user);
        printf("      密码  :");
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
        printf("      你输入的错误次数太多了!\n\n");
        welcome_ui(NULL);
    }
    else
    {
        matchState = matchUserAndCode(user,code);
        switch(matchState)
        {
            case 0:
                clear_screen();
                printf("      \n登陆成功!\n\n");
                strncpy(ss,user,11);
                ss[11] ='\0';
                login_flag =1 ;
                welcome_ui(user);
                break;

            case 1:
                clear_screen();
                printf("      \n没有此用户!\n\n");
                welcome_ui(NULL);
                break;

            case 2:
                clear_screen();
                printf("      \n密码错误!\n\n");
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
                printf("      信息被非法篡改!\n");
                welcome_ui(loginUser);
                break;
            }
        }


     }
     printf("\n      您的账单如下:\n");
     printf("      用户名:%s\n",userTel[id]);
     printf("      固定长途电话:%d分钟,产生费用为%.2f元\n",tel_time[id][0],0.02*tel_time[id][0]);
     printf("      固定本地电话:%d分钟,产生费用为%.2f元\n",tel_time[id][1],0.06*tel_time[id][1]);
     printf("      无线长途电话:%d分钟,产生费用为%.2f元\n",tel_time[id][2],1.00*tel_time[id][2]);
     printf("      无线本地电话:%d分钟,产生费用为%.2f元\n",tel_time[id][3],0.60*tel_time[id][3]);
     printf("      无线接听电话:%d分钟,产生费用为%.2f元\n",tel_time[id][4],0.50*tel_time[id][4]);
     printf("      总计产生费用为%.2f元\n\n",0.02*tel_time[id][0]\
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
        printf("      请输入功能号:");
        scanf("%d",&user_choice);
        if( 1 == user_choice )
        {
            login(activeUser);
        }
        else if(2 == user_choice)
        {
            if( 0 == login_flag)
            {
                printf("\n      请先登录系统!\n\n");
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
            printf("\n      再见!\n");
            flag =0 ;
        }

    }
    system("pause");
    return 0;
}
