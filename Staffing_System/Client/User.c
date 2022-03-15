#include "User.h"

/**
 * @brief 员工注册
 * 
 * @param sockfd 
 * @param msg 
 */
int regist(int sockfd, MSG msg)
{
    //printf("regist:%s-%s\n", msg.user.account, msg.user.passwd);
    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    RecvMsg(sockfd, &msg);
    //printf("%s\n", msg.data);
    if(strcmp(msg.data, "regist_success") == 0)
    {
        return 0;
    }
    else if(strcmp(msg.data, "user_exist") == 0)
    {
        return 1;
    }
    //else if(strcmp(msg.data, "regist_fail") == 0)
    else
    {
        return -1;
    }
}


/**
 * @brief 员工登录
 * 
 * @param sockfd 
 * @param msg 
 * @return int 
 */
int login(int sockfd, MSG msg)
{
    //printf("login:%s-%s\n", msg.user.account, msg.user.passwd);
    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    RecvMsg(sockfd, &msg);
    //printf("%s\n", msg.data);
    if(strcmp(msg.data, "staff_login_success") == 0)
    {
        return 1;
    }
    else if(strcmp(msg.data, "manager_login_success") == 0)
    {
        return 2;
    }
    else if(strcmp(msg.data, "info_error") == 0)
    {
        return 0;
    }
    //else if(strcmp(msg.data, "manager_login_fail") == 0)
    else
    {
        return -1;
    }
}

/**
 * @brief 新用户判断
 * 
 * @param sockfd 
 * @param msg 
 * @return int 
 */
int new_user_judge(int sockfd, MSG msg)
{
    msg.optcode = 10;

    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    RecvMsg(sockfd, &msg);

    if(strcmp(msg.data, "true") == 0)
    {
        memset(msg.data, 0, sizeof(msg.data));
        return 0;
    }    
    else
    {
        memset(msg.data, 0, sizeof(msg.data));
        return -1;
    }
}

/**
 * @brief 首页界面
 * 
 */
void home_page(void)
{
    system("clear");  
    printf("\n\n\n");  
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                 Staffing System                    \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf("\n");   
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);   
    printf(BACK_WHITE_FONT_BLUE"\t\t            Welcome！Choose your actions            \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                 L: Login                           \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                 S: Staffing Regist                 \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);   
    printf(BACK_WHITE_FONT_BLUE"\t\t                 M: Manager Regist                  \n"COLOR_NONE);   
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
    printf(BACK_WHITE_FONT_BLUE"\t\t                 E: Exit                            \n"COLOR_NONE);   
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
}

/**
 * @brief 普通员工登录成功后的界面
 * 
 * @param sockfd 
 * @param msg 
 */
void user_page(MSG msg)
{
    system("clear");  
    printf("\n\n\n");  
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                 Staffing System                    \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t                                      [%s] \n"COLOR_NONE, msg.user.account);  
    printf("\n");   
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);   
    printf(BACK_WHITE_FONT_BLUE"\t\t            Welcome to manager center!              \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t               [1]: 查看个人信息                    \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t               [2]: 修改个人信息                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t               [3]: 打卡                            \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t               [4]: 查看历史打卡                    \n"COLOR_NONE);   
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
    printf(BACK_WHITE_FONT_BLUE"\t\t               [0]: 退出登录                        \n"COLOR_NONE);     
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
}

/**
 * @brief 员工修改个人信息界面
 * 
 * @param sockfd 
 * @param msg 
 */
void user_modify_page(MSG msg)
{
    system("clear");  
    printf("\n\n\n");  
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                 Staffing System                    \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t                                      [%s] \n"COLOR_NONE, msg.user.account);  
    printf("\n");   
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);   
    printf(BACK_WHITE_FONT_BLUE"\t\t                 <修改个人信息>                     \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t             [1]: 密码    [2]: 姓名                 \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t             [3]: 性别    [4]: 电话                 \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t             [5]: 地址                              \n"COLOR_NONE);      
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
    printf(BACK_WHITE_FONT_BLUE"\t\t                   [0]: 返回                        \n"COLOR_NONE);     
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
}

