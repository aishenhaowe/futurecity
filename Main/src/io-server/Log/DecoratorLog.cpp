//
//  DecoratorLog.cpp
//  logtest
//
//  Created by 李浩然 on 2017/1/31.
//  Copyright © 2017年 李浩然. All rights reserved.
//

#include "DecoratorLog.hpp"
#include<iostream>

//具体的装饰类A
class DecoratorLogA : public DecoratorLog
{
public:
    DecoratorLogA(BaseLog *baselog) : DecoratorLog(baselog) {}
    void ShowDecorate() { DecoratorLog::ShowDecorate(); AddDecorate(); }
private:
    void AddDecorate() {
        
        const time_t t = time(NULL);
        std::cout<<"系统时间"<<std::endl;
        /*本地时间：日期，时间 年月日，星期，时分秒*/
        struct tm* current_time = localtime(&t);
        printf("今年是 %d;今月是 %d;今天是 %d\r\n",
               1900 + current_time->tm_year,
               1 + current_time->tm_mon/*此month的范围为0-11*/,
               current_time->tm_mday);
        
        printf("现在时间 %d:%d:%d \r\n",
               current_time->tm_hour,
               current_time->tm_min,
               current_time->tm_sec);
        
        printf("本地时间：%d-%d-%d %d:%d:%d\r\n",
               current_time->tm_year + 1900,
               current_time->tm_mon + 1,
               current_time->tm_mday,
               current_time->tm_hour,
               current_time->tm_min,
               current_time->tm_sec);
    } //增加的装饰
    
};
//具体的装饰类B
class DecoratorLogB : public DecoratorLog
{
public:
    DecoratorLogB(BaseLog *baselog) : DecoratorLog(baselog) {}
    void ShowDecorate() { DecoratorLog::ShowDecorate(); AddDecorate(); }
private:
    void AddDecorate() {
        std::cout<<"增加挂件B"<<std::endl;
        //TODO
    } //增加的装饰
};


