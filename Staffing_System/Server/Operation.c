#include "Operation.h"

/**
 * @brief 注册
 * 
 * @param sockfd 
 * @param msg 
 * @param db 
 * @return int 
 */
int regist(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd)
{
    int ret = sql_exec(db, sqlcmd);
    memset(msg.data, 0, sizeof(msg.data));

    if(0 == ret)
    {
        strcat(msg.data, "regist_success");
        printf(FONT_COLOR_YELLOW"<%s>\n"COLOR_NONE, msg.data);
    }
    else if(1 == ret)
    {
        strcat(msg.data, "user_exist");
        printf(FONT_COLOR_YELLOW"<%s>\n"COLOR_NONE, msg.data);
    }
    else
    {
        strcat(msg.data, "regist_fail");
        printf(FONT_COLOR_RED"<%s>\n"COLOR_NONE, msg.data);
    }

    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
}

/**
 * @brief 登录
 * 
 * @param sockfd
 * @param msg 
 * @param db 
 * @return int 
 */
int login(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd)
{
    char staff_judge[128] = {0};
    char manager_judge[128] = {0};
    sprintf(staff_judge, "select * from staff_info where account = '%s' and class = 0", msg.user.account);
    sprintf(manager_judge, "select * from staff_info where account = '%s' and class = 1", msg.user.account);

    int ret = sql_judge(db, msg, sqlcmd);
    memset(msg.data, 0, sizeof(msg.data));

    if(0 == ret)
    {
        int ret1 = sql_judge(db, msg, staff_judge);
        int ret2 = sql_judge(db, msg, manager_judge);

        if(0 == ret1)
        {
            strcat(msg.data, "staff_login_success");
            printf(FONT_COLOR_YELLOW"<%s>\n"COLOR_NONE, msg.data);
        }
        if(0 == ret2)
        {
            strcat(msg.data, "manager_login_success");
            printf(FONT_COLOR_YELLOW"<%s>\n"COLOR_NONE, msg.data);
        }
    }
    else if(1 == ret)
    {
        strcat(msg.data, "info_error");
        printf(FONT_COLOR_YELLOW"<%s>\n"COLOR_NONE, msg.data);
    }
    else
    {
        strcat(msg.data, "login_fail");
        printf(FONT_COLOR_RED"<%s>\n"COLOR_NONE, msg.data);
    }

    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
}

/**
 * @brief 判断新用户
 * 
 * @param sockfd 
 * @param msg 
 * @param db 
 * @param sqlcmd 
 * @return int 
 */
int new_user_judge(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd)
{
    int ret = sql_judge(db, msg, sqlcmd);
    memset(msg.data, 0, sizeof(msg.data));
    if(0 == ret)
    {
        strcat(msg.data, "true");
        printf(FONT_COLOR_YELLOW"<%s>\n"COLOR_NONE, msg.data);
    }
    else
    {
        strcat(msg.data, "false");
        printf(FONT_COLOR_RED"<%s>\n"COLOR_NONE, msg.data);
    }

    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    return 0;
}

/**
 * @brief 新用户完善信息
 * 
 * @param sockfd 
 * @param msg 
 * @param db 
 * @param sqlcmd 
 * @return int 
 */
int add_user_info(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd)
{
    int ret = sql_exec(db, sqlcmd);
    memset(msg.data, 0, sizeof(msg.data));
    if(0 == ret)
    {
        strcat(msg.data, "updata_info_success");
        printf(FONT_COLOR_YELLOW"<%s>\n"COLOR_NONE, msg.data);
    }
    else
    {
        strcat(msg.data, "updata_info_fail");
        printf(FONT_COLOR_RED"<%s>\n"COLOR_NONE, msg.data);
    }

    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    return 0;
}

/**
 * @brief 查看个人或员工信息
 * 
 * @return int 
 */
int user_show(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd)
{
    sql_getdata(sockfd, msg, db, sqlcmd);

    return 0;
}

/**
 * @brief 修改个人或员工信息
 * 
 * @return int 
 */
int user_modify(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd)
{
    int ret = sql_exec(db, sqlcmd);
    memset(msg.data, 0, sizeof(msg.data));
    
    if(0 == ret)
    {
        strcat(msg.data, "modify_success");
        printf(FONT_COLOR_YELLOW"<%s>\n"COLOR_NONE, msg.data);
    }
    else
    {
        strcat(msg.data, "modify_fail");
        printf(FONT_COLOR_RED"<%s>\n"COLOR_NONE, msg.data);
    }

    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    return 0;
}

/**
 * @brief 员工打卡
 * 
 * @return int 
 */
int user_clock(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd)
{
    int ret = sql_exec(db, sqlcmd);
    memset(msg.data, 0, sizeof(msg.data));

    if(0 == ret)
    {
        strcat(msg.data, "clock_success");
        printf(FONT_COLOR_YELLOW"<%s>\n"COLOR_NONE, msg.data);
    }
    else
    {
        strcat(msg.data, "clock_fail");
        printf(FONT_COLOR_RED"<%s>\n"COLOR_NONE, msg.data);
    }

    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    return 0;
}

/**
 * @brief 个人、管理员查看历史打卡信息
 * 
 * @return int 
 */
void user_history_clock(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd)
{
    sql_getdata(sockfd, msg, db, sqlcmd);
}

/**
 * @brief 删除员工
 * 
 * @return int 
 */
int user_delete(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd)
{
    int ret = sql_exec(db, sqlcmd);
    memset(msg.data, 0, sizeof(msg.data));

    if(0 == ret)
    {
        strcat(msg.data, "delete_success");
        printf(FONT_COLOR_YELLOW"<%s>\n"COLOR_NONE, msg.data);
    }
    else
    {
        strcat(msg.data, "delete_fail");
        printf(FONT_COLOR_RED"<%s>\n"COLOR_NONE, msg.data);
    }

    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    return 0;
}
