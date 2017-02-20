/******************************************************************************

                  版权所有 (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  文 件 名   : BaseConnection.h
  版 本 号   : 初稿
  作    者   : ChenZhen
  生成日期   : 2017年2月20日
  最近修改   :
  功能描述   : BaseConnection.cc 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BASECONNECTION_H__
#define __BASECONNECTION_H__


/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include <iostream>
#include <arpa/inet.h>

using namespace std;


/*----------------------------------------------*
 * 类声明                                       *
 *----------------------------------------------*/

class BaseHandleThread;

class BaseConnection
{
public:
    BaseConnection();
    ~BaseConnection();

    int Init(BaseHandleThread *handleThread, 
             int epollFd, 
             int clientFd, 
             struct sockaddr_in clientAddr, 
             int recvBuffInitSize, 
             int recvBuffMaxSize);
    virtual void Release();                                                     /* 释放 */
    bool IsValid();                                                             /* 是否被回收 */
    long long GetConnId();                                                      /* 获取连接ID */
    void StartPoll();

    void OnEvent(const struct epoll_event& event);
    int PushMessage(const string &buf);

    int GetEpollFd();
    int GetClientFd();

    unsigned int GetClientIpNum();

    void Close();
    bool IsClose();

protected:
    int ReadMessage();
    int SendMessage();

    virtual void onMessage(const char buf, size_t size){}
    virtual void onCreate();
    virtual void onClose();
    virtual IBox* getCheckerBox() = 0;
    virtual void onPushMessage(const string& buf){}

    static long long newSn();

protected:
    int                         m_epollFd;
    int                         m_clientFd;
    struct sockaddr_in          m_clientAddr;

    string                      m_recvBuf;                                      /* 接收buf */
    int                         m_recvLen;                                      /* 已经接收的长度 */

    string                      m_sendBuf;                                      /* 待发送的数据 */

    BaseHandleThread*           m_handleThread;

    long long                   m_connId;

    static long long            g_GConnId;

    int                         m_recvBufMaxSize;
    
};


#endif /* __BASECONNECTION_H__ */
