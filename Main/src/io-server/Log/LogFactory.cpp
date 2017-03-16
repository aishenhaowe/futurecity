//
//  main.cpp
//  logtest
//
//  Created by 李浩然 on 2017/1/30.
//  Copyright © 2017年 李浩然. All rights reserved.
//

#include <iostream>
#include "BaseLog.cpp"
#include "DecoratorLog.cpp"


/**
 *   主程序测试
 */

int main(int argc, const char * argv[]) {
    // insert code here...
    BaseLog *baselog = new Log1("0000");
    BaseLog *dpa = new DecoratorLogA(baselog); //装饰，增加挂件
    BaseLog *dpb = new DecoratorLogB(dpa);    //装饰，增加挂件
    dpb->ShowDecorate();
    delete dpa;
    delete dpb;
    delete baselog;
    return 0;
}
