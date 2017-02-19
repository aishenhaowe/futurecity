/******************************************************************************

                  版权所有 (C), 2001-2011, IOT CopyRight

 ******************************************************************************
  文 件 名   : InnerHandleThread.cc
  版 本 号   : 初稿
  作    者   : ChenZhen
  生成日期   : 2017年2月19日
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :
  1.日    期   : 2017年2月19日
    作    者   : ChenZhen
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "InnerHandleThread.h"
#include "BaseHandleThread.h"


InnerHandleThread::InnerHandleThread(Server *server, const string &host, short port, int backLog):
    BaseHandleThread(server, host, port, backLog)
{

}


