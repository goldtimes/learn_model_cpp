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

# UDP
目标：
  需要掌握UDP和TCP的区别

# 多进程并发服务器
  ## 理解fork()系统调用函数
  fork创建子进程。在父进程中创建一个新的进程-子进程。
  子进程完成对父进程的写时copy.但是复制进程的开销比较大，开销在哪呢？
  进程上下文、代码区、数据区、堆区、栈区、内存信息、文件描述符、信号处理函数、进程优先级、
  当前工作目录、根目录等等等。
  通过PID来区分子进程和父进程。子进程对父进程的存储空间拷贝，而不是共享。
  ```C++
  #include <>
  int main()
  {
    while(1)
    {
      int sockfd = socket(); // 属于内核对象，对内核对象进行引用次数+1
      int connect_sockfd = accept();
      if(fork() == 0) //子进程执行的代码
      {
        // 因为子进程对sockfd复制了，引用计数+1。此时的引用计数为2。
        // 那么如果先在这里关闭一次，父进程关闭一次。这个socket对象才真正的被释放了。
        close(sockfd); 
        fun();
        close(connect_sockfd);// 同理
        exit(0);
      }
      close(connect_sockfd); // 同理
    }
    close(sockfd);
    return 0;
  }
  ```

# 多线程服务器
## 工作模型
```c++
#include <>

int main()
{
  int sockfd = socket();
  bind(sockfd);
  liste(sockfd);
  while(1)
  {
    int conn_fd = accept();
    pthread_t tid;
    pthread_create(&tid, nullptr, client_fun, (void*) conn_fd);
    pthread_deatch(tid);
  }
  close(sockfd);
  return 0;
}

void * client_fun(void *argc)
{
  int conn_fd = (int) argv;
  func(); // 真正处理服务器请求的地方
  close(connfd);
}
```
# IO多路复用
通过某种机制，在一个进程内去监听多个socket描述符，一旦某个socket描述符就绪之后
，通知程序进行相应的读写。select, pselect, poll, epoll等同步I/O。首先这些函数是同步的
，然后用户讲内核数据->应用程序的读写是阻塞的。
优势在于 系统开销小。而select是一般操作系统实现的。epoll是linux操作系统所特有的。
## 使用场景
### 客户端
* 客户端处理多个文件描述符(交互式输入和网络socket)
* 客户端处理多个套接字
### 服务器
* TCP同时处理多个套接字，既要监听套接字，又要处理已连接的套接字
* 服务器既要处理TCP，又要处理UDP
* 服务器要处理多个服务或者协议

## selectI/O多路复用的服务器

## pollI/O多路复用的服务器
* linux系统write函数
```c++
// fd为文件描述符(套接字、磁盘)
// buf 数据缓冲区
// count 写的数据个数
// return 写入的字节数，发生错误的时候为-1，写入errno;
ssize_t write(int fd, const void* buf, size_t count);
```
* linux系统read函数
```c++
// 函数返回实际读取到的字节数，如果返回0，则到达文件尾部或者没有数据。
// 返回值可能小于count(想要读取的字节数)
  // * 在读取count个字节之前，就达到文件末尾
// 网络套接字，返回值可能小于count.
// 阻塞： fd文件描述符中的字节比如是50个字节，但是count指定了100个字节(想要的)，那么有可能阻塞
// 常规文件不会阻塞，文件只有10个字节，但是我想要100.这种情况不会阻塞，读到多少就是多少。
ssize_t read(int fd, const void* buf, size_t count);

```
## epoll I/O多路复用的服务器
epoll 为什么效率比select高？ 
select模型中，需要对所有的文件描述符监听，然后对目标文件描述符需要遍历整个数组来
找到是否准备好了数据。对于数十万的并发，如果某一时刻只有几百个活跃连接，那么遍历所有的文件描述符，效率是不高的。而内核使用轮询的方式检测FD_SET中的文件描述符

### epoll的实现方式
1. 通过epoll_create创建epoll描述符
2. 通过函数epoll_ctrl 添加或者删除所有待监控的连接,不频繁调用
3. epoll_wait返回活跃的连接， 需要频繁调用。
epoll的三个关键实现细节： mmap, 红黑树， 双向链表。
#### mmap技术
首先要明白文件是存放在磁盘中的。那么当用户的进程需要读取并修改文件的操作要经历：
进程运行，会分配虚拟内存， 进程读取文件，将文件拷贝进内核内存，然后在读到用户进程的虚拟内存中，同样如果修改数据后，写入文件也是先修改虚拟内存中的文件，然后写入内核中的
内存，最后写到磁盘。
mmap技术就是将用户空间的虚拟内存地址和文件进行绑定。对映射后的虚拟内存进行读写操作，就如同对文件读写操作一样。
mmap将用户空间的一块地址和内核空间的一块地址同时映射到相同的一块物理内存地址（不管是用户空间还是内核空间都是虚拟地址，最终要通过地址映射到物理地址），使得这块物理内存对内核和用户均可见，减少用户态和内核态之间的数据交换
红黑树和双向链表的数据结构都是为了加快插入和查找的性能。


