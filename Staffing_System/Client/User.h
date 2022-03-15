#ifndef __USER_H_
#define __USER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Staff.h"
#include "Connect.h"

int regist(int sockfd, MSG msg);
int login(int sockfd, MSG msg);
int get_user_name(int sockfd, MSG msg);
int add_info(int sockfd, MSG msg);
int new_user_judge(int sockfd, MSG msg);
void home_page(void);
void user_page(MSG msg);
void user_modify_page(MSG msg);
void manage_page(MSG msg);
void manage_modify_page(MSG msg);
void user_modify_center(int sockfd, MSG msg);
void manage_modify_center(int sockfd, MSG msg);
void user_center(int sockfd, MSG msg);
void manage_center(int sockfd, MSG msg);

void info_show(int sockfd, MSG msg);
void staff_modify(int sockfd, MSG msg);
void staff_clock(int sockfd, MSG msg);
void manager_modify(int sockfd, MSG msg);
void delete_staff(int sockfd, MSG msg);

#endif
