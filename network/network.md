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