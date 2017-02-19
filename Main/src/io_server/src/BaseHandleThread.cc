/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  �� �� ��   : BaseHandleThread.cc
  �� �� ��   : ����
  ��    ��   : ChenZhen
  ��������   : 2017��2��19��
  ����޸�   :
  ��������   : 
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "BaseHandleThread.h"


/*****************************************************************************
 �� �� ��  : BaseHandleThread.BaseHandleThread
 ��������  : ���캯��
 �������  : Server * server  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
BaseHandleThread::BaseHandleThread(Server * server, const string &host, int port, int backLog)
{
    m_server        = server;
    m_host          = host;
    m_port          = port;
    m_backLog       = backLog;

    m_epollFd       = -1;
    m_listener      = -1;
    m_notifyFd      = -1;

    pthread_mutex_init(&this->m_mutexPendingMsgs, NULL);
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.~BaseHandleThread
 ��������  : ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
BaseHandleThread::~BaseHandleThread()
{
    // TODO:��Ҫ�ڴ˴��������
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.GetServer
 ��������  : ��ȡ������Serverʵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : Server*
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
Server* BaseHandleThread::GetServer()
{
    return this->m_server;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.GetEpollFd
 ��������  : ��ȡEPOLL FD
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseHandleThread::GetEpollFd()
{
    return this->m_epollFd;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.GetHost
 ��������  : ��ȡHOST IP��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : const
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
const string& BaseHandleThread::GetHost()
{
    return this->m_host;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.GetPort
 ��������  : ��ȡ�˿ں�
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseHandleThread::GetPort()
{
    return this->m_port;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.GetNowTime
 ��������  : ��ȡ��ǰʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : struct
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
struct timeval & BaseHandleThread::GetNowTime()
{
    return this->m_nowTime;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.Init
 ��������  : ��ʼ��BaseHandleThreadʵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseHandleThread::Init()
{
    /* �������������� */
    int listener = this->createListener(m_host, m_port, m_backLog);
    if (listener < 0)
    {
        return -1;
    }
    m_listener = listener;

    /* ����֪ͨFD */
    int notifyFd = this->createNotifyFd();
    if (notifyFd < 0)
    {
        return -2;
    }

    /* ����EPOLL FD */
    this->m_epollFd = this->createEpoll();

    return 0;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.Start
 ��������  : ����BaseHandleThreadʵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseHandleThread::Start()
{
    pthread_attr_t          attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    int ret = 0;
    pthread_t thread;

    ret = pthread_create(&thread, &attr, &BaseHandleThread::threadWorkerProxy, (void *)this);
    if (ret != 0)
    {
        return ret;
    }

    pthread_attr_destroy(&attr);
    
    return ret;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.PushCacheMsg
 ��������  : ������������������
 �������  : IOBox *box  
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
void BaseHandleThread::PushCacheMsg(IOBox *box)
{
    this->m_cacheMsgs.push_back(box);
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.ExtendPendingMsgs
 ��������  : ��չ�Ĺ�����Ϣ
 �������  : const deque<IOBox*> &msgQueue  
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
void BaseHandleThread::ExtendPendingMsgs(const deque<IOBox*> &msgQueue)
{
    pthread_mutex_lock(&this->m_mutexPendingMsgs);

    /* ����msgQueue�Ƿ�empty��Ҫ���ã�Ϊ�������е�Notify */
    if (!msgQueue.empty())
    {
        this->m_pendingMsgs.insert(m_pendingMsgs.end(), msgQueue.begin(), msgQueue.end());
        this->onPendingMsgsSizeChanged();
    }

    /* ֪ͨ�����ݵ����� */
    if (!m_pendingMsgs.empty())
    {
        this->Notify();
    }
    
    pthread_mutex_unlock(&this->m_mutexPendingMsgs);
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.Notify
 ��������  : ֪ͨ������EPOLL����ֱ�ӷ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
void BaseHandleThread::Notify()
{
    struct epoll_event ev;
    ev.events = EPOLLONESHOT;
    ev.data.ptr = NULL;

    if (epoll_ctl(this->m_epollFd, EPOLL_CTL_MOD, this->m_notifyFd, &ev) < 0)
    {
        return;
    }
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.createListener
 ��������  : ����Listener
 �������  : const string &host  
             int port            
             int backLog         
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseHandleThread::createListener(const string &host, int port, int backLog)
{
    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        
        return -1;
    }

    setNonBlocking(listener);
    reuseAddr(listener);

    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons((unsigned short)port);
    myaddr.sin_addr.s_addr = inet_addr(host.c_str());

    if (bind(listener, (struct sockaddr*)&myaddr, sizeof(struct sockaddr)) < 0)
    {
        close(listener);
        
        return -2;
    }

    if (listen(listener, backLog) < 0)
    {
        close(listener);
        return -3;
    }
    
    return listener;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.threadWorkerProxy
 ��������  : �������̴߳���
 �������  : void *args  
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
void *BaseHandleThread::threadWorkerProxy(void *args)
{
    BaseHandleThread *thread = (BaseHandleThread *)args;

    thread->epollWorker();

    return NULL;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.createEpoll
 ��������  : ����EPOLL
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseHandleThread::createEpoll()
{
    return epoll_create(EPOLL_FD_MAX);
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.epollWorker
 ��������  : EPOLL�������߳�
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
void BaseHandleThread::epollWorker()
{
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET | EPOLLUP | EPOLLERR;
    ev.data.ptr = NULL;

    if (epoll_ctl(this->m_epollFd, EPOLL_CTL_ADD, this->m_listener, &ev) < 0)
    {
        return;
    }

    /* ����ط���������event=0���ᵼ��ÿ�ζ��������ƺ�epoll������ */
    ev.events = EPOLLONESHOT;
    ev.data.ptr = NULL;

    if (epoll_ctl(this->m_epollFd, EPOLL_CTL_ADD, this->m_notifyFd, &ev) < 0)
    {
        return;
    }

    int eventsMaxSize = EPOLL_EVENTS_MAXSIZE;
    struct epoll_event *events = new struct epoll_event[eventsMaxSize];

    while (1)
    {
        int eventCount = epoll_wait(this->m_epollFd, events, eventsMaxSize, EPOLL_WAIT_TIME);
        if (-1 == eventCount)
        {
            continue;
        }

        /* ����nowtime����ֹ�ظ����� */
        calcNowTime();

        for (int i = 0; i < eventCount; ++i)
        {
            struct epoll_event &event = events[i];

            onEpollEvent(event);
        }

        this->onOneEpollLoopOver();
    }

    delete[] events;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.createNotifyFd
 ��������  : ����֪ͨFD
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseHandleThread::createNotifyFd()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        return -1;
    }
    
    return fd;
}

/*****************************************************************************
 �� �� ��  : BaseHandleThread.setNonBlocking
 ��������  : ���÷�����������
 �������  : int sockFd  
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��19��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseHandleThread::setNonBlocking(int sockFd)
{
    //if (fcntl(sockFd, F_SETFL, fcntl(sockFd, F_GETFD, 0) | O_NOBLOCK) == -1)
    {
        return -1;
    }

    return 0;
}

int BaseHandleThread::reuseAddr(int sockFd)
{
    const int on = 1;

    return setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
}

