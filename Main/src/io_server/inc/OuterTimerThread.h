/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  �� �� ��   : OuterTimerThread.h
  �� �� ��   : ����
  ��    ��   : ChenZhen
  ��������   : 2017��2��17��
  ����޸�   :
  ��������   : OuterTimerThread.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2017��2��17��
    ��    ��   : ChenZhen
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __OUTERTIMERTHREAD_H__
#define __OUTERTIMERTHREAD_H__


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/

class Server;

class OuterTimerThread
{
public:
    OuterTimerThread(Server *server);
    ~OuterTimerThread();
    
public:
    
protected:
    
protected:
    
private:
    
private:
    Server      *m_server;
};



#endif /* __OUTERTIMERTHREAD_H__ */

