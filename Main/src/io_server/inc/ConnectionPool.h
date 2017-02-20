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
    ConnectionPool(int maxSize);
    virtual ~ConnectionPool();

    DataType* Alloc();                                                          /* 分配节点                     */
    void Recycle(DataType *obj);                                                /* 回收指定的节点               */
    int GetCount();                                                             /* 获取所有节点的总个数         */
    int GetAliveCount();                                                        /* 获取活动节点的总个数         */
    int GetDeadCount();                                                         /* 获取非活动节点的总个数       */
    int GetMaxSize();                                                           /* 获取连接池尺寸               */
    set<DataType*>& GetAliveObjs();                                             /* 获取活动节点队列             */
    
private:
    int m_maxSize;
    int m_aliveCount;
    int m_deadCount;

    deque<DataType*> m_aliveObjs;
    deque<DataType*> m_deadObjs;
};


#endif /* __CONNECTIONPOOL_H__ */

