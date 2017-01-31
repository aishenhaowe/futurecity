//
//  BaseLog.cpp
//  logtest
//
//  Created by 李浩然 on 2017/1/30.
//  Copyright © 2017年 李浩然. All rights reserved.
//

#include "BaseLog.hpp"
#include<iostream>

using namespace std;

/**
 *  log具体类
 */
class Log1 : public BaseLog{
private:
    std::string m_name;
public:
    Log1(std::string name): m_name(name){}
    ~Log1() {}
    void ShowDecorate() { std::cout<<m_name<<"的装饰"<<std::endl;}
};
