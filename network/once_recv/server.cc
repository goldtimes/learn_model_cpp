#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <cstdio>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <assert.h>

constexpr int BUFF_LEN = 300;

using SOCKADDR_IN = struct sockaddr_in;
using SOCKADDR = struct sockaddr;

int main(int argc, char** argv)
{
  int err, recv_data_len;
  char on = 1;
  int sock_srv = socket(AF_INET, SOCK_STREAM, 0);
  assert(sock_srv >= 0);
  // reuse
  setsockopt(sock_srv, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  SOCKADDR_IN bind_addr;
  bind_addr.sin_addr.s_addr = inet_addr("10.33.33.37");
  bind_addr.sin_port = htons(8000);
  bind_addr.sin_family = AF_INET;
  auto bind_result = bind(sock_srv, (SOCKADDR*)(&bind_addr), sizeof(SOCKADDR));
  listen(sock_srv, 5);
  SOCKADDR_IN client_sock;
  int len = sizeof(SOCKADDR);
  while (true)
  {
    std::cout << "等待客户端的连接" << std::endl;
    int connected_sock =
        accept(sock_srv, (SOCKADDR*)(&client_sock), (socklen_t*)(&len));
    char send_buff[100] = "";
    for (int i = 0; i < 5; i++)
    {
      sprintf(
          send_buff,
          "NO.%d,welcome to server. 1+1=?(client ip: %s)",
          i + 1,
          inet_ntoa(client_sock.sin_addr));
      send(connected_sock, send_buff, strlen(send_buff), 0);
      memset(send_buff, 0, strlen(send_buff));
    }
    // 数据发送完毕之后
    auto send_flag = shutdown(connected_sock, SHUT_WR);
    if (send_flag == -1)
    {
      std::cout << "关闭已连接的socket,error." << std::endl;
      close(connected_sock);
      return -1;
    }
    // 持续接受客户端的信息
    char recv_buff[BUFF_LEN];
    do
    {
      recv_data_len = recv(connected_sock, recv_buff, BUFF_LEN, 0);
      if (recv_data_len > 0)
      {
        std::cout << "recv_data_len: " << recv_data_len << std::endl;
        std::cout << recv_buff << std::endl;
      }
      else if (recv_data_len == 0)
      {
        std::cout << "客户端关闭连接" << std::endl;
      }
      else
      {
        std::cout << "recv error" << std::endl;
        close(connected_sock);
        return 1;
      }
    } while (recv_data_len > 0);
    close(connected_sock);
    puts("continue monitoring?(y/n)");
    char ch = getchar();
    if (ch != 'y')
      break;
  }
  close(sock_srv);
  return 0;
}