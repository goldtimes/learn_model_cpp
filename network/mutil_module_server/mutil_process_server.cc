#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
  int sockfd;
  char on = 1;
  unsigned short port = 8000;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    std::cerr << "create socker error" << std::endl;
    exit(-1);
  }
  // 配置地址信息
  struct sockaddr_in server_addr;
  // 分配内存并清空地址
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htonl(port);
  server_addr.sin_family = AF_INET;
  // 端口复用
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  auto result =
      bind(sockfd, (struct sockaddr*)(&server_addr), sizeof(server_addr));
  if (result != 0)
  {
    std::cerr << "bind addr to socker error" << std::endl;
    close(sockfd);
    getchar();
    exit(-1);
  }
  // 监听连接
  result = listen(sockfd, 5);
  if (result != 0)
  {
    std::cerr << "get lister error" << std::endl;
    close(sockfd);
    getchar();
    exit(-1);
  }
  while (1)
  {
    char client_ip[INET_ADDRSTRLEN] = {0};
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    std::cout << "In Father process, get pid: " << getpid()
              << ",waiting client..." << std::endl;
    int connected_sock =
        accept(sockfd, (struct sockaddr*)(&client_addr), &client_addr_len);
    if (connected_sock < 0)
    {
      std::cerr << "accept error" << std::endl;
      close(sockfd);
      exit(-1);
    }
    pid_t pid = fork();
    if (pid < 0)
    {
      std::cerr << "fork error, return pid < 0" << std::endl;
      exit(-1);
    }
    else if (pid == 0)
    { //子进程
      close(sockfd);
      char recv_buf[1024] = {0};
      int recv_len = 0;
      memset(&client_addr, 0, sizeof(client_addr));
      inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
      std::cout << "---------------\n";
      std::cout << "client ip:" << client_ip
                << ",port:" << ntohs(client_addr.sin_port) << std::endl;
      while (recv_len = recv(connected_sock, recv_buf, sizeof(recv_buf), 0) > 0)
      {
        std::cout << "recv: " << recv_buf << std::endl;
        send(
            connected_sock, &recv_buf, sizeof(recv_buf), 0); // 给客户端返回数据
      }
      std::cout << "client_port:" << ntohs(client_addr.sin_port)
                << " closed \n";
      close(connected_sock);
      exit(0);
    }
    else
    {
      close(connected_sock);
    }
  }
  close(sockfd);
  return 0;
}