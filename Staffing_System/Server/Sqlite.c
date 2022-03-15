#include "Sqlite.h"

/**
 * @brief 获取当前时间
 * 
 * @param data 
 */
void getdate(char date[])
{
    time_t t;
    struct tm *tp;
    time(&t);
    tp = localtime(&t);
    sprintf(date, "%d-%d-%d %d:%d:%d",
        1900+tp->tm_year, 1+tp->tm_mon, tp->tm_mday,
        tp->tm_hour, tp->tm_min, tp->tm_sec);
}

/**
 * @brief 创建/打开数据库
 * 
 * @param dbname 
 * @param db 
 * @return sqlite3* 
 */
sqlite3 *sql_open(const char *dbname, sqlite3 *db)
{
    if(sqlite3_open(dbname, &db) != SQLITE_OK)
    {
        printf(FONT_COLOR_RED"[数据库创建/打开错误]%s\n"COLOR_NONE, sqlite3_errmsg(db));
    }
    else
    {
        printf(FONT_COLOR_YELLOW"[数据库创建/打开成功]\n"COLOR_NONE);
        return db;
    }
}

/**
 * @brief 执行数据库操作(创建表，插入、删除、更新记录)
 * 
 * @param db 
 * @param sqlcmd 
 * @return int 
 */
int sql_exec(sqlite3 *db, const char *sqlcmd)
{
    char *errmsg;
    if(sqlite3_exec(db, sqlcmd, NULL, NULL, &errmsg) != SQLITE_OK)
    {
        if(errno == 2)
        {
            return 1;   /*存在记录*/
        }
        return -1;
    }

    return 0;
}

/**
 * @brief 判断记录是否存在
 * 
 * @param db 
 * @param msg 
 * @param sqlcmd 
 * @return int 
 */
int sql_judge(sqlite3 *db, MSG msg, const char *sqlcmd)
{
    char *errmsg, **result;
    int nrow, ncolum;

    if(sqlite3_get_table(db, sqlcmd, &result, &nrow, &ncolum, &errmsg) != SQLITE_OK)
    {
        return -1;
    }
    if(nrow == 0)
    {
        //printf(FONT_COLOR_RED"[未查到记录]\n"COLOR_NONE);
        return 1;
    }
    else
    {
        //printf(FONT_COLOR_YELLOW"[查询表成功]\n"COLOR_NONE);
        return 0;
    }
}


/**
 * @brief Get the data callback object
 * 
 * @param arg 
 * @param f_num 
 * @param f_value 
 * @param f_name 
 * @return int 
 */
int gethistory_callback(void *arg, int f_num, char **f_value, char **f_name)
{
    int sockfd = *(int *)arg;
    MSG msg;

    sprintf(msg.data, "%s   -   %s   -   %s", f_value[0], f_value[1], f_value[2]);
    //printf(FONT_COLOR_YELLOW"%s - %s - %s\n"COLOR_NONE, f_value[0], f_value[1], f_value[2]);

    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    return 0;
}

int getinfo_callback(void *arg, int f_num, char **f_value, char **f_name)
{
    int sockfd = *(int *)arg;
    MSG msg;

    /*staff_info(class int, account text primary key, passwd text, name text, sex text, duty text, pay int, phone text, address text, regist_date text)*/
    sprintf(msg.data, "%s - %s - %s - %s - %s - %s - %s - %s", f_value[1], f_value[2], f_value[3], f_value[4], f_value[5], f_value[6], f_value[7], f_value[8]);
    //printf(FONT_COLOR_YELLOW"%s - %s - %s - %s - %s - %s - %s - %s - %s\n"COLOR_NONE, f_value[0], f_value[1], f_value[2], f_value[3], f_value[4], f_value[5], f_value[6], f_value[7], f_value[8]);

    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));

    return 0;
}

/**
 * @brief 获取数据库内容
 * 
 * @param sockfd 
 * @param msg 
 * @param db 
 * @param sqlcmd 
 */
void sql_getdata(int sockfd, MSG msg, sqlite3 *db, const char *sqlcmd)
{
    char *errmsg; 
    /*使用函数指针替换exec中的回调函数*/
    int (*p_callback)() = NULL;

    if((3 == msg.optcode) || (7 == msg.optcode) || (12 == msg.optcode))
        p_callback = getinfo_callback;
    else if(6 == msg.optcode)
        p_callback = gethistory_callback;

    if(sqlite3_exec(db, sqlcmd, p_callback, (void *)&sockfd, &errmsg) != SQLITE_OK)
    {
        printf(msg.data, "get_fail");
    }
    msg.data[0] = '\0';

    SendMsg(sockfd, &msg);
}
