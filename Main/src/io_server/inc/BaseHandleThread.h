/*-------------------------------------------------------------------------
    
-------------------------------------------------------------------------*/
/******************************************************************************

                  版权所有 (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  文 件 名   : BaseHandleThread.h
  版 本 号   : 初稿
  作    者   : ChenZhen
  生成日期   : 2017年2月17日
  最近修改   :
  功能描述   : BaseHandleThread.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2017年2月17日
    作    者   : ChenZhen
    修改内容   : 创建文件

******************************************************************************/
#ifndef __BASEHANDLETHREAD_H__
#define __BASEHANDLETHREAD_H__


/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>

#include <memory>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <deque>

#include "IOBox.h"
#include "IOServerDefines.h"


using namespace std;

class Server;

/*----------------------------------------------*
 * 类声明                                       *
 *----------------------------------------------*/
class BaseHandleThread
{
public:
    BaseHandleThread(Server * server, const string &host, int port, int backLog);
    ~BaseHandleThread();

    Server *GetServer();                                                        /* 获取关联的Server实例         */
    int GetEpollFd();                                                           /* 获取EPOLL FD                 */
    const string &GetHost();                                                    /* 获取HOST IP地址              */
    int GetPort();                                                              /* 获取端口号                   */
    struct timeval &GetNowTime();                                               /* 获取当前时间                 */

    int Init();                                                                 /* 初始化                       */
    int Start();                                                                /* 启动                         */
    void PushCacheMsg(IOBox *box);                                              /* 缓存起来，马上送走           */
    void ExtendPendingMsgs(const deque<IOBox*> &msgQueue);                      /* 扩展的挂起消息               */

    void Notify();                                                              /* 通知，这样EPOLL可以直接返回  */
    
public:
    
protected:
    virtual void onOneEpollLoopOver() = 0;                                      /* 一个循环之后的处理           */
    virtual void onEpollEvent(const epoll_event &event) = 0;
    virtual void onPendingMsgsSizeChanged() {}

    int createListener(const string &host, int port, int backLog);              /* 创建Listener                 */
    static void *threadWorkerProxy(void *args);                                 /* 工作者线程代理               */
    int createEpoll();                                                          /* 创建EPOLL                    */
    void epollWorker();                                                         /* EPOLL工作者线程              */
    int createNotifyFd();                                                       /* 创建通知FD                   */

    int setNonBlocking(int sockFd);                                             /* 设置非阻塞掉调用             */
    int reuseAddr(int sockFd);

    void calcNowTime();
    
protected:
    deque<IOBox*>   m_cacheMsgs;                                                /* 加锁                         */
    pthread_mutex_t m_mutexPendingMsgs;
    deque<IOBox*>   m_pendingMsgs;                                              /* 保存别的线程发送过来的消息   */
    
    Server         *m_server;
    string          m_host;
    int             m_port;
    int             m_backLog;
    int             m_epollFd;
    int             m_listener;
    int             m_notifyFd;
    struct timeval  m_nowTime;

private:
    
private:
};




#endif /* __BASEHANDLETHREAD_H__ */

