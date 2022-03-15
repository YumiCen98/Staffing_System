#ifndef __STAFF_H_
#define __STAFF_H_

//#define N 256
#define DATANAME "staff.db"

/*定义颜色代码，用户不同场景下的信息提示*/
#define COLOR_NONE              "\033[0m"       //恢复默认
#define FONT_COLOR_YELLOW       "\033[1;33m"    //黄色高亮
#define FONT_COLOR_RED          "\033[1;31m"    //红色高亮
#define FONT_COLOR_BLUE         "\033[1;34m"    //蓝色高亮

#define ERR_LOG(errmsg) do{ \
    perror(errmsg); \
    printf(FONT_COLOR_RED"[%s - %s - %d]\n"COLOR_NONE, __FILE__, __func__, __LINE__); \
    exit(1); \
}while(0)

/*操作码功能枚举*/
enum OP
{
	LOGIN,
	STAFF_REGIST,
	MANAGER_REGIST,
	STAFF_SHOW,
    STAFF_MODIFY,
    STAFF_CLOCK,
    HISTORY_SHOW,
    MANAGER_SHOW,
    MANAGER_MODIFY,
	DELETE_STAFF,
    NEW_USER_JUDGE,
    ADD_USER_INFO,
    ALL_SHOW
};

/*用户信息结构体*/
/*用户注册后职务默认为员工，只有管理员可以修改职务*/
/*用户注册后薪资默认为￥12000.00，只有管理员可以修改薪资*/
typedef struct {
    char account[12];	/*账号为11位手机号*/
    char passwd[17];	/*密码规定8-16位*/
    char name[20];
    char sex[10]; 		/*一个汉字占两个字节*/
    char phone[12]; 	/*固定11位数字*/
    char address[50];	/*地址*/
}USER;

/*传输信息结构体*/
typedef struct {
    int optcode;        /*定义操作码，用于服务器识别，使用枚举类型定义操作码含义*/
    USER user;	        /*用户基本信息*/
    char choose[10];     /*定义副功能识别指令，用于服务器识别*/
    char text[128];      /*传输服务器发送的提示信息*/
    char data[128];     /*用于存储提示信息和传输的数据库数据*/
}MSG;


#endif