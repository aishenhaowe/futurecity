/******************************************************************************

                  版权所有 (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  文 件 名   : Server.h
  版 本 号   : 初稿
  作    者   : ChenZhen
  生成日期   : 2017年2月17日
  最近修改   :
  功能描述   : Server.cc 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2017年2月17日
    作    者   : ChenZhen
    修改内容   : 创建文件

******************************************************************************/
#ifndef __SERVER_H__
#define __SERVER_H__


/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "InnerHandleThread.h"
#include "OuterHandleThread.h"
#include "OuterTimerThread.h"

using namespace std;


/*----------------------------------------------*
 * 类声明                                       *
 *----------------------------------------------*/
class Server
{
/* Public Methods */
public:
    Server();
    virtual ~Server();

    int GetTag();
    int Init(string configPath);
    int Run();

/* Public Members */
public:
    InnerHandleThread       *m_InnerHandleThread;
    OuterHandleThread       *m_OuterHandleThread;
    OuterTimerThread        *m_OuterTimerThread;

/* Protected Methods */
protected:

/* Protected Members */
protected:

/* Private Methods */
private:

/* Private Members */
private:
    int                     m_tag;
    string                  m_configPath;
};


#endif /* __SERVER_H__ */
