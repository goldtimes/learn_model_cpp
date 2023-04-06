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

char wbuf[50];

using SOCKADDR_IN = struct sockaddr_in;
using SOCKADDR = struct sockaddr;

int main(int argc, char** argv)
{
  int sockfd, addr_size, ret;
  char on = 1;

  SOCKADDR_IN addr;
  addr_size = sizeof(SOCKADDR_IN);
  memset(&addr, 0, addr_size);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("192.168.0.197");
  addr.sin_port = htons(9999);
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (sockfd < 0)
  {
    std::cerr << "create socket error" << std::endl;
    return -1;
  }

  // 端口复用
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  puts("please enter data:");
  scanf("%s", wbuf, sizeof(wbuf));
  // sendto
  ret = sendto(
      sockfd, wbuf, sizeof(wbuf), 0, (SOCKADDR*)(&addr), sizeof(SOCKADDR));
  if (ret < 0)
  {
    std::cout << "sendto failed." << std::endl;
  }
  close(sockfd);
  getchar();
  return 0;
}