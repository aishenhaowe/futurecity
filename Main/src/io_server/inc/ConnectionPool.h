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


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include <iostream>
#include <deque>
#include <set>

using namespace std;

/*----------------------------------------------*
 * ������                                       *
 *----------------------------------------------*/
template<class DataType>

class ConnectionPool
{
public:
    ConnectionPool(int maxSize)
    {
        this->m_maxSize         = maxSize;
        this->m_aliveCount      = 0;
        this->m_deadCount       = 0;
    }
    
    virtual ~ConnectionPool()
    {

    }

    DataType* Alloc()                                                           /* ����ڵ�                     */
    {
        DataType *obj = NULL;
        if (this->m_deadCount > 0)
        {
            obj = this->m_deadObjs.front();
            this->m_deadObjs.pop_front();
            this->m_deadCount--;
        }
        else
        {
            /* �ж��Ƿ��� */
            if (this->m_maxSize >= 0 && this->GetCount() >= this->m_maxSize)
            {
                return NULL;
            }

            obj = new DataType();
        }

        this->m_aliveObjs.insert(obj);
        this->m_aliveCount++;

        return obj;
    }
    
    void Recycle(DataType *obj)                                                 /* ����ָ���Ľڵ�               */
    {
        obj->release();
        this->m_aliveObjs.erase(obj);
        this->m_aliveCount--;
        this->m_deadObjs.push_back(obj);
        this->m_deadCount++;
    }
    int GetCount()                                                              /* ��ȡ���нڵ���ܸ���         */
    {
        return this->m_aliveCount + this->m_deadCount;
    }
    int GetAliveCount()                                                         /* ��ȡ��ڵ���ܸ���         */
    {
        return this->m_aliveCount;
    }
    int GetDeadCount()                                                          /* ��ȡ�ǻ�ڵ���ܸ���       */
    {
        return this->m_deadCount;
    }
    
    int GetMaxSize()                                                            /* ��ȡ���ӳسߴ�               */
    {
        return this->m_maxSize;
    }
    set<DataType*>& GetAliveObjs()                                              /* ��ȡ��ڵ����             */
    {
        return m_aliveObjs;
    }
    
private:
    int m_maxSize;
    int m_aliveCount;
    int m_deadCount;

    deque<DataType*> m_aliveObjs;
    deque<DataType*> m_deadObjs;
};


#endif /* __CONNECTIONPOOL_H__ */

