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
using namespace std;

class Server;

/*----------------------------------------------*
 * ������                                       *
 *----------------------------------------------*/
class BaseHandleThread
{
public:
    BaseHandleThread(Server *server);
    ~BaseHandleThread();
    
public:
    
protected:
    
protected:
    
private:
    
private:
    Server      *m_server;
};




#endif /* __BASEHANDLETHREAD_H__ */

