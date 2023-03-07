# 线程局部存储
## 声明和使用
```c++
struct X{
    thread_local int i;
};

thread_local X x;

int main()
{
    thread_local X b;
}
```

## 线程局部对象和线程中定义变量是不同的创建和销毁方式
```c++
std::mutex g_out_lock;

struct RefCount
{
    RefCount(const char* f) : i(0), func(f)
    {
        std::local_guard<std::mutex> lock(g_out_local);
        std::cout << std::this_thread::get_id() << "|" <<func<< ":ctor i("<<i<<")" << std::endl;
    }
    ~RefCount()
    {

        std::local_guard<std::mutex> lock(g_out_local);
        std::cout << std::this_thread::get_id() << "|" <<func<< ":ctor i("<<i<<")" << std::endl;
    }
    void inc()
    {
        std::local_guard<std::mutex> lock(g_out_local);
        std::cout << std::this_thread::get_id() << "|" <<func<< ":ctor i("<<i<<")" << std::endl;
        i++;
    }
    int i;
    std::string func;
};

void foo(const char* f)
{
    std::string s(f);
    thread_local RefCount tv(s.append("#foo").c_str());
    tv.inc();
}

void bar(const char* f)
{
    std::string s(f);
    thread_local RefCount tv(s.append("#bar").c_str());
    tv.inc();
}

void thread1()
{
    const char* s = "tread1";
    foo(s);
    foo(s);
    foo(s);
}

void thread2()
{
    const char* s = "tread2";
    foo(s);
    foo(s);
    foo(s);
}

void thread3()
{
    const char*s = "tread3";
    bar(s);
    foo(s);
    foo(s);
}

//最后来说明一下线程局部存储对象的初始化和销毁。在同一个线程中，
//一个线程局部存储对象只会初始化一次，即使在某个函数中被多次调用。这一点和单线程程序中的静态对象非常相似。
int main()
{
    std::thread t1(thead1);
    std::thread t2(thread2);
    std::thread t3(thread3);

    t1.join();
    t2.join();
    t3.join();
}
```
