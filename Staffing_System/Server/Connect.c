#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Connect.h"

/**
 * @brief Create a Server object
 * 
 * @param ipaddr 
 * @param port 
 * @return int 
 */
int CreateServer(char const *ipaddr, char const *port)
{
    int sockfd;
    struct sockaddr_in serveraddr;
    socklen_t addrlen = sizeof(serveraddr);

    //1.创建套接字
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        ERR_LOG("fail to socket");
    }

    //2.填充服务器网络信息结构体
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(ipaddr);
    serveraddr.sin_port = htons(atoi(port));
    //printf("[%s:%d]\n", inet_ntoa(serveraddr.sin_addr), ntohs(serveraddr.sin_port));

    //3.将套接字与服务器网络信息结构体绑定
    if(bind(sockfd, (struct sockaddr *)&serveraddr, addrlen) == -1)
    {
        ERR_LOG("fail to bind");
    }

    //4.将套接字设置为被动监听状态
    if(listen(sockfd, 5) == -1)
    {
        ERR_LOG("fail to listen");
    }

    printf(FONT_COLOR_YELLOW"[服务器创建成功]\n"COLOR_NONE);

    return sockfd;
}

/**
 * @brief 等待客户端连接
 * 
 * @param sockfd 
 * @param clientaddr 
 * @return int 
 */
int WaitConnect(int sockfd, struct sockaddr_in *clientaddr)
{
    //申明客户端的clientfd
    int clientfd;
    socklen_t len = sizeof(clientaddr);

    //5.调用accept阻塞等待客户端连接
    if((clientfd = accept(sockfd, (struct sockaddr *)clientaddr, &len)) == -1)
    {
        ERR_LOG("fail to accept");
    }

    //打印客户端信息
    printf(FONT_COLOR_YELLOW"[%s:%d]已连接\n"COLOR_NONE, inet_ntoa(clientaddr->sin_addr), ntohs(clientaddr->sin_port));

    //返回客户端clientfd
    return clientfd;
}

/**
 * @brief 发送数据
 * 
 * @param clientfd 
 * @param msg 
 */
void SendMsg(int clientfd, MSG *msg)
{
    if((send(clientfd, msg, sizeof(MSG), 0)) == -1)
    {
        ERR_LOG("fail to send");
    }
}

/**
 * @brief 接收数据，返回int类型数据判断客户端是否退出
 * 
 * @param clientfd 
 * @param msg 
 * @return int 
 */
int RecvMsg(int clientfd, MSG *msg)
{
    int bytes;
    if((bytes = recv(clientfd, msg, sizeof(MSG), 0)) == -1)
    {
        ERR_LOG("fail to recv");
    }

    return bytes;
}
