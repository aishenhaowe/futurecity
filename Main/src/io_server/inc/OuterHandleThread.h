/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  �� �� ��   : OuterHandleThread.h
  �� �� ��   : ����
  ��    ��   : ChenZhen
  ��������   : 2017��2��17��
  ����޸�   :
  ��������   : OuterHandleThread.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2017��2��17��
    ��    ��   : ChenZhen
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __OUTERHANDLETHREAD_H__
#define __OUTERHANDLETHREAD_H__


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "BaseHandleThread.h"

using namespace std;

class Server;

/*----------------------------------------------*
 * ������                                       *
 *----------------------------------------------*/
class OuterHandleThread : public BaseHandleThread
{
public:
    OuterHandleThread(Server *server);
    ~OuterHandleThread();
    
public:
    
protected:
    
protected:
    
private:
    
private:
    Server      *m_server;
};


#endif /* __OUTERHANDLETHREAD_H__ */

