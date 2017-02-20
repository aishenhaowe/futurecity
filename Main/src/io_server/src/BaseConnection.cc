/******************************************************************************

                  版权所有 (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  文 件 名   : BaseConnection.cc
  版 本 号   : 初稿
  作    者   : ChenZhen
  生成日期   : 2017年2月20日
  最近修改   :
  功能描述   : 基础连接
  函数列表   :
  修改历史   :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include <stdlib.h>
#include <stdint.h>
#include "BaseConnection.h"


long long BaseConnection::g_GConnId = 0;


/*****************************************************************************
 函 数 名  : BaseConnection.BaseConnection
 功能描述  : 构造函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
BaseConnection::BaseConnection()
{
    this->m_epollFd             = -1;
    this->m_clientFd            = -1;
    this->m_recvLen             = 0;
    this->m_recvBufMaxSize      = -1;
    this->m_handleThread        = NULL;
}

/*****************************************************************************
 函 数 名  : BaseConnection.~BaseConnection
 功能描述  : 析构函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
BaseConnection::~BaseConnection()
{

}

/*****************************************************************************
 函 数 名  : BaseConnection.Init
 功能描述  : 初始化
 输入参数  : BaseHandleThread * handleThread  
             int epollFd                      
             int clientFd                     
             struct sockaddr_in clientAddr    
             int recvBuffInitSize             
             int recvBuffMaxSize              
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int BaseConnection::Init(BaseHandleThread * handleThread, int epollFd, int clientFd, struct sockaddr_in clientAddr, int recvBuffInitSize, int recvBuffMaxSize)
{
    this->m_connId              = ++ g_GConnId;

    this->m_epollFd             = epollFd;
    this->m_clientFd            = clientFd;
    this->m_clientAddr          = clientAddr;
    
    this->m_recvLen             = 0;

    /* 小于才需要 */
    if (this->m_recvBuf.size() < (uint32_t)recvBuffInitSize)
    {
        this->m_recvBuf.resize(recvBuffInitSize);
    }
    this->m_recvBufMaxSize      = recvBuffMaxSize;
    this->m_handleThread        = handleThread;

    return 0;
}

