#ifndef __OPERATION_H_
#define __OPERATION_H_

#include "Staff.h"
#include "Connect.h"
#include "Sqlite.h"

int regist(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd);
int login(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd);
int new_user_judge(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd);
int add_user_info(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd);
int user_show(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd);
int user_modify(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd);
int user_clock(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd);
void user_history_clock(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd);
int user_delete(int sockfd, MSG msg, sqlite3 *db, char *sqlcmd);


#endif