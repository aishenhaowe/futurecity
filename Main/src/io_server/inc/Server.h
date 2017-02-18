/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  �� �� ��   : Server.h
  �� �� ��   : ����
  ��    ��   : ChenZhen
  ��������   : 2017��2��17��
  ����޸�   :
  ��������   : Server.cc ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2017��2��17��
    ��    ��   : ChenZhen
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __SERVER_H__
#define __SERVER_H__


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "InnerHandleThread.h"
#include "OuterHandleThread.h"
#include "OuterTimerThread.h"

using namespace std;


/*----------------------------------------------*
 * ������                                       *
 *----------------------------------------------*/
class Server
{
/* Public Methods */
public:
    /* ���캯�� */
    Server();
    
    /* �������� */
    virtual ~Server();

    /* ��ȡTag */
    int GetTag();

    /* ��ʼ�� */
    int Init(string configPath);

    /* ���������� */
    int Run();

/* Public Members */
public:
    InnerHandleThread       *m_InnerHandleThread;
    OuterHandleThread       *m_OuterHandleThread;
    OuterTimerThread        *m_OuterTimerThread;

/* Protected Methods */
protected:

/* Protected Members */
protected:

/* Private Methods */
private:

/* Private Members */
private:
    int                     m_tag;
    string                  m_configPath;
};


#endif /* __SERVER_H__ */
