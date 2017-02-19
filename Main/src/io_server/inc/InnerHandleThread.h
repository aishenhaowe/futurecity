/******************************************************************************

                  版权所有 (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  文 件 名   : InnerHandleThread.h
  版 本 号   : 初稿
  作    者   : ChenZhen
  生成日期   : 2017年2月17日
  最近修改   :
  功能描述   : InnerHandleThread.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2017年2月17日
    作    者   : ChenZhen
    修改内容   : 创建文件

******************************************************************************/
#ifndef __INNERHANDLETHREAD_H__
#define __INNERHANDLETHREAD_H__


/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "BaseHandleThread.h"
using namespace std;

class Server;

/*----------------------------------------------*
 * 类声明                                       *
 *----------------------------------------------*/
class InnerHandleThread : public BaseHandleThread
{
public:
    InnerHandleThread(Server *server, const string &host, short port, int backLog);
    ~InnerHandleThread();
    
public:
    
protected:
    
protected:
    
private:
    
private:
    Server      *m_server;
};




#endif /* __INNERHANDLETHREAD_H__ */

