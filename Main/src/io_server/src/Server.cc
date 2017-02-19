/******************************************************************************

                  版权所有 (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  文 件 名   : Server.cc
  版 本 号   : 初稿
  作    者   : ChenZhen
  生成日期   : 2017年2月17日
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :
  1.日    期   : 2017年2月17日
    作    者   : ChenZhen
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include <iostream>
#include <unistd.h>

#include "Server.h"


/*****************************************************************************
 函 数 名  : Server.Server
 功能描述  : 构造函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月17日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
Server::Server()
{
    this->m_InnerHandleThread       = NULL;
    this->m_OuterHandleThread       = NULL;
    this->m_OuterTimerThread        = NULL;
    this->m_tag                     = 0;
}

/*****************************************************************************
 函 数 名  : Server.~Server
 功能描述  : 析构函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月17日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
Server::~Server()
{
    
}

/*****************************************************************************
 函 数 名  : Server.GetTag
 功能描述  : 获取TAG
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月17日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int Server::GetTag()
{
    return this->m_tag;
}

/*****************************************************************************
 函 数 名  : Server.Init
 功能描述  : 初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月17日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int Server::Init(string configPath)
{
    m_configPath = configPath;
    
    return 0;
}

/*****************************************************************************
 函 数 名  : Server.Run
 功能描述  : 运行服务器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2017年2月17日
    作    者   : ChenZhen
    修改内容   : 新生成函数

*****************************************************************************/
int Server::Run()
{
    /* 先启动Handle */
    this->m_OuterHandleThread = new OuterHandleThread(this);
    this->m_InnerHandleThread = new InnerHandleThread(this);
    this->m_OuterTimerThread  = new OuterTimerThread(this);
    
    while(1)
    {
        //sleep(1);
    }
    
    return 0;
}

