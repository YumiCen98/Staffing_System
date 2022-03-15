#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "Staff.h"
#include "Connect.h"
#include "Sqlite.h"
#include "Operation.h"

/*给线程处理函数传递参数的结构体*/
typedef struct{
    int acceptfd;
    struct sockaddr_in clientaddr;
    MSG msg;
    sqlite3 *db;
}FD_MSG;


/*线程处理函数*/
void *thread_fun(void *arg)
{
    FD_MSG fd_msg = *(FD_MSG *)arg;
    int bytes, ret;

    while(1)
    {
        memset(&fd_msg.msg, 0, sizeof(MSG));
        printf(FONT_COLOR_YELLOW"[%s:%d]"COLOR_NONE, inet_ntoa(fd_msg.clientaddr.sin_addr), ntohs(fd_msg.clientaddr.sin_port));

        /*判断客户端是否退出*/
        if((bytes = RecvMsg(fd_msg.acceptfd, &fd_msg.msg)) == 0)
        {
            printf(FONT_COLOR_YELLOW"已退出\n"COLOR_NONE);
            close(fd_msg.acceptfd);
            break;
        }

        /*用于保存数据库操作命令*/
        char sqlcmd[256] = {0};
        /*记录操作时间*/
        char date[20] = "";

        printf("OptCode = %d\n", fd_msg.msg.optcode);
        getdate(date);

        /**
         * 表键值：
         * staff_info(class int, account text primary key, passwd text, name text, sex text, duty text, pay int, phone int, address text, regist_date text)
         * clock_info(account text, name text, clock_date text)
         */

        switch(fd_msg.msg.optcode)
        {
            case LOGIN:
                printf(FONT_COLOR_YELLOW"登录信息\n"COLOR_NONE);
                printf("Account:%s\nPasswd:%s\n", fd_msg.msg.user.account, fd_msg.msg.user.passwd);
                sprintf(sqlcmd, "select * from staff_info where account = '%s' and passwd = '%s'", fd_msg.msg.user.account, fd_msg.msg.user.passwd);
                login(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                sprintf(sqlcmd, "update staff_info set login_count=login_count+1 where account = '%s'", fd_msg.msg.user.account);
                sql_exec(fd_msg.db, sqlcmd);
                //printf("%s\n", sqlite3_errmsg(fd_msg.db));
                break;

            case STAFF_REGIST:
                printf(FONT_COLOR_YELLOW"员工注册信息\n"COLOR_NONE);
                printf("Account:%s\nPasswd:%s\n", fd_msg.msg.user.account, fd_msg.msg.user.passwd);
                sprintf(sqlcmd, "insert into staff_info values(0, '%s', '%s', 'NULL', 'NULL', '普通员工', 12000, 'NULL', 'NULL', '%s', 0)", fd_msg.msg.user.account, fd_msg.msg.user.passwd, date);
                regist(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;
                
            case MANAGER_REGIST:
                printf(FONT_COLOR_YELLOW"管理员注册信息\n"COLOR_NONE);
                printf("Account:%s\nPasswd:%s\n", fd_msg.msg.user.account, fd_msg.msg.user.passwd);
                sprintf(sqlcmd, "insert into staff_info values(1, '%s', '%s', 'NULL', 'NULL', '管理员', 15000, 'NULL', 'NULL', '%s', 0)", fd_msg.msg.user.account, fd_msg.msg.user.passwd, date);
                regist(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;

            case STAFF_SHOW:
                printf(FONT_COLOR_YELLOW"个人信息\n"COLOR_NONE);
                sprintf(sqlcmd, "select * from staff_info where account = '%s'", fd_msg.msg.user.account);
                user_show(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;

            case STAFF_MODIFY:
                printf(FONT_COLOR_YELLOW"修改个人信息\n"COLOR_NONE);
                if(strcmp(fd_msg.msg.choose, "passwd") == 0)        /*修改密码*/
                {
                    sprintf(sqlcmd, "update staff_info set passwd = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.user.account);
                }
                else if(strcmp(fd_msg.msg.choose, "name") == 0)     /*修改姓名*/
                {
                    sprintf(sqlcmd, "update staff_info set name = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.user.account);
                }
                else if(strcmp(fd_msg.msg.choose, "sex") == 0)      /*修改性别*/
                {
                    sprintf(sqlcmd, "update staff_info set sex = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.user.account);
                }
                else if(strcmp(fd_msg.msg.choose, "phone") == 0)    /*修改电话*/
                {
                    sprintf(sqlcmd, "update staff_info set phone = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.user.account);
                }
                else if(strcmp(fd_msg.msg.choose, "address") == 0)  /*修改地址*/
                {
                    sprintf(sqlcmd, "update staff_info set address = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.user.account);
                }
                else
                    break;
                user_modify(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;

            case STAFF_CLOCK:
                printf(FONT_COLOR_YELLOW"打卡\n"COLOR_NONE);
                printf("Account:%s\nName:%s\nDate:%s\n", fd_msg.msg.user.account, fd_msg.msg.user.name, date);
                sprintf(sqlcmd, "insert into clock_info values('%s', '%s', '%s')", fd_msg.msg.user.account, fd_msg.msg.user.name, date);
                user_clock(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;

            case HISTORY_SHOW:
                printf(FONT_COLOR_YELLOW"查询历史打卡\n"COLOR_NONE);
                printf("Account:%s\nPasswd:%s\n", fd_msg.msg.user.account, fd_msg.msg.user.passwd);
                sprintf(sqlcmd, "select * from clock_info where account = '%s'", fd_msg.msg.user.account);
                user_history_clock(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;

            case MANAGER_SHOW:
                printf(FONT_COLOR_YELLOW"员工信息\n"COLOR_NONE);
                sprintf(sqlcmd, "select * from staff_info where account = '%s'", fd_msg.msg.data);
                ret = user_show(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;

            case MANAGER_MODIFY:
                printf(FONT_COLOR_YELLOW"修改员工信息\n"COLOR_NONE);
                if(strcmp(fd_msg.msg.choose, "passwd") == 0)        /*修改密码*/
                {
                    sprintf(sqlcmd, "update staff_info set passwd = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.text);
                }
                else if(strcmp(fd_msg.msg.choose, "name") == 0)     /*修改姓名*/
                {
                    sprintf(sqlcmd, "update staff_info set name = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.text);
                }
                else if(strcmp(fd_msg.msg.choose, "sex") == 0)      /*修改性别*/
                {
                    sprintf(sqlcmd, "update staff_info set sex = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.text);
                }
                else if(strcmp(fd_msg.msg.choose, "duty") == 0)      /*修改职务*/
                {
                    sprintf(sqlcmd, "update staff_info set duty = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.text);
                }
                else if(strcmp(fd_msg.msg.choose, "pay") == 0)      /*修改薪资*/
                {
                    sprintf(sqlcmd, "update staff_info set pay = %d where account = '%s'", atoi(fd_msg.msg.data), fd_msg.msg.text);
                }
                else if(strcmp(fd_msg.msg.choose, "phone") == 0)    /*修改电话*/
                {
                    sprintf(sqlcmd, "update staff_info set phone = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.text);
                }
                else if(strcmp(fd_msg.msg.choose, "address") == 0)  /*修改地址*/
                {
                    sprintf(sqlcmd, "update staff_info set address = '%s' where account = '%s'", fd_msg.msg.data, fd_msg.msg.text);
                }
                else
                    break;
                user_modify(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;

            case DELETE_STAFF:
                printf(FONT_COLOR_YELLOW"删除员工信息\n"COLOR_NONE);
                printf("Account:%s\nName:%s\n", fd_msg.msg.user.account, fd_msg.msg.user.name);
                sprintf(sqlcmd, "delete from staff_info where account = '%s'", fd_msg.msg.data);
                ret = user_delete(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;
            case NEW_USER_JUDGE:
                printf(FONT_COLOR_YELLOW"判断新用户\n"COLOR_NONE);
                sprintf(sqlcmd, "select * from staff_info where account = '%s' and login_count = 1", fd_msg.msg.user.account);
                ret = new_user_judge(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;
            case ADD_USER_INFO:
                printf(FONT_COLOR_YELLOW"完善用户信息\n"COLOR_NONE);
                sprintf(sqlcmd, "update staff_info set name = '%s', sex = '%s', phone = '%s', address = '%s' where account = '%s'", \
                    fd_msg.msg.user.name, fd_msg.msg.user.sex, fd_msg.msg.user.phone, fd_msg.msg.user.address, fd_msg.msg.user.account);
                //printf("%s\n", sqlcmd);
                ret = add_user_info(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                //printf("add: %d-%s\n", ret, sqlite3_errmsg(fd_msg.db));
                break;
            case ALL_SHOW:
                printf(FONT_COLOR_YELLOW"查询所有员工\n"COLOR_NONE);
                sprintf(sqlcmd, "select * from staff_info");
                ret = user_show(fd_msg.acceptfd, fd_msg.msg, fd_msg.db, sqlcmd);
                break;
        }
    }
}

int main(int argc, char const *argv[])
{
    FD_MSG fd_msg;
    char date[256]="";

    if(argc < 3)
    {
        printf("Usage：%s <ip> <port>\n", argv[0]);
        return -1;
    }

    /*TCP*/
    int sockfd, clientfd;
    struct sockaddr_in clientaddr;
    MSG msg;
    int bytes, ret;

    /*Sqlite3*/
    sqlite3 *user_db;
    sqlite3 *book_db;
    char *errmsg;
    char sqlcmd[256];


    /*创建服务器*/
    if((sockfd = CreateServer(argv[1], argv[2])) < 0)
    {
        printf("create server error\n");
        return -1;
    }


    /*创建/打开数据库*/
    fd_msg.db = sql_open(DATANAME, fd_msg.db);

    /*创建员工信息表:{等级(0-普通员工 1-管理员)，账号(primary key)，密码，姓名，性别，职务，薪资，电话，住址，注册时间}*/
    getdate(date);
    sprintf(sqlcmd, "create table staff_info(class int, account text primary key, passwd text, name text, sex text, duty text, pay int, phone int, address text, regist_date text, login_count int)");
    ret = sql_exec(fd_msg.db, sqlcmd);
    if(0 == ret)
    {
        printf(FONT_COLOR_YELLOW"[创建表成功]\n"COLOR_NONE);
    }
    else
    {
        /*这里传递过来的errmsg输出会乱码，所以这里调用函数sqlite3_errmsg*/
        printf(FONT_COLOR_RED"[创建表失败]:%s\n"COLOR_NONE, sqlite3_errmsg(fd_msg.db));
    }
    memset(date, 0, sizeof(date));

    /*员工打卡表:{账号、姓名、打卡时间}*/
    getdate(date);
    sprintf(sqlcmd, "create table clock_info(account text, name text, clock_date text)");
    ret = sql_exec(fd_msg.db, sqlcmd);
    if(0 == ret)
    {
        printf(FONT_COLOR_YELLOW"[创建表成功]\n"COLOR_NONE);
    }
    else
    {
        printf(FONT_COLOR_RED"[创建表失败]:%s\n"COLOR_NONE, sqlite3_errmsg(fd_msg.db));
    }
    memset(date, 0, sizeof(date));


    /*使用对线程实现TCP并发服务器*/
    pthread_t thread;

    while(1)
    {
        /*等待客户端连接，并保存客户端的地址*/
        if((clientfd = WaitConnect(sockfd, &clientaddr)) < 0)
        {
            printf("connect server error\n");
            return -1;
        }

        /*将参数传递到结构体中*/
        fd_msg.acceptfd = clientfd;
        fd_msg.clientaddr = clientaddr;

        /*创建线程，实现并发*/
        if(pthread_create(&thread, NULL, thread_fun, &fd_msg) != 0)
        {
            ERR_LOG("fail to pthread_create");
        }

        /*设置线程为分离属性，线程退出时释放资源*/
        pthread_detach(thread);
    }

    return 0;
}
