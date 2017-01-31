include <iostream>

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
//具体的装饰类A
class DecoratorLogA : public DecoratorLog
{
public:
    DecoratorLogA(BaseLog *baselog) : DecoratorLog(baselog) {}
    void ShowDecorate() { DecoratorLog::ShowDecorate(); AddDecorate(); }
private:
    void AddDecorate() { std::cout<<"增加挂件A"<<std::endl; } //增加的装饰
};
//具体的装饰类B
class DecoratorLogB : public DecoratorLog
{
public:
    DecoratorLogB(BaseLog *baselog) : DecoratorLog(baselog) {}
    void ShowDecorate() { DecoratorLog::ShowDecorate(); AddDecorate(); }
private:
    void AddDecorate() { std::cout<<"增加挂件B"<<std::endl; } //增加的装饰
};


/**
 *   主程序测试
 */

int main(int argc, const char * argv[]) {
    // insert code here...
    BaseLog *baselog = new Log1("0000");
    BaseLog *dpa = new DecoratorLogA(baselog); //装饰，增加挂件
    BaseLog *dpb = new DecoratorLogB(dpa);    //装饰，屏幕贴膜
    dpb->ShowDecorate();
    delete dpa;
    delete dpb;
    delete baselog;
//    std::cout << "Hello, World!\n";
    return 0;
}

