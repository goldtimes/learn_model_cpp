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
  int sock_addr_len, err;
  char on = 1;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  char msg[] = "hi, server!";
  sockaddr_in server_addr;
  server_addr.sin_addr.s_addr = inet_addr("10.33.33.37");
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(8000);
  // 发起连接
  err =
      connect(sock, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr));
  if (err == -1)
  {
    std::cout << "connect to server error" << std::endl;
    return -1;
  }

  char recv_buff[100];
  recv(sock, recv_buff, 100, 0);
  std::cout << "recv msg:" << recv_buff << std::endl;
  send(sock, msg, strlen(msg) + 1, 0);
  close(sock);
  getchar();

  //   // 允许地址重用
  //   setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  //   struct sockaddr_in bind_addr, get_sock_addr;
  //   memset(&bind_addr, 0, sizeof(struct sockaddr_in));
  //   bind_addr.sin_addr.s_addr = inet_addr("10.33.33.37");
  //   bind_addr.sin_family = AF_INET;
  //   bind_addr.sin_port = htons(10056);
  //   auto bind_result =
  //       bind(sock, (struct sockaddr*)(&bind_addr), sizeof(struct
  //       sockaddr));
  //   if (bind_result == -1)
  //   {
  //     std::cout << "client bind error" << std::endl;
  //     return -1;
  //   }
  //   sock_addr_len = sizeof(struct sockaddr_in);
  //   getsockname(
  //       sock, (struct sockaddr*)(&get_sock_addr),
  //       (socklen_t*)&sock_addr_len);
  //   std::cout << "client ip:" << inet_ntoa(get_sock_addr.sin_addr)
  //             << ",port:" << ntohs(get_sock_addr.sin_port) << std::endl;

  // }
}