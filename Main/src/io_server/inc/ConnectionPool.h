/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  �� �� ��   : ConnectionPool.h
  �� �� ��   : ����
  ��    ��   : ChenZhen
  ��������   : 2017��2��20��
  ����޸�   :
  ��������   : ConnectionPool.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __CONNECTIONPOOL_H__
#define __CONNECTIONPOOL_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
using namespace std;

/*----------------------------------------------*
 * ������                                       *
 *----------------------------------------------*/
template<class DataType>

class ConnectionPool
{
public:
    ConnectionPool(int maxSize);
    virtual ~ConnectionPool();

    DataType* Alloc();                                                          /* ����ڵ�                     */
    void Recycle(DataType *obj);                                                /* ����ָ���Ľڵ�               */
    int GetCount();                                                             /* ��ȡ���нڵ���ܸ���         */
    int GetAliveCount();                                                        /* ��ȡ��ڵ���ܸ���         */
    int GetDeadCount();                                                         /* ��ȡ�ǻ�ڵ���ܸ���       */
    int GetMaxSize();                                                           /* ��ȡ���ӳسߴ�               */
    set<DataType*>& GetAliveObjs();                                             /* ��ȡ��ڵ����             */
    
private:
    int m_maxSize;
    int m_aliveCount;
    int m_deadCount;

    deque<DataType*> m_aliveObjs;
    deque<DataType*> m_deadObjs;
};


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CONNECTIONPOOL_H__ */