/**
 * @brief 管理员登录成功后的界面
 * 
 * @param sockfd 
 * @param msg 
 */
void manage_page(MSG msg)
{
    system("clear");  
    printf("\n\n\n");  
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                 Staffing System                    \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t                                      [%s] \n"COLOR_NONE, msg.user.account);  
    printf("\n");   
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);   
    printf(BACK_WHITE_FONT_BLUE"\t\t            Welcome to manager center!              \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t               [1]: 查找员工                        \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t               [2]: 修改员工信息                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t               [3]: 删除员工信息                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t               [4]: 显示所有员工                    \n"COLOR_NONE);      
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
    printf(BACK_WHITE_FONT_BLUE"\t\t               [0]: 退出登录                        \n"COLOR_NONE);     
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
}

/**
 * @brief 管理员修改员工信息界面
 * 
 * @param sockfd 
 * @param msg 
 */
void manage_modify_page(MSG msg)
{
    system("clear");  
    printf("\n\n\n");  
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                Staffing System                     \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t                                      [%s] \n"COLOR_NONE, msg.user.account);  
    printf("\n");   
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);   
    printf(BACK_WHITE_FONT_BLUE"\t\t                 <修改员工信息>                     \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t             [1]: 密码    [2]: 姓名                \n"COLOR_NONE);    
    printf(BACK_WHITE_FONT_BLUE"\t\t             [3]: 性别    [4]: 电话                 \n"COLOR_NONE);  
    printf(BACK_WHITE_FONT_BLUE"\t\t             [5]: 职务    [6]: 薪资                 \n"COLOR_NONE); 
    printf(BACK_WHITE_FONT_BLUE"\t\t             [7]: 地址                              \n"COLOR_NONE);     
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
    printf(BACK_WHITE_FONT_BLUE"\t\t                   [0]: 返回                        \n"COLOR_NONE);     
    printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
}

/**
 * @brief 员工修改操作
 * 
 * @param sockfd 
 * @param msg 
 */
void user_modify_center(int sockfd, MSG msg)
{
    int Opt, ret;

    user_modify_page(msg);
USER_MODIFY_NEXT:
    memset(msg.text, 0, sizeof(msg.text));
    memset(msg.data, 0, sizeof(msg.data));
    printf(FONT_COLOR_BLUE"input:>"COLOR_NONE);
    scanf("%d", &Opt);
    getchar();
    if(0 == Opt)
    {
        return ;
    }
    else if(1 == Opt)
    {
        strcat(msg.choose, "passwd");
        printf(FONT_COLOR_BLUE"输入新密码:>"COLOR_NONE);
    }
    else if(2 == Opt)
    {
        strcat(msg.choose, "name");
        printf(FONT_COLOR_BLUE"输入姓名:>"COLOR_NONE);
    }
    else if(3 == Opt)
    {
        strcat(msg.choose, "sex");
        printf(FONT_COLOR_BLUE"输入性别:>"COLOR_NONE);
    }
    else if(4 == Opt)
    {
        strcat(msg.choose, "phone");
        printf(FONT_COLOR_BLUE"输入新电话:>"COLOR_NONE);
    }
    else if(5 == Opt)
    {
        strcat(msg.choose, "address");
        printf(FONT_COLOR_BLUE"输入新地址:>"COLOR_NONE);
    }
    else
    {
        printf(FONT_COLOR_RED"请输入正确的序号\n"COLOR_NONE);
        goto USER_MODIFY_NEXT;
    }

    scanf("%s", msg.data);
    getchar();
    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    RecvMsg(sockfd, &msg);
    //printf("%s\n", msg.data);
    if(strcmp(msg.data, "modify_success") == 0)
    {
        //printf(FONT_COLOR_YELLOW"[修改成功]\n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                     < OK >                         \n"COLOR_NONE);     
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
    }
    else
    {
        //printf(FONT_COLOR_RED"[修改失败]\n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                     < Fail >                       \n"COLOR_NONE);     
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
    }

    memset(msg.data, 0, sizeof(msg.data));
    //goto USER_MODIFY_NEXT;
    sleep(1);
}

