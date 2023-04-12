#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
constexpr int PORT = 9000;
constexpr int MAX_CLIENT = 5;
constexpr int BUFF_SIZE = 200;

int socketfds[MAX_CLIENT];  // socket描述符
int connected_count_amount; // 当前的连接数

void showClient()
{
  std::cout << "client amount:" << connected_count_amount << std::endl;
  for (int i = 0; i < MAX_CLIENT; ++i)
  {
    std::cout << "i: " << i << ", socketfds:" << socketfds[i] << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  int sockfd, connected_sockfd;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  unsigned int addr_len = sizeof(server_addr);

  char yes = 1;
  char buff[BUFF_SIZE];
  int ret_code;
  int i;
  // 建立套接字
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    std::cerr << "create socket error" << std::endl;
    exit(1);
  }
  // 设置端口复用
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)))
  {
    std::cout << "setsockopt" << std::endl;
  }
  // {
  //   std::cerr << "setsockopt error" << std::endl;
  //   exit(1);
  // }
  // 主机字节序
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  // bind addr
  if (bind(sockfd, (struct sockaddr*)(&server_addr), sizeof(server_addr)) == -1)
  {
    std::cerr << "bind error" << std::endl;
    close(sockfd);
    exit(-1);
  }
  if (listen(sockfd, MAX_CLIENT) != 0)
  {
    std::cerr << "listen error" << std::endl;
    close(sockfd);
    exit(-1);
  }
  // 定义文件描述符
  fd_set fd;
  int maxsock;

  struct timeval tv;
  connected_count_amount = 0;
  addr_len = sizeof(client_addr);
  maxsock = sockfd;
  while (1)
  {
    // 将描述符清零
    FD_ZERO(&fd);
    // 将socket描述符加入文件描述fd中
    FD_SET(sockfd, &fd);
    // 超时设置
    tv.tv_sec = 30;
    tv.tv_usec = 0;
    // 遍历socketfds数组，找到活动的socketfd，添加到fd文件描述符中
    for (int i = 0; i < MAX_CLIENT; ++i)
    {
      if (socketfds[i] != 0)
      {
        FD_SET(socketfds[i], &fd);
      }
    }
    // 系统调用select
    ret_code = select(maxsock + 1, &fd, nullptr, nullptr, &tv);
    if (ret_code < 0) // select没有找到有效连接
    {
      std::cerr << "select error" << std::endl;
      break;
    }
    else if (ret_code == 0) // 指定的超时时间到了
    {
      std::cout << "select timeout" << std::endl;
      continue;
    }
    // 判断定义的socketfds描述符中数据是否到达
    for (int i = 0; i < connected_count_amount; i++)
    {
      // 依次判断socketfd是否有数据到达
      if (FD_ISSET(socketfds[i], &fd))
      {
        ret_code = recv(socketfds[i], buff, sizeof(buff), 0);
        if (ret_code <= 0) // 客户端关闭连接
        {
          std::cout << "client: " << i << " close \n";
          close(socketfds[i]);
          FD_CLR(socketfds[i], &fd);
          socketfds[i] = 0;
          connected_count_amount--;
        }
        else // 收到数据
        {
          if (ret_code < BUFF_SIZE)
            memset(&buff[ret_code], '\0', 1); // 给尾部假设字符串结束符号
          std::cout << "client:" << i << ",send " << buff << std::endl;
          send(socketfds[i], buff, sizeof(buff), 0); // 发送数据给客户端
        }
      }
    }
    // 判断sockfd中是监听到新的连接
    if (FD_ISSET(sockfd, &fd))
    {
      connected_sockfd =
          accept(sockfd, (struct sockaddr*)(&client_addr), &addr_len);
      if (connected_sockfd < 0)
      {
        std::cerr << "accept error" << std::endl;
        continue;
      }
      // 当前连接的socket
      if (connected_count_amount < MAX_CLIENT)
      {
        for (int i = 0; i < MAX_CLIENT; ++i)
        {
          if (socketfds[i] == 0)
          {
            socketfds[i] = connected_sockfd;
            break;
          }
        }
        connected_count_amount++;
        std::cout << "connect client count:" << connected_count_amount
                  << ",client ip:" << inet_ntoa(client_addr.sin_addr)
                  << ",port:" << ntohs(client_addr.sin_port);
        if (connected_sockfd > maxsock)
        {
          maxsock = connected_sockfd;
        }
      }
      else
      {
        std::cout << "max connections arrive.exit!\n";
        send(connected_sockfd, "bye", 4, 0);
        continue;
      }
    }
    showClient();
  }
  for (int i = 0; i < MAX_CLIENT; ++i)
  {
    if (socketfds[i] != 0)
    {
      close(socketfds[i]);
    }
  }
  return 0;
}
