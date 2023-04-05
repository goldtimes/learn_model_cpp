#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <cstdio>

int main(int argc, char** argv)
{
  int sfp; // 创建socket返回的结果
  // 结构体对象
  struct sockaddr_in s_add;
  unsigned short port = 10051;
  struct sockaddr_in s_addr = {0};
  char on = 1;
  // 根据不同的平台，申明不同的address长度
  int addr_len = sizeof(sockaddr_in);
  // sock_stream tcp
  // sock_dgram upd
  // sock_raw
  // AF_INET ipv4
  sfp = socket(AF_INET, SOCK_STREAM, 0);
  if (sfp == -1)
  {
    std::cerr << "socket fail" << std::endl;
    return -1;
  }
  std::cout << "socket ok!" << std::endl;
  std::cout << "ip:" << inet_ntoa(s_addr.sin_addr)
            << ",port:" << ntohs(s_addr.sin_port) << std::endl;
  // 地址重用
  setsockopt(sfp, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  // 将这个结构体赋值为0
  memset(&s_add, 0, sizeof(struct sockaddr_in));
  s_add.sin_family = AF_INET;
  s_add.sin_addr.s_addr = inet_addr("192.168.0.197");
  s_add.sin_port = htons(port);

  // bind socket对象绑定本地的地址
  auto bind_result =
      bind(sfp, (struct sockaddr*)(&s_add), sizeof(struct sockaddr));
  if (bind_result == -1)
  {
    std::cerr << "bind address error" << std::endl;
    return -1;
  }
  std::cout << "bind ok" << std::endl;
  getsockname(sfp, (struct sockaddr*)(&s_addr), (socklen_t*)(&addr_len));
  std::cout << "bind after ip:" << inet_ntoa(s_addr.sin_addr)
            << ",port:" << ntohs(s_addr.sin_port) << std::endl;
  return 0;
}