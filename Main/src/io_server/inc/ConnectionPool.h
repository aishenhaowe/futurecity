/******************************************************************************

                  版权所有 (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  文 件 名   : ConnectionPool.h
  版 本 号   : 初稿
  作    者   : ChenZhen
  生成日期   : 2017年2月20日
  最近修改   :
  功能描述   : ConnectionPool.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CONNECTIONPOOL_H__
#define __CONNECTIONPOOL_H__


/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include <iostream>
#include <deque>
#include <set>

using namespace std;

/*----------------------------------------------*
 * 类声明                                       *
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

    DataType* Alloc()                                                           /* 分配节点                     */
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
            /* 判断是否超限 */
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
    
    void Recycle(DataType *obj)                                                 /* 回收指定的节点               */
    {
        obj->release();
        this->m_aliveObjs.erase(obj);
        this->m_aliveCount--;
        this->m_deadObjs.push_back(obj);
        this->m_deadCount++;
    }
    int GetCount()                                                              /* 获取所有节点的总个数         */
    {
        return this->m_aliveCount + this->m_deadCount;
    }
    int GetAliveCount()                                                         /* 获取活动节点的总个数         */
    {
        return this->m_aliveCount;
    }
    int GetDeadCount()                                                          /* 获取非活动节点的总个数       */
    {
        return this->m_deadCount;
    }
    
    int GetMaxSize()                                                            /* 获取连接池尺寸               */
    {
        return this->m_maxSize;
    }
    set<DataType*>& GetAliveObjs()                                              /* 获取活动节点队列             */
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

