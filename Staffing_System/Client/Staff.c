#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "Staff.h"
#include "Connect.h"
#include "User.h"

int main(int argc, char const *argv[])
{
    if(argc < 3)
    {
        printf(FONT_COLOR_RED"[Usage：%s <ip> <port>]\n"COLOR_NONE, argv[0]);
        return -1;
    }

    int sockfd, clientfd;
    int bytes, ret, i;
    char Opt;
    MSG msg;
    struct sockaddr_in clientaddr;

    sockfd = ConnectServer(argv[1], argv[2]);

    while(1)
    { 
HOME_PAGE:
        memset(&msg, 0, sizeof(MSG));
        home_page();

        printf(FONT_COLOR_BLUE"input:>"COLOR_NONE);
        scanf("%c", &Opt);
        getchar();
        switch(Opt)
        {
            /*退出程序*/
            case 'E':
                exit(0);

            /*用户登录*/
            case 'L':
LOGIN_ACCOUNT:
                msg.optcode = 0;
                printf(FONT_COLOR_YELLOW"[User Login]\n"COLOR_NONE);
                printf(FONT_COLOR_BLUE"Account:>"COLOR_NONE);
                //fgets(msg.user.account, strlen(msg.user.account), stdin);
                //msg.user.account[strlen(msg.user.account) - 1] = '\0';
                scanf("%s", msg.user.account);
                getchar();
                for(i=0; i<strlen(msg.user.account); i++)
                {
                    /*判断账号是否纯数字*/
                    if( (!(isdigit(msg.user.account[i]))) || (msg.user.account[0] != '1') || (strlen(msg.user.account) != 11) )
                    {
                        //printf(FONT_COLOR_RED"账号格式不正确，请重新输入\n"COLOR_NONE);
                        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                        printf(BACK_WHITE_FONT_BLUE"\t\t           < 账号格式不正确，请重新输入！ >           \n"COLOR_NONE);     
                        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                        printf("\n");
                        memset(msg.user.account, 0, N);
                        goto LOGIN_ACCOUNT;
                    }
                }
LOGIN_PASSWD:
                printf(FONT_COLOR_BLUE"Password:>"COLOR_NONE);
                //fgets(msg.user.passwd, strlen(msg.user.passwd), stdin);
                //msg.user.passwd[strlen(msg.user.passwd) - 1] = '\0';
                scanf("%s", msg.user.passwd);
                getchar();
                if( (strlen(msg.user.passwd) < 8) || (strlen(msg.user.passwd) > 16) )
                {
                    //printf(FONT_COLOR_RED"密码为8~16位，请重新输入\n"COLOR_NONE);
                    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                    printf(BACK_WHITE_FONT_BLUE"\t\t            < 密码为8~16位，请重新输入 >             \n"COLOR_NONE);     
                    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                    printf("\n");
                    memset(msg.user.passwd, 0, N);
                    goto LOGIN_PASSWD;
                }

                ret = login(sockfd, msg);
                if(1 == ret)
                {
                    //printf(FONT_COLOR_YELLOW"[登录成功，跳转中...]\n"COLOR_NONE);
                    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                    printf(BACK_WHITE_FONT_BLUE"\t\t               < 登录成功，跳转中... >              \n"COLOR_NONE);     
                    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                    printf("\n");

                    sleep(1);

                    ret = new_user_judge(sockfd, msg);
                    if(0 == ret)
                    {
                        //add_info(sockfd, msg);
                        msg.optcode = 11;
                        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                        printf(BACK_WHITE_FONT_BLUE"\t\t           <!>新用户初次登录请完善以下信息          \n"COLOR_NONE);    
                        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                        printf("\n");   
                        printf(FONT_COLOR_BLUE"姓名:>"COLOR_NONE);
                        scanf("%s", msg.user.name);
                        getchar();
                        printf(FONT_COLOR_BLUE"性别:>"COLOR_NONE);
                        scanf("%s", msg.user.sex);
                        getchar();
                        printf(FONT_COLOR_BLUE"电话:>"COLOR_NONE);
                        scanf("%s", msg.user.phone);
                        getchar();
                        printf(FONT_COLOR_BLUE"住址:>"COLOR_NONE);
                        scanf("%s", msg.user.address);
                        getchar();

                        SendMsg(sockfd, &msg);
                        memset(msg.data, 0, sizeof(msg.data));
                        RecvMsg(sockfd, &msg);

                        if(strcmp(msg.data, "updata_info_success") == 0)
                        {
                            //printf(FONT_COLOR_YELLOW"信息完善成功\n"COLOR_NONE);
                            printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                            printf(BACK_WHITE_FONT_BLUE"\t\t                   < 信息完善成功 >                  \n"COLOR_NONE);     
                            printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                            printf("\n");
                        }
                        else
                        {
                            //printf(FONT_COLOR_YELLOW"信息添加失败\n"COLOR_NONE);
                            printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                            printf(BACK_WHITE_FONT_BLUE"\t\t                   < 信息添加失败 >                  \n"COLOR_NONE);     
                            printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                            printf("\n");
                        }
                        sleep(1);
                    }

                    user_center(sockfd, msg);   
                    goto HOME_PAGE;
                }
                else if(2 == ret)
                {
                    printf(FONT_COLOR_YELLOW"[登录成功，跳转中...]\n"COLOR_NONE);
                    sleep(1);
                    
                    ret = new_user_judge(sockfd, msg);
                    if(0 == ret)
                    {
                        //add_info(sockfd, msg);
                        msg.optcode = 11;
                        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                        printf(BACK_WHITE_FONT_BLUE"\t\t           <!>新用户初次登录请完善以下信息          \n"COLOR_NONE);
                        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                        printf("\n");   
                        printf(FONT_COLOR_BLUE"姓名:>"COLOR_NONE);
                        scanf("%s", msg.user.name);
                        getchar();
                        printf(FONT_COLOR_BLUE"性别:>"COLOR_NONE);
                        scanf("%s", msg.user.sex);
                        getchar();
                        printf(FONT_COLOR_BLUE"电话:>"COLOR_NONE);
                        scanf("%s", msg.user.phone);
                        getchar();
                        printf(FONT_COLOR_BLUE"住址:>"COLOR_NONE);
                        scanf("%s", msg.user.address);
                        getchar();

                        SendMsg(sockfd, &msg);
                        memset(msg.data, 0, sizeof(msg.data));
                        RecvMsg(sockfd, &msg);
                        //printf("%s\n", msg.data);
                        if(strcmp(msg.data, "updata_info_success") == 0)
                        {
                            //printf(FONT_COLOR_YELLOW"信息完善成功\n"COLOR_NONE);
                            printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                            printf(BACK_WHITE_FONT_BLUE"\t\t                   < 信息完善成功 >                  \n"COLOR_NONE);     
                            printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                            printf("\n");
                        }
                        else
                        {
                            //printf(FONT_COLOR_YELLOW"信息添加失败\n"COLOR_NONE);
                            printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                            printf(BACK_WHITE_FONT_BLUE"\t\t                   < 信息添加失败 >                  \n"COLOR_NONE);     
                            printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                            printf("\n");
                        }

                        sleep(1);
                    }

                    manage_center(sockfd, msg);
                    goto HOME_PAGE;
                }
                else if(0 == ret)
                {
                    //printf(FONT_COLOR_RED"[账号或密码错误]\n"COLOR_NONE);
                    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                    printf(BACK_WHITE_FONT_BLUE"\t\t                  < 账号或密码错误 >                 \n"COLOR_NONE);     
                    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                    printf("\n");
                }
                else
                {
                    //printf(FONT_COLOR_RED"[登录失败]\n"COLOR_NONE);
                    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                    printf(BACK_WHITE_FONT_BLUE"\t\t                     < 登录失败 >                   \n"COLOR_NONE);     
                    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
                    printf("\n");
                }
                sleep(1);
                break;
            
            /*员工注册*/
            case 'S':  
            /*管理员注册*/
            case 'M':
                if(Opt == 'S')
                {
                    msg.optcode = 1;
                    printf(FONT_COLOR_YELLOW"[Staff Regist]\n"COLOR_NONE);
                }
                else if(Opt == 'M')
                {
                    msg.optcode = 2;
                    printf(FONT_COLOR_YELLOW"[Manager Regist]\n"COLOR_NONE);
                }
                else
                {
                    printf(FONT_COLOR_RED"请输入正确的选项\n"COLOR_NONE);
                    break;
                }
GEGIST_ACCOUNT:
                printf(FONT_COLOR_BLUE"11位手机号:>"COLOR_NONE);
                //fgets(msg.user.account, strlen(msg.user.account), stdin);
                //msg.user.account[strlen(msg.user.account) - 1] = '\0';
                scanf("%s", msg.user.account);
                getchar();

                for(i=0; i<strlen(msg.user.account); i++)
                {
                    /*判断账号是否纯数字*/
                    if( (!(isdigit(msg.user.account[i]))) || (msg.user.account[0] != '1') || (strlen(msg.user.account) != 11) )
                    {
                        printf(FONT_COLOR_RED"账号格式不正确，请重新输入\n"COLOR_NONE);
                        memset(msg.user.account, 0, N);
                        goto GEGIST_ACCOUNT;
                    }
                }
GEGIST_PASSWD:
                printf(FONT_COLOR_BLUE"8~16位密码:>"COLOR_NONE);
                //fgets(msg.user.passwd, strlen(msg.user.passwd), stdin);
                //msg.user.passwd[strlen(msg.user.passwd) - 1] = '\0';
                scanf("%s", msg.user.passwd);
                getchar();

                if( (strlen(msg.user.passwd) < 8) || (strlen(msg.user.passwd) > 16) )
                {
                    printf(FONT_COLOR_RED"密码为8~16位，请重新输入\n"COLOR_NONE);
                    memset(msg.user.passwd, 0, N);
                    goto GEGIST_PASSWD;
                }

                ret = regist(sockfd, msg);
                if(0 == ret)
                {
                    printf(FONT_COLOR_YELLOW"[注册成功]\n"COLOR_NONE);
                }
                else if(1 == ret)
                {
                    printf(FONT_COLOR_RED"[用户存在]\n"COLOR_NONE);
                }
                else
                {
                    printf(FONT_COLOR_RED"[注册失败]\n"COLOR_NONE);
                }
                sleep(1);
                break;
            
            default:
                printf(FONT_COLOR_RED"请输入正确的选项\n"COLOR_NONE);
                sleep(1);
                break;
        }
    }

    return 0;
}