/**
 * @brief 管理员修改操作
 * 
 * @param sockfd 
 * @param msg 
 */
void manage_modify_center(int sockfd, MSG msg)
{
    int Opt, ret;

    manage_modify_page(msg);
USER_MODIFY_NEXT:
    memset(msg.text, 0, sizeof(msg.text));
    memset(msg.data, 0, sizeof(msg.data));

    printf(FONT_COLOR_BLUE"输入要修改的选项序号:>"COLOR_NONE);
    scanf("%d", &Opt);
    getchar();

    printf(FONT_COLOR_BLUE"输入要修改的员工账号:>"COLOR_NONE);
    scanf("%s", msg.text);
    getchar();

    if(0 == Opt)
    {
        return ;
    }
    else if(1 == Opt)
    {
        strcat(msg.choose, "passwd");
        printf(FONT_COLOR_BLUE"输入新密码:>"COLOR_NONE);
    }
    else if(2 == Opt)
    {
        strcat(msg.choose, "name");
        printf(FONT_COLOR_BLUE"输入姓名:>"COLOR_NONE);
    }
    else if(3 == Opt)
    {
        strcat(msg.choose, "sex");
        printf(FONT_COLOR_BLUE"输入性别:>"COLOR_NONE);
    }
    else if(4 == Opt)
    {
        strcat(msg.choose, "phone");
        printf(FONT_COLOR_BLUE"输入新电话:>"COLOR_NONE);
    }
    else if(5 == Opt)
    {
        strcat(msg.choose, "phone");
        printf(FONT_COLOR_BLUE"输入新职务:>"COLOR_NONE);
    }
    else if(6 == Opt)
    {
        strcat(msg.choose, "phone");
        printf(FONT_COLOR_BLUE"输入新薪资:>"COLOR_NONE);
    }
    else if(7 == Opt)
    {
        strcat(msg.choose, "address");
        printf(FONT_COLOR_BLUE"输入新地址:>"COLOR_NONE);
    }
    else
    {
        printf(FONT_COLOR_RED"请输入正确的序号\n"COLOR_NONE);
        goto USER_MODIFY_NEXT;
    }

    scanf("%s", msg.data);
    getchar();
    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    RecvMsg(sockfd, &msg);
    //printf("%s\n", msg.data);
    if(strcmp(msg.data, "modify_success") == 0)
    {
        //printf(FONT_COLOR_YELLOW"[修改成功]\n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                     < OK >                         \n"COLOR_NONE);     
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
    }
    else
    {
        //printf(FONT_COLOR_YELLOW"[修改失败]\n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                     < Fail >                       \n"COLOR_NONE);     
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
    }

    memset(msg.data, 0, sizeof(msg.data));
    //goto USER_MODIFY_NEXT;
    sleep(1);
}

/**
 * @brief 员工操作
 * 
 * @param sockfd 
 * @param msg 
 */
void user_center(int sockfd, MSG msg)
{
    int Opt, ret;
    char name[20] = {0};
USER_PAGE:
    user_page(msg);
USER_NEXT:
    memset(msg.data, 0, sizeof(msg.data));
    printf(FONT_COLOR_BLUE"input:>"COLOR_NONE);
    scanf("%d", &Opt);
    getchar();
    switch(Opt)
    {
        case 0:
            return ;
            break;
        case 1:
            msg.optcode = 3;
            info_show(sockfd, msg);
            break;
        case 2:
            msg.optcode = 4;
            user_modify_center(sockfd, msg);
            goto USER_PAGE;
            break;
        case 3:
            msg.optcode = 5;
            staff_clock(sockfd, msg);
            break;
        case 4:
            msg.optcode = 6;
            info_show(sockfd, msg);
            break;
        default:
            printf(FONT_COLOR_RED"请输入正确的序号\n"COLOR_NONE);
            break;
    }

    goto USER_NEXT;
}

/**
 * @brief 管理员操作
 * 
 * @param sockfd 
 * @param msg 
 */
