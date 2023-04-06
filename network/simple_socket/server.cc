#include <cstdio>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv)
{
  int addr_len, err;
  char on = 1;
  // 创建socket，阻塞的套接字
  int sock_srv = socket(AF_INET, SOCK_STREAM, 0);
  // 允许地址重用
  setsockopt(sock_srv, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  struct sockaddr_in get_sock_addr, bind_addr;
  memset(&bind_addr, 0, sizeof(struct sockaddr_in));
  bind_addr.sin_addr.s_addr = inet_addr("10.33.33.37");
  bind_addr.sin_family = AF_INET;
  bind_addr.sin_port = htons(8000);
  // bind
  auto bind_result =
      bind(sock_srv, (struct sockaddr*)(&bind_addr), sizeof(struct sockaddr));
  if (bind_result == -1)
  {
    std::cout << "bind error" << std::endl;
    return -1;
  }
  // 获取本地套接字地址
  addr_len = sizeof(struct sockaddr_in);
  getsockname(
      sock_srv, (struct sockaddr*)(&get_sock_addr), (socklen_t*)&addr_len);
  std::cout << "ip:" << inet_ntoa(get_sock_addr.sin_addr)
            << ",port:" << ntohs(get_sock_addr.sin_port) << std::endl;
  // 设置最大的监听连接数
  listen(sock_srv, 5);

  struct sockaddr_in client_addr;
  int len = sizeof(sockaddr_in);
  while (true)
  {
    std::cout << "-------------wait client---------------" << std::endl;
    // 获取请求队列中最前的一个客户请求
    // accept 是阻塞的，等待客户端的连接
    int request_sock =
        accept(sock_srv, (struct sockaddr*)(&client_addr), (socklen_t*)&len);
    char send_buff[100];
    // std::cout << "welcome client:" << inet_ntoa(client_addr.sin_addr)
    //           << "to server!/n";
    sprintf(
        send_buff,
        "welcome client(%s) to server!",
        inet_ntoa(client_addr.sin_addr));
    // 将应用层的send_buff放到协议栈的缓冲区(内核buff);
    // 阻塞，直到内核buff的空间足够放下send_buff
    send(request_sock, send_buff, strlen(send_buff) + 1, 0);
    char recv_buff[100];
    // 也是阻塞的，等待客户端的数据
    recv(request_sock, recv_buff, 100, 0);
    printf("recv msg: %s\n", recv_buff);
    close(request_sock); // 关闭已连接的socket
    puts("continue to listen?(y/n)");
    char ch[2];
    scanf("%s", ch, 2);
    if (ch[0] != 'y')
      break;
  }
  close(sock_srv); // 关闭监听的socket
  return 0;
}
