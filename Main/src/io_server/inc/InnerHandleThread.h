/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  �� �� ��   : InnerHandleThread.h
  �� �� ��   : ����
  ��    ��   : ChenZhen
  ��������   : 2017��2��17��
  ����޸�   :
  ��������   : InnerHandleThread.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2017��2��17��
    ��    ��   : ChenZhen
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __INNERHANDLETHREAD_H__
#define __INNERHANDLETHREAD_H__


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "BaseHandleThread.h"
using namespace std;

class Server;

/*----------------------------------------------*
 * ������                                       *
 *----------------------------------------------*/
class InnerHandleThread : public BaseHandleThread
{
public:
    InnerHandleThread(Server *server);
    ~InnerHandleThread();
    
public:
    
protected:
    
protected:
    
private:
    
private:
    Server      *m_server;
};




#endif /* __INNERHANDLETHREAD_H__ */

