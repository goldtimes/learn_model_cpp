#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>

char rbuf[50];

using SOCKADDR_IN = struct sockaddr_in;

int main(int argc, char** argv)
{
  int sockfd, addr_size;
  char on = 1;
  SOCKADDR_IN server_addr;
  SOCKADDR_IN client_addr;

  addr_size = sizeof(SOCKADDR_IN);
  memset(&server_addr, 0, addr_size);
  server_addr.sin_addr.s_addr = inet_addr("192.168.0.197");
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(9999);
  // 创建套接字
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
  {
    std::cerr << "scoket error" << std::endl;
    return -1;
  }
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  bind(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr));
  int addr_len = sizeof(struct sockaddr);
  puts("waiting data");
  auto ret = recvfrom(
      sockfd,
      rbuf,
      50,
      0,
      (struct sockaddr*)(&client_addr),
      (socklen_t*)(&addr_len));
  std::cout << "recv data:" << rbuf << std::endl;
  close(sockfd);
  getchar();
  return 0;
}