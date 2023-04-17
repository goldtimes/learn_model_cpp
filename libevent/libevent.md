# libevent 
是一个开源的高性能事件通知库。
## Reactor模式
Reactor-事件驱动设计模式
### 普通程序的函数调用处理：
1. 声明并且定义某函数read
2. 程序在某处调用该函数read
3. 等待read函数执行完，将结果返回给调用函数的地方
4. 程序继续
### Reactor模式
应用程序不需要主动调用read函数。而是将read函数注册到reactor上。
所以应用程序需要维护一个reactor对象(单例模式)。那么什么时候处罚这个read函数呢？
比如我们约定了收到数据的时候(触发事件)，reactor去调用read函数。
read函数也称为应用程序的回调函数。
理解这个模型可以用生活中的例子情况。
普通函数调用的情况就是： 
reactor的模式就是: 去面试，然后面试官是有你的电话号码的.面试完，等待结果出来。但是你不用一直等待，因为结果出来的时候，你就可以接收到HR的电话通知。 电话是不是可以看做一个回调函数呢？

## 使用Libevent
下载
配置 
```
     cd libevent-2.1.12-stable/
     ./configure --prefix=/opt/libevent
```
--prefix=/opt/libevent 将头文件和动态库放在了/opt/libevent目录下
但是我们默认的动态库连接是在/usr/local/lib中，所以可以创建软链接
需要创建这两个软链接，否则编译会出错
```
sudo ln -s /opt/libevent/lib/libevent.so /usr/local/lib/libevent.so 
sudo ln -s /opt/libevent/lib/libevent-2.1.so.7 /usr/local/lib/libevent-2.1.so.7 
```
编译
```
 g++ event.cc -o event -I /opt/libevent/include/ -L /opt/libevent/lib/ -levent
```