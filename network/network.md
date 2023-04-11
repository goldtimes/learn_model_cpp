# 套接字
## 协议簇
* AF_INET  ipv4
* AF_INET6  ipv6
## socket 类型
* SOCKET_STREAM //tcp 类型
* SOCKET_DGRAW  // udp 报文
* SOCKET_RAW
```c++
// 创建ipv4的tcp协议 socket
int sfp = socket(AF_INET, SOCK_STREAM, 0);

// 将这个结构体赋值为0
  memset(&s_add, 0, sizeof(struct sockaddr_in));
  // 设置ipv4
  s_add.sin_family = AF_INET;
  // inet_addr将字符串ip地址装换成2进制
  s_add.sin_addr.s_addr = inet_addr("192.168.0.197");
  // 设置端口号
  s_add.sin_port = htons(port);

  // bind socket对象绑定本地的地址
  auto bind_result =
      bind(sfp, (struct sockaddr*)(&s_add), sizeof(struct sockaddr));
  // 获取socket的local地址
  getsockname(sfp, (struct sockaddr*)(&s_addr), (socklen_t*)(&addr_len));
```
# 字节序
内存->分为很多歌存储单元，单元是以字节为单位的。
CPU 16/32/64的处理器决定了一次性读取多少个字节。
x86结构是小端模式
ARM,DSP一般也为小端，ARM可以由硬件来决定是大端还是小端
## 主机字节序
首先内存的地址顺序肯定是低->高。那么小端就是数据低字节在内存低地址，大端就是数据高字节存放在内存低地址
* 小端字节序
数据的低字节存放在内存低地址，高字节存放在高地址
* 大端字节序
0x12345678 long类型的8字节数据
地址(32位)     数据（小端模式）   数据(大端模式)
0x0029f458    0x78             0x12
0x0029f459    0x56             0x34
0x0029f45a    0x34             0x56
0x0029f45b    0x12             0x78
数据的高字节存放在内存低地址，低字节数据放在高地址
## 网络字节序
* htonl() 主机字节序->网络字节序(大端) 处理uint32
* ntohl() 和htonl()相反
* htons()  处理unit16
* ntohs()

# TCP套接字开发流程
## 服务端
1. 创建套接字
2. 使用bind函数绑定服务的ip和端口
3. 套接字对象使用listen()函数来监听连接
4. 有请求到了之后，调用accept函数接受连接，返回一个新的套接字
5. 通过返回的新的套接字来send/recv信息。
6. 通信关闭，调用closesocket来关闭该返回的新socket
7. 监听套接字继续监听，等待新的连接
## 
客户端
1. 创建连接socket
2. 调用connect来向服务器发起连接。
3. send/recv发送和接受信息

# Socket数据收发的情况
## 发送数据的情况
需要假设网络拥堵和tcp的协议中的内核缓冲区不够应用层的发送数据。总共有六种情况。
## 接受数据的情况
* 一次请求响应的数据接收
接受端接受完全部数据后，接受结束，发送端断开连接。接受端通过过判断连接是否关闭来判断接受数据过程是否结束。
关键的是： 通过result = recv()的结果为0来判断数据发送完毕。
* 多次响应的数据接收
  * 定长数据接收
  while 去判断接受数据长度是否满足我们约定的长度。
  {
    do{
      result = recv()
    }while(resuilt > 0);
  }
  * 不定长的数据接收
  struct Mydata
  {
    int data_len;
    char data[];
  }; //sizeof(Mydata) == 4;  


  # 多进程并发服务器
  ## 理解fork()系统调用函数
  fork创建子进程。在父进程中创建一个新的进程-子进程。
  子进程完成对父进程的写时copy.但是复制进程的开销比较大，开销在哪呢？
  进程上下文、代码区、数据区、堆区、栈区、内存信息、文件描述符、信号处理函数、进程优先级、
  当前工作目录、根目录等等等。
  通过PID来区分子进程和父进程。子进程对父进程的存储空间拷贝，而不是共享。
