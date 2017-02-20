/******************************************************************************

                  版权所有 (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  文 件 名   : ConnectionPool.cc
  版 本 号   : 初稿
  作    者   : ChenZhen
  生成日期   : 2017年2月20日
  最近修改   :
  功能描述   : 连接池
  函数列表   :
  修改历史   :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "ConnectionPool.h"


/*****************************************************************************
 函 数 名  : ConnectionPool.ConnectionPool
 功能描述  : 构造函数
 输入参数  : int maxSize  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
template<class DataType>
ConnectionPool<DataType>::ConnectionPool(int maxSize)
{
    this->m_maxSize         = maxSize;
    this->m_aliveCount      = 0;
    this->m_deadCount       = 0;
}

/*****************************************************************************
 函 数 名  : ConnectionPool.~ConnectionPool
 功能描述  : 析构函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
template<class DataType>
ConnectionPool<DataType>::~ConnectionPool()
{

}

/*****************************************************************************
 函 数 名  : ConnectionPool.Alloc
 功能描述  : 分配节点
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

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

/*****************************************************************************
 函 数 名  : ConnectionPool.Recycle
 功能描述  : 回收指定的节点
 输入参数  : DataType *obj  
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

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
 函 数 名  : ConnectionPool.GetCount
 功能描述  : 获取所有节点的总个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
template<class DataType>
int ConnectionPool<DataType>::GetCount()
{
    return this->m_aliveCount + this->m_deadCount;
}

/*****************************************************************************
 函 数 名  : ConnectionPool.GetAliveCount
 功能描述  : 获取活动节点的总个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
template<class DataType>
int ConnectionPool<DataType>::GetAliveCount()
{
    return this->m_aliveCount;
}

/*****************************************************************************
 函 数 名  : ConnectionPool.GetDeadCount
 功能描述  : 获取非活动节点的总个数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
template<class DataType>
int ConnectionPool<DataType>::GetDeadCount()
{
    return this->m_deadCount;
}

/*****************************************************************************
 函 数 名  : ConnectionPool.GetMaxSize
 功能描述  : 获取连接池尺寸
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
template<class DataType>
int ConnectionPool<DataType>::GetMaxSize()
{
    return this->m_maxSize;
}

/*****************************************************************************
 函 数 名  : ConnectionPool.GetAliveObjs
 功能描述  : 获取活动节点队列
 输入参数  : 无
 输出参数  : 无
 返 回 值  : set<DataType*>&
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月20日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
template<class DataType>
set<DataType*>& ConnectionPool<DataType>::GetAliveObjs()
{
    return m_aliveObjs;
}

