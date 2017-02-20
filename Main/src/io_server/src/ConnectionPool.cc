/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  �� �� ��   : ConnectionPool.cc
  �� �� ��   : ����
  ��    ��   : ChenZhen
  ��������   : 2017��2��20��
  ����޸�   :
  ��������   : ���ӳ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "ConnectionPool.h"


/*****************************************************************************
 �� �� ��  : ConnectionPool.ConnectionPool
 ��������  : ���캯��
 �������  : int maxSize  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
template<class DataType>
ConnectionPool<DataType>::ConnectionPool(int maxSize)
{
    this->m_maxSize         = maxSize;
    this->m_aliveCount      = 0;
    this->m_deadCount       = 0;
}

/*****************************************************************************
 �� �� ��  : ConnectionPool.~ConnectionPool
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
template<class DataType>
ConnectionPool<DataType>::~ConnectionPool()
{

}

/*****************************************************************************
 �� �� ��  : ConnectionPool.Alloc
 ��������  : ����ڵ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
template<class DataType>
void ConnectionPool<DataType>::Alloc()
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

/*****************************************************************************
 �� �� ��  : ConnectionPool.Recycle
 ��������  : ����ָ���Ľڵ�
 �������  : DataType *obj  
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
template<class DataType>
void ConnectionPool<DataType>::Recycle(DataType *obj)
{
    obj->release();
    this->m_aliveObjs.erase(obj);
    this->m_aliveCount--;
    this->m_deadObjs.push_back(obj);
    this->m_deadCount++;
}

/*****************************************************************************
 �� �� ��  : ConnectionPool.GetCount
 ��������  : ��ȡ���нڵ���ܸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
template<class DataType>
int ConnectionPool<DataType>::GetCount()
{
    return this->m_aliveCount + this->m_deadCount;
}

/*****************************************************************************
 �� �� ��  : ConnectionPool.GetAliveCount
 ��������  : ��ȡ��ڵ���ܸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
template<class DataType>
int ConnectionPool<DataType>::GetAliveCount()
{
    return this->m_aliveCount;
}

/*****************************************************************************
 �� �� ��  : ConnectionPool.GetDeadCount
 ��������  : ��ȡ�ǻ�ڵ���ܸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
template<class DataType>
int ConnectionPool<DataType>::GetDeadCount()
{
    return this->m_deadCount;
}

/*****************************************************************************
 �� �� ��  : ConnectionPool.GetMaxSize
 ��������  : ��ȡ���ӳسߴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
template<class DataType>
int ConnectionPool<DataType>::GetMaxSize()
{
    return this->m_maxSize;
}

/*****************************************************************************
 �� �� ��  : ConnectionPool.GetAliveObjs
 ��������  : ��ȡ��ڵ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : set<DataType*>&
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��2��20��
    ��    ��   : ChenZhen
    �޸�����   : �����ɺ���

*****************************************************************************/
template<class DataType>
set<DataType*>& ConnectionPool<DataType>::GetAliveObjs()
{
    return m_aliveObjs;
}