/*****************************************************************************
 函 数 名  : BaseConnection.Release
 功能描述  : 释放连接
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
void BaseConnection::Release()
{
    this->m_connId              = 0;
}

/*****************************************************************************
 函 数 名  : BaseConnection.StartPoll
 功能描述  : 启动POLL
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
void BaseConnection::StartPoll()
{
    struct epoll_event  ev;
    ev.data.ptr                 = this;
    ev.events                   = EPOLLIN | EPOLLET | EPOLLHUP | EPOLLERR;

    epoll_ctl(this->m_epollFd, EPOLL_CTL_ADD, this->m_clientFd, &ev);

    this->onCreate();
}

/*****************************************************************************
 函 数 名  : BaseConnection.GetEpollFd
 功能描述  : 获取EPOLL-FD
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int BaseConnection::GetEpollFd()
{
    this->m_epollFd;
}

/*****************************************************************************
 函 数 名  : BaseConnection.GetClientFd
 功能描述  : 获取CLIENT-FD
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int BaseConnection::GetClientFd()
{
    this->m_clientFd;
}

/*****************************************************************************
 函 数 名  : BaseConnection.GetClientIpNum
 功能描述  : 获取客户端IP
 输入参数  : 无
 输出参数  : 无
 返 回 值  : unsigned
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int BaseConnection::GetClientIpNum()
{
    return htonl(this->m_clientAddr.sin_addr.s_addr);
}

/*****************************************************************************
 函 数 名  : BaseConnection.OnEvent
 功能描述  : 回调函数
 输入参数  : const struct epoll_event & event  
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
void BaseConnection::OnEvent(const struct epoll_event & event)
{
    if (event.events & EPOLLIN)
    {
        this->ReadMessage();
    }
    else if (event.events & EPOLLOUT)
    {
        this->SendMessage();
    }

    if (event.events & (EPOLLERR | EPOLLHUP))
    {
        close();
    }
}

/*****************************************************************************
 函 数 名  : BaseConnection.ReadMessage
 功能描述  : 读取消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int BaseConnection::ReadMessage()
{
    bool            socket_need_close           = false;

    while(true)
    {
        if (this->m_recvBufMaxSize >= 0 && this->m_recvLen > this->m_recvBufMaxSize)
        {
            socket_need_close                   = true;
            break;
        }

        if ((size_t)this->m_recvLen >= this->m_recvBuf.size())
        {
            int newSize = this->m_recvLen * 2;
            if (this->m_recvBufMaxSize >= 0)
            {
                newSize = newSize > this->m_recvBufMaxSize + 1 ? this->m_recvBufMaxSize + 1 : newSize;
            }

            this->m_recvBuf.resize(newSize);
        }

        int ret = recv(this->m_clientFd, (char *)this->m_recvBuf.c_str() + this->m_recvLen, this->m_recvBuf.size() - this->m_recvLen, 0);
        if (ret < 0)
        {
            if (errno == EAGAIN || errno == EPIPE || errno == ECONNRESET)
            {
                /* EPIPE, ECONNRESET
                 * 连接已经关闭，返回-1，errno为ECONNRESET，如果再次调用recv，返回-1，errno为EPIPE，同时产生EPIPE信号
                 * EAGAIN
                 * 由于是非阻塞的模式，所以当errno为EAGAIN时，表示当前缓冲区已无数据可读，在这里就当作是该次事件已处理
                 */
                break;
            }
            else
            {
                /* 其他中断，继续；比如ENTER */
                continue;
            }
        }
        else if (ret == 0)
        {
            /* 这里表示对端的socket已正常关闭 */
            socket_need_close                   = true;
            break;
        }
        else
        {
            /* 增加长度 */
            this->m_recvLen                    += ret;
        }
    }

    while (true)
    {
        int ret = this->getCheckerBox()->check(this->m_recvBuf.c_str(), this->m_recvLen);
        if (ret < 0)
        {
            /* 说明出错了 */
            socket_need_close                   = true;
            break;
        }
        else if (ret == 0)
        {
            /* 继续收 */
            break;
        }
        else
        {
            /* ret是长度 */
            this->onMessage(this->m_recvBuf.c_str(), ret);

            /* 说明数据可以了，剩下的数据copy过去 */
            memmove((char *)this->m_recvBuf.c_str(), this->m_recvBuf.c_str() + ret, this->m_recvLen - ret);
            this->m_recvLen -= ret;

            if (this->m_recvLen <= 0)
            {
                break;
            }
        }
    }

    if (socket_need_close)
    {
        /* 关闭 */
        close();
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : BaseConnection.SendMessage
 功能描述  : 发送消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int BaseConnection::SendMessage()
{
    while (!this->m_sendBuf.empty())
    {
        int len = send(this->m_clientFd, this->m_sendBuf.c_str(), this->m_sendBuf.size(), 0);
        if (len < 0)
        {
            if (errno == EAGAIN || errno == EPIPE)
            {
                /* EPIPE
                 * 说明写入的socket已经被关闭,由于之前调用了signal(SIGPIPE, SIG_IGN),所以进程不会退出
                 * EAGAIN
                 * 说明发送缓存区满了
                 */
                break;
            }
            else
            {
                /* 其他中断，继续；比如ENTER */
                continue;
            }
        }

        memmove((char *)this->m_sendBuf.c_str(), this->m_sendBuf.c_str() + len, this->m_sendBuf.size() - len);
        this->m_sendBuf.resize(this->m_sendBuf.size() - len);
    }

    struct epoll_event ev;
    ev.data.ptr = this;

    if (this->m_sendBuf.empty())
    {
        ev.events = EPOLLIN | EPOLLET | EPOLLHUP | EPOLLERR;
    }
    else
    {
        ev.events = EPOLLOUT | EPOLLET | EPOLLHUP | EPOLLERR;
    }

    epoll_ctl(this->m_epollFd, EPOLL_CTL_MOD, this->m_clientFd, &ev);

    return 0;
}

/*****************************************************************************
 函 数 名  : BaseConnection.PushMessage
 功能描述  : 推送消息
 输入参数  : const string & buf  
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int BaseConnection::PushMessage(const string & buf)
{
    this->onPushMessage(buf);
    this->m_sendBuf.append(buf);

    /* 先发送 */
    this->SendMessage();

    return 0;
}

void BaseConnection::Close()
{
    if (this->IsClose())
    {
        /* 防止重复调用close */
        return;
    }

    this->onClose();

    /* 从epoll清空 */
    epoll_ctl(this->m_epollFd, EPOLL_CTL_DEL, this->m_clientFd, NULL);
    ::close(this->m_clientFd);

    this->m_clientFd = -1;
}

/*****************************************************************************
 函 数 名  : BaseConnection.IsClose
 功能描述  : 判断连接是否关闭
 输入参数  : 无
 输出参数  : 无
 返 回 值  : bool
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
bool BaseConnection::IsClose()
{
    return this->m_clientFd < 0;
}

/*****************************************************************************
 函 数 名  : BaseConnection.GetConnId
 功能描述  : 获取连接ID
 输入参数  : 无
 输出参数  : 无
 返 回 值  : long
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
long long BaseConnection::GetConnId()
{
    return this->m_connId;
}

/*****************************************************************************
 函 数 名  : BaseConnection.IsValid
 功能描述  : 连接是否有效
 输入参数  : 无
 输出参数  : 无
 返 回 值  : bool
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月21日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
bool BaseConnection::IsValid()
{
    return this->m_connId > 0;
}

