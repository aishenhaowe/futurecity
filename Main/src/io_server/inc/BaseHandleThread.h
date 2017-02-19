/*-------------------------------------------------------------------------
    
-------------------------------------------------------------------------*/
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  �� �� ��   : BaseHandleThread.h
  �� �� ��   : ����
  ��    ��   : ChenZhen
  ��������   : 2017��2��17��
  ����޸�   :
  ��������   : BaseHandleThread.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2017��2��17��
    ��    ��   : ChenZhen
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __BASEHANDLETHREAD_H__
#define __BASEHANDLETHREAD_H__


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
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
 * ������                                       *
 *----------------------------------------------*/
class BaseHandleThread
{
public:
    BaseHandleThread(Server * server, const string &host, int port, int backLog);
    ~BaseHandleThread();

    Server *GetServer();                                                        /* ��ȡ������Serverʵ��         */
    int GetEpollFd();                                                           /* ��ȡEPOLL FD                 */
    const string &GetHost();                                                    /* ��ȡHOST IP��ַ              */
    int GetPort();                                                              /* ��ȡ�˿ں�                   */
    struct timeval &GetNowTime();                                               /* ��ȡ��ǰʱ��                 */

    int Init();                                                                 /* ��ʼ��                       */
    int Start();                                                                /* ����                         */
    void PushCacheMsg(IOBox *box);                                              /* ������������������           */
    void ExtendPendingMsgs(const deque<IOBox*> &msgQueue);                      /* ��չ�Ĺ�����Ϣ               */

    void Notify();                                                              /* ֪ͨ������EPOLL����ֱ�ӷ���  */
    
public:
    
protected:
    virtual void onOneEpollLoopOver() = 0;                                      /* һ��ѭ��֮��Ĵ���           */
    virtual void onEpollEvent(const epoll_event &event) = 0;
    virtual void onPendingMsgsSizeChanged() {}

    int createListener(const string &host, int port, int backLog);              /* ����Listener                 */
    static void *threadWorkerProxy(void *args);                                 /* �������̴߳���               */
    int createEpoll();                                                          /* ����EPOLL                    */
    void epollWorker();                                                         /* EPOLL�������߳�              */
    int createNotifyFd();                                                       /* ����֪ͨFD                   */

    int setNonBlocking(int sockFd);                                             /* ���÷�����������             */
    int reuseAddr(int sockFd);

    void calcNowTime();                                                         /* ���㵱ǰʱ��                 */
    
protected:
    deque<IOBox*>   m_cacheMsgs;                                                /* ����                         */
    pthread_mutex_t m_mutexPendingMsgs;
    deque<IOBox*>   m_pendingMsgs;                                              /* �������̷߳��͹�������Ϣ   */
    
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

