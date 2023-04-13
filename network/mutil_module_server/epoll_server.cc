#include <ctype.h>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h> // for close
#include <iostream>
#include <string>

constexpr int MAXLINE = 80;
constexpr int SEVERPORT = 8888;
constexpr int OPEN_MAX = 1024;

void errExit(const std::string& error = "")
{
  std::cerr << "get error:" << error << std::endl;
  getchar();
  exit(-1);
}

int main(int argc, char** argv)
{
  int sockfd, connected_sockfd, listen_fd;
  int nready, res;
  ssize_t n;

  char buff[MAXLINE], str[INET_ADDRSTRLEN];
  socklen_t client_len;
  int client[OPEN_MAX]; // 客户端的数组
  struct sockaddr_in client_addr, server_addr;
  struct epoll_event temp_ep_event, ep_events[OPEN_MAX];

  // socket
  listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(SEVERPORT);
  server_addr.sin_family = AF_INET;
  // bind
  auto result =
      bind(listen_fd, (struct sockaddr*)(&server_addr), sizeof(server_addr));
  if (result == -1)
  {
    close(listen_fd);
    errExit("bind error");
  }
  // listen
  result = listen(listen_fd, 20);
  if (result == -1)
  {
    close(listen_fd);
    errExit("listen error");
  }
  //   std::cout << "sizeof(client):" << sizeof(client) << std::endl;
  memset(client, -1, sizeof(client));
  //   for (const auto& i : client)
  //   {
  //     std::cout << i << " ";
  //   }
  int maxi = -1;
  int efd = epoll_create(OPEN_MAX); // 创建epoll句柄，底层创建了一个红黑树。
  if (efd == -1)
  {
    errExit("create epoll error");
  }
  // 创建 epoll_event
  temp_ep_event.events = EPOLLIN;
  temp_ep_event.data.fd = listen_fd;
  // 添加监听套接字到epoll套接字，并添加temp_ep_event
  result = epoll_ctl(efd, EPOLL_CTL_ADD, listen_fd, &temp_ep_event);
  if (result == -1)
  {
    close(listen_fd);
    errExit("epoll_ctl error");
  }
  while (1)
  {
    // 一直阻塞监听，传入epoll句柄，还有定义的events数组，最大的event事件。
    // 返回就绪的文件描述符的个数
    int ready = epoll_wait(efd, ep_events, OPEN_MAX, -1);
    if (nready == -1)
      errExit("epoll wait error");
    for (int i = 0; i < nready; ++i)
    {
      // 不是读的事件
      if (!(ep_events[i].events & EPOLLIN))
        continue;
      if (ep_events[i].data.fd = listen_fd) // 判断发生的事件来自与监听套接字
      {
        client_len = sizeof(client_addr);
        // 获取连接的客户端socket
        connected_sockfd =
            accept(listen_fd, (struct sockaddr*)(&client_addr), &client_len);
        std::cout << "recv from client ip:"
                  << inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str))
                  << ",port:" << ntohs(client_addr.sin_port);
        int j = 0;
        for (j = 0; j < OPEN_MAX; ++j)
        {
          if (client[j] < 0)
          {
            // 将客户端的通信套接字存放到client数组中
            client[j] = connected_sockfd;
            break;
          }
        }
        // 如果客户端到达最大值
        if (j == OPEN_MAX)
          errExit("too many clients");
        // 更新当前client的个数
        if (j > maxi)
          maxi = j;
        // 添加客户端连接的socket到epoll红黑树中
        temp_ep_event.events = EPOLLIN;
        temp_ep_event.data.fd = connected_sockfd;
        // 将已连接的客户端socket放到epoll的红黑树中，并监听事件
        result =
            epoll_ctl(efd, EPOLL_CTL_ADD, connected_sockfd, &temp_ep_event);
        if (result == -1)
          errExit("epoll_ctl");
      }
      // 这里不是监听套接字的代码执行块，而是epoll中监听的connectsocks
      else
      {
        // 获取活动的sockets
        sockfd = ep_events[i].data.fd;
        // 读取数据
        int read_len = read(sockfd, buff, MAXLINE);
        if (read_len == 0) // 无数据，删除该节点
        {
          int j = 0;
          for (j = 0; j <= maxi; ++j)
          {
            if (client[j] == sockfd)
            {
              client[j] = -1;
              break;
            }
          }
          // 从epoll树节点删除该sockfd
          result = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, nullptr);
          if (result == -1)
            errExit("epoll_ctl error");
          close(sockfd);
          std::cout << "client:" << j << ", closed connection." << std::endl;
        }
        else
        {
          std::cout << "recive data size: " << read_len << std::endl;
          for (int j = 0; j < read_len; ++j)
          {
            buff[j] = toupper(buff[j]);
          }
          write(sockfd, buff, sizeof(buff));
        }
      }
    }
  }
  return 0;
}