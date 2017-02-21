/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  �� �� ��   : BaseConnection.h
  �� �� ��   : ����
  ��    ��   : ChenZhen
  ��������   : 2017��2��20��
  ����޸�   :
  ��������   : BaseConnection.cc ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __BASECONNECTION_H__
#define __BASECONNECTION_H__


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include <iostream>
#include <arpa/inet.h>
#include "IBox.h"

using namespace std;


/*----------------------------------------------*
 * ������                                       *
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
    virtual void Release();                                                     /* �ͷ� */
    bool IsValid();                                                             /* �Ƿ񱻻��� */
    long long GetConnId();                                                      /* ��ȡ����ID */
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

    virtual void onMessage(const char* buf, size_t size){}
    virtual void onCreate(){}
    virtual void onClose(){}
    virtual IBox* getCheckerBox() = 0;
    virtual void onPushMessage(const string& buf){}

    static long long newSn();

protected:
    int                         m_epollFd;
    int                         m_clientFd;
    struct sockaddr_in          m_clientAddr;

    string                      m_recvBuf;                                      /* ����buf */
    int                         m_recvLen;                                      /* �Ѿ����յĳ��� */

    string                      m_sendBuf;                                      /* �����͵����� */

    BaseHandleThread*           m_handleThread;

    long long                   m_connId;

    static long long            g_GConnId;

    int                         m_recvBufMaxSize;
    
};


#endif /* __BASECONNECTION_H__ */
