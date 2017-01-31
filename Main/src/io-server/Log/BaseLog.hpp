//
//  BaseLog.hpp
//  logtest
//
//  Created by 李浩然 on 2017/1/30.
//  Copyright © 2017年 李浩然. All rights reserved.
//

#ifndef BaseLog_hpp
#define BaseLog_hpp

#include <stdio.h>
/**
 *  log基类
 */
class BaseLog
{
public:
    BaseLog() {}
    virtual ~BaseLog() {}
    virtual void ShowDecorate() {}
};

#endif /* BaseLog_hpp */
