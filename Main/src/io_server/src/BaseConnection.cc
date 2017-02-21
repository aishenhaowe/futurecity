/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  �� �� ��   : BaseConnection.cc
  �� �� ��   : ����
  ��    ��   : ChenZhen
  ��������   : 2017��2��20��
  ����޸�   :
  ��������   : ��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <memory>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "BaseConnection.h"


long long BaseConnection::g_GConnId = 0;


/*****************************************************************************
 �� �� ��  : BaseConnection.BaseConnection
 ��������  : ���캯��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

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
 �� �� ��  : BaseConnection.~BaseConnection
 ��������  : ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
BaseConnection::~BaseConnection()
{

}

/*****************************************************************************
 �� �� ��  : BaseConnection.Init
 ��������  : ��ʼ��
 �������  : BaseHandleThread * handleThread  
             int epollFd                      
             int clientFd                     
             struct sockaddr_in clientAddr    
             int recvBuffInitSize             
             int recvBuffMaxSize              
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseConnection::Init(BaseHandleThread * handleThread, int epollFd, int clientFd, struct sockaddr_in clientAddr, int recvBuffInitSize, int recvBuffMaxSize)
{
    this->m_connId              = ++ g_GConnId;

    this->m_epollFd             = epollFd;
    this->m_clientFd            = clientFd;
    this->m_clientAddr          = clientAddr;
    
    this->m_recvLen             = 0;

    /* С�ڲ���Ҫ */
    if (this->m_recvBuf.size() < (uint32_t)recvBuffInitSize)
    {
        this->m_recvBuf.resize(recvBuffInitSize);
    }
    this->m_recvBufMaxSize      = recvBuffMaxSize;
    this->m_handleThread        = handleThread;

    return 0;
}

/*****************************************************************************
 �� �� ��  : BaseConnection.Release
 ��������  : �ͷ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
void BaseConnection::Release()
{
    this->m_connId              = 0;
}

/*****************************************************************************
 �� �� ��  : BaseConnection.StartPoll
 ��������  : ����POLL
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

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
 �� �� ��  : BaseConnection.GetEpollFd
 ��������  : ��ȡEPOLL-FD
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseConnection::GetEpollFd()
{
    this->m_epollFd;
}

/*****************************************************************************
 �� �� ��  : BaseConnection.GetClientFd
 ��������  : ��ȡCLIENT-FD
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseConnection::GetClientFd()
{
    this->m_clientFd;
}

/*****************************************************************************
 �� �� ��  : BaseConnection.GetClientIpNum
 ��������  : ��ȡ�ͻ���IP
 �������  : ��
 �������  : ��
 �� �� ֵ  : unsigned
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned int BaseConnection::GetClientIpNum()
{
    return htonl(this->m_clientAddr.sin_addr.s_addr);
}

/*****************************************************************************
 �� �� ��  : BaseConnection.OnEvent
 ��������  : �ص�����
 �������  : const struct epoll_event & event  
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

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
        this->Close();
    }
}

/*****************************************************************************
 �� �� ��  : BaseConnection.ReadMessage
 ��������  : ��ȡ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

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
                 * �����Ѿ��رգ�����-1��errnoΪECONNRESET������ٴε���recv������-1��errnoΪEPIPE��ͬʱ����EPIPE�ź�
                 * EAGAIN
                 * �����Ƿ�������ģʽ�����Ե�errnoΪEAGAINʱ����ʾ��ǰ�������������ݿɶ���������͵����Ǹô��¼��Ѵ���
                 */
                break;
            }
            else
            {
                /* �����жϣ�����������ENTER */
                continue;
            }
        }
        else if (ret == 0)
        {
            /* �����ʾ�Զ˵�socket�������ر� */
            socket_need_close                   = true;
            break;
        }
        else
        {
            /* ���ӳ��� */
            this->m_recvLen                    += ret;
        }
    }

    while (true)
    {
        int ret = this->getCheckerBox()->check(this->m_recvBuf.c_str(), this->m_recvLen);
        if (ret < 0)
        {
            /* ˵�������� */
            socket_need_close                   = true;
            break;
        }
        else if (ret == 0)
        {
            /* ������ */
            break;
        }
        else
        {
            /* ret�ǳ��� */
            this->onMessage(this->m_recvBuf.c_str(), ret);

            /* ˵�����ݿ����ˣ�ʣ�µ�����copy��ȥ */
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
        /* �ر� */
        this->Close();
    }

    return 0;
}

/*****************************************************************************
 �� �� ��  : BaseConnection.SendMessage
 ��������  : ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

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
                 * ˵��д���socket�Ѿ����ر�,����֮ǰ������signal(SIGPIPE, SIG_IGN),���Խ��̲����˳�
                 * EAGAIN
                 * ˵�����ͻ���������
                 */
                break;
            }
            else
            {
                /* �����жϣ�����������ENTER */
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
 �� �� ��  : BaseConnection.PushMessage
 ��������  : ������Ϣ
 �������  : const string & buf  
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
int BaseConnection::PushMessage(const string & buf)
{
    this->onPushMessage(buf);
    this->m_sendBuf.append(buf);

    /* �ȷ��� */
    this->SendMessage();

    return 0;
}

void BaseConnection::Close()
{
    if (this->IsClose())
    {
        /* ��ֹ�ظ�����close */
        return;
    }

    this->onClose();

    /* ��epoll��� */
    epoll_ctl(this->m_epollFd, EPOLL_CTL_DEL, this->m_clientFd, NULL);
    close(this->m_clientFd);

    this->m_clientFd = -1;
}

/*****************************************************************************
 �� �� ��  : BaseConnection.IsClose
 ��������  : �ж������Ƿ�ر�
 �������  : ��
 �������  : ��
 �� �� ֵ  : bool
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
bool BaseConnection::IsClose()
{
    return this->m_clientFd < 0;
}

/*****************************************************************************
 �� �� ��  : BaseConnection.GetConnId
 ��������  : ��ȡ����ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : long
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
long long BaseConnection::GetConnId()
{
    return this->m_connId;
}

/*****************************************************************************
 �� �� ��  : BaseConnection.IsValid
 ��������  : �����Ƿ���Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : bool
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��21��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
bool BaseConnection::IsValid()
{
    return this->m_connId > 0;
}

