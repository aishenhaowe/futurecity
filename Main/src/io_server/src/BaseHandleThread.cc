/******************************************************************************

                  版权所有 (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  文 件 名   : BaseHandleThread.cc
  版 本 号   : 初稿
  作    者   : ChenZhen
  生成日期   : 2017年2月19日
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "BaseHandleThread.h"
#include "ILog.h"


/*****************************************************************************
 函 数 名  : BaseHandleThread.BaseHandleThread
 功能描述  : 构造函数
 输入参数  : Server * server  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

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
 函 数 名  : BaseHandleThread.~BaseHandleThread
 功能描述  : 析构函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
BaseHandleThread::~BaseHandleThread()
{
    // TODO:需要在此处清理队列
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.GetServer
 功能描述  : 获取关联的Server实例
 输入参数  : 无
 输出参数  : 无
 返 回 值  : Server*
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
Server* BaseHandleThread::GetServer()
{
    return this->m_server;
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.GetEpollFd
 功能描述  : 获取EPOLL FD
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int BaseHandleThread::GetEpollFd()
{
    return this->m_epollFd;
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.GetHost
 功能描述  : 获取HOST IP地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : const
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
const string& BaseHandleThread::GetHost()
{
    return this->m_host;
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.GetPort
 功能描述  : 获取端口号
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int BaseHandleThread::GetPort()
{
    return this->m_port;
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.GetNowTime
 功能描述  : 获取当前时间
 输入参数  : 无
 输出参数  : 无
 返 回 值  : struct
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
struct timeval & BaseHandleThread::GetNowTime()
{
    return this->m_nowTime;
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.Init
 功能描述  : 初始化BaseHandleThread实例
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int BaseHandleThread::Init()
{
    /* 创建并启动监听 */
    int listener = this->createListener(m_host, m_port, m_backLog);
    if (listener < 0)
    {
        ERROR_LOG("createListener fail with listener_fd=%d\n", listener);
        return -1;
    }
    m_listener = listener;

    /* 创建通知FD */
    int notifyFd = this->createNotifyFd();
    if (notifyFd < 0)
    {
        return -2;
    }
    this->m_notifyFd = notifyFd;

    /* 创建EPOLL FD */
    this->m_epollFd = this->createEpoll();

    return 0;
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.Start
 功能描述  : 启动BaseHandleThread实例
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

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
 函 数 名  : BaseHandleThread.PushCacheMsg
 功能描述  : 缓存起来，马上送走
 输入参数  : IOBox *box  
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
void BaseHandleThread::PushCacheMsg(IOBox *box)
{
    this->m_cacheMsgs.push_back(box);
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.ExtendPendingMsgs
 功能描述  : 扩展的挂起消息
 输入参数  : const deque<IOBox*> &msgQueue  
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
void BaseHandleThread::ExtendPendingMsgs(const deque<IOBox*> &msgQueue)
{
    pthread_mutex_lock(&this->m_mutexPendingMsgs);

    /* 无论msgQueue是否empty都要调用，为的是其中的Notify */
    if (!msgQueue.empty())
    {
        this->m_pendingMsgs.insert(m_pendingMsgs.end(), msgQueue.begin(), msgQueue.end());
        this->onPendingMsgsSizeChanged();
    }

    /* 通知有数据到来了 */
    if (!m_pendingMsgs.empty())
    {
        this->Notify();
    }
    
    pthread_mutex_unlock(&this->m_mutexPendingMsgs);
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.Notify
 功能描述  : 通知，这样EPOLL可以直接返回
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

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
 函 数 名  : BaseHandleThread.createListener
 功能描述  : 创建Listener
 输入参数  : const string &host  
             int port            
             int backLog         
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

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
 函 数 名  : BaseHandleThread.threadWorkerProxy
 功能描述  : 工作者线程代理
 输入参数  : void *args  
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
void *BaseHandleThread::threadWorkerProxy(void *args)
{
    BaseHandleThread *thread = (BaseHandleThread *)args;

    thread->epollWorker();

    return NULL;
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.createEpoll
 功能描述  : 创建EPOLL
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int BaseHandleThread::createEpoll()
{
    return epoll_create(EPOLL_FD_MAX);
}

/*****************************************************************************
 函 数 名  : BaseHandleThread.epollWorker
 功能描述  : EPOLL工作者线程
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
void BaseHandleThread::epollWorker()
{
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET | EPOLLHUP | EPOLLERR;
    ev.data.ptr = NULL;

    if (epoll_ctl(this->m_epollFd, EPOLL_CTL_ADD, this->m_listener, &ev) < 0)
    {
        return;
    }

    /* 这个地方，不能用event=0，会导致每次都触发，似乎epoll不允许 */
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

        /* 计算nowtime，防止重复计算 */
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
 函 数 名  : BaseHandleThread.createNotifyFd
 功能描述  : 创建通知FD
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

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
 函 数 名  : BaseHandleThread.setNonBlocking
 功能描述  : 设置非阻塞掉调用
 输入参数  : int sockFd  
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

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

/*****************************************************************************
 函 数 名  : BaseHandleThread.calcNowTime
 功能描述  : 计算当前时间
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
void BaseHandleThread::calcNowTime()
{
    gettimeofday(&this->m_nowTime, NULL);
}

