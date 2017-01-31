//
//  DecoratorLog.hpp
//  logtest
//
//  Created by 李浩然 on 2017/1/31.
//  Copyright © 2017年 李浩然. All rights reserved.
//

#ifndef DecoratorLog_hpp
#define DecoratorLog_hpp

#include <stdio.h>
#include "BaseLog.hpp"

/*
 * 装饰类
 */
class DecoratorLog : public BaseLog
{
private:
    BaseLog *m_baselog;  //要装饰的日志
public:
    DecoratorLog(BaseLog *baselog): m_baselog(baselog) {}
    virtual void ShowDecorate() { m_baselog->ShowDecorate(); }
};


#endif /* DecoratorLog_hpp */
