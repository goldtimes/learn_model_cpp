#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <cstring>
#include <initializer_list>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <time.h>

void errExit(const std::string& error_msg)
{
  std::cerr << "get error: " << error_msg << std::endl;
  getchar();
  exit(-1);
}

const std::string resp = R"("HTTP/1.1 200\r\n\
Content-Type: application/json\r\n\
Content-Length: 13\r\n\
Date: Thu, 2 Aug 2021 04:02:00 GMT\r\n\
Keep-Alive: timeout=60\r\n\
Connection: keep-alive\r\n\r\n\
[HELLO WORLD]\r\n\r\n";)";
constexpr unsigned int PORT = 8888;

int main(int argc, char** argv)
{
  int sockfd, return_code;
  // 创建套接字
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
    errExit("create_socket");
  // 端口复用
  char on = 1;
  auto result = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  // if (result == -1)
  //   errExit("set socketopt error");
  // bind 地址
  struct sockaddr_in server_addr;
  unsigned int server_addr_len;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  server_addr.sin_family = AF_INET;
  result = bind(sockfd, (struct sockaddr*)(&server_addr), sizeof(server_addr));
  if (result == -1)
    errExit("bind_error");
  if (listen(sockfd, 1024))
    errExit("listen error");
  // 以上为create+bind+listen的模式创建监听套接字完毕
  // 使用poll
  int currentFdNums = 1;
  // 创建pollfd类型的数组，数组大小为100;
  pollfd* fds = static_cast<pollfd*>(calloc(100, sizeof(pollfd)));
  fds[0].fd = sockfd;
  fds[0].events = POLLIN;
  nfds_t nfds = 1;
  int timeout = -1; // 一直等待
  std::cout << "polling" << std::endl;
  while (1)
  {
    return_code = poll(fds, 1, timeout);
    if (return_code == -1)
      errExit("polling return error.");
    else if (return_code == 0)
      std::cout << "poll return no data\n";
    else // get return > 0
    {
      // 有客户端的连接
      // 检查fds
      if (fds[0].revents & POLLIN)
      {
        // 获取客户端的连接
        struct sockaddr_in client_addr;
        socklen_t client_addr_len;
        int childfds = accept(
            fds[0].fd, (struct sockaddr*)(&client_addr), &client_addr_len);
        if (childfds == -1)
          errExit("accept error");
        // 设置childfds为非阻塞的socket
        int flag = fcntl(childfds, F_GETFL);
        if (fcntl(childfds, F_SETFL, flag | O_NONBLOCK) == -1)
          errExit("设置非阻塞socket error");
        // 将childfds添加到fds，并设置POLLIN事件
        fds[currentFdNums].fd = childfds;
        fds[currentFdNums].events = (POLLIN | POLLRDHUP);
        nfds++;
        currentFdNums++;
        std::cout << "child:" << currentFdNums - 1 << "push to poll list"
                  << std::endl;
      }
      // childfds read & write 遍历fds
      for (int i = 0; i < currentFdNums; ++i)
      {
        if (fds[i].revents & (POLLHUP | POLLRDHUP | POLLNVAL))
        {
          // 客户端描述符关闭
          // 设置当前的fd = -1，event = 0.不在关心
          std::cout << "child:" << i << ",shutdown\n";
          close(fds[i].fd);
          fds[i].events = 0;
          fds[i].fd = -1;
          continue;
        }
        // read
        if (fds[i].revents & POLLIN)
        {
          //接受buffer
          char recv_buff[1024] = {};
          int ret_code = 0;
          while (1)
          {
            // 读取数据
            ret_code = read(fds[i].fd, recv_buff, sizeof(recv_buff));
            std::cout << "read data from child:" << i << ",datas:" << ret_code
                      << std::endl;
            // 读数据要分三种情况
            if (ret_code == 0) // 连接断开
            {
              std::cout << "read EOF\n";
              break;
            }
            // 对于网络套接字，ret_code == -1不代表错误
            if (ret_code == -1)
            {
              const int tempErrno = errno;
              // EWOULDBLOCK|EAGAIN 表示读取会阻塞，等待下一次读取
              if (tempErrno == EWOULDBLOCK || tempErrno == EAGAIN)
              {
                std::cout << "read would block, stop reading\n";
                // 因为等待到了一次读取操作，就可以设置为POLLIN|POLLOUT
                // 关心读写操作
                fds[i].events |= POLLOUT;
                break;
              }
              else
              {
                errExit("read error");
              }
            }
          }
        }
        // write
        if (fds[i].revents & POLLOUT)
        {
          auto return_code = write(fds[i].fd, resp.c_str(), sizeof(resp));
          std::cout << "write on: " << i << ",return code:" << return_code;
          if (return_code == -1)
            errExit("write error");
          // 套接字写操作一般是可行的，所以不需要关心
          fds[i].events &= !(POLLOUT);
        }
      }
    }
  }
  return 0;
}