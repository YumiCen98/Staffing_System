#ifndef __SQLITE_H_
#define __SQLITE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>
#include <errno.h>
#include "Staff.h"
#include "Connect.h"


void getdate(char date[]);
sqlite3 *sql_open(const char *dbname, sqlite3 *db);
int sql_exec(sqlite3 *db, const char *sqlcmd);
int sql_judge(sqlite3 *db, MSG msg, const char *sqlcmd);
int gethistory_callback(void *arg, int f_num, char **f_value, char **f_name);
int getinfo_callback(void *arg, int f_num, char **f_value, char **f_name);
int getname_callback(void *arg, int f_num, char **f_value, char **f_name);
void sql_getdata(int sockfd, MSG msg, sqlite3 *db, const char *sqlcmd);

#endif