void manage_center(int sockfd, MSG msg)
{
    int Opt, ret;
MANAGER_PAGE:
    manage_page(msg);
MANAGER_NEXT:
    memset(msg.data, 0, sizeof(msg.data));
    printf(FONT_COLOR_BLUE"input:>"COLOR_NONE);
    scanf("%d", &Opt);
    getchar(); //必须吃掉回车，否则留在缓冲区影响后续的输入
    switch(Opt)
    {
        case 0:
            return ;
            break;
        case 1:
            msg.optcode = 7;
            printf(FONT_COLOR_BLUE"员工账号:>"COLOR_NONE);
            scanf("%s", msg.data);
            getchar();
            info_show(sockfd, msg);
            msg.optcode = 6;
            memset(msg.user.account, 0, sizeof(msg.user.account));
            strcat(msg.user.account, msg.data);
            info_show(sockfd, msg);

            break;
        case 2:
            msg.optcode = 8;
            manage_modify_center(sockfd, msg);
            goto MANAGER_PAGE;
            break;
        case 3:
            msg.optcode = 9;
            printf(FONT_COLOR_BLUE"员工账号:>"COLOR_NONE);
            scanf("%s", msg.data);
            getchar();
            delete_staff(sockfd, msg);
            break;
        case 4:
            msg.optcode = 12;
            info_show(sockfd, msg);
            break;
        default:
            printf(FONT_COLOR_RED"请输入正确的序号\n"COLOR_NONE);
            break;
    }
    goto MANAGER_NEXT;
}

void info_show(int sockfd, MSG msg)
{
    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    if((3 == msg.optcode) || (7 == msg.optcode) || (12 == msg.optcode))
    {
        //printf(BACK_WHITE_FONT_BLUE"\t\t      18598859557 - chenym666 - 陈运明 - 男 - 普通员工 - 12000 - 18598859557 - 海淀区xxx    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                                                             \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t         账号         密码       姓名   性别   职务      薪资      电话         住址         \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t=============================================================================================\n"COLOR_NONE);
    }
    else if(6 == msg.optcode)
    {
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t          账号       姓名         打卡时间          \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t====================================================\n"COLOR_NONE);
    }
    while(1)
    {
        RecvMsg(sockfd, &msg);
        if(msg.data[0] == '\0')break;
        printf(BACK_WHITE_FONT_BLUE"\t\t      %s     \n"COLOR_NONE, msg.data);
    }
    printf("\n");
    return ;
}

void staff_modify(int sockfd, MSG msg)
{
    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    RecvMsg(sockfd, &msg);
    //printf("%s\n", msg.data);
    if(strcmp(msg.data, "modify_success") ==0)
    {
        //printf(FONT_COLOR_YELLOW"[修改成功]\n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                     < OK >                         \n"COLOR_NONE);     
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf("\n");
    }
    else
    {
        //printf(FONT_COLOR_RED"[修改失败]\n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                     < Fail >                       \n"COLOR_NONE);     
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf("\n");
    }
}

void staff_clock(int sockfd, MSG msg)
{
    //printf("%s\n", msg.user.name);
    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    RecvMsg(sockfd, &msg);
    
    if(strcmp(msg.data, "clock_success") == 0)
    {
        //printf(FONT_COLOR_YELLOW"[打卡成功]\n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                     < OK >                         \n"COLOR_NONE);     
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf("\n");
    }
    else
    {
        //printf(FONT_COLOR_RED"[打卡失败]\n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                     < Fail >                       \n"COLOR_NONE);     
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf("\n");
    }
}

void delete_staff(int sockfd, MSG msg)
{
    SendMsg(sockfd, &msg);
    memset(msg.data, 0, sizeof(msg.data));
    RecvMsg(sockfd, &msg);
    if(strcmp(msg.data, "delete_success") == 0)
    {
        //printf(FONT_COLOR_YELLOW"[删除成功]\n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                     < OK >                         \n"COLOR_NONE);     
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf("\n");
    }
    else
    {
        //printf(FONT_COLOR_RED"[删除失败]\n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf(BACK_WHITE_FONT_BLUE"\t\t                     < Fail >                       \n"COLOR_NONE);     
        printf(BACK_WHITE_FONT_BLUE"\t\t                                                    \n"COLOR_NONE);
        printf("\n");
    }
}
