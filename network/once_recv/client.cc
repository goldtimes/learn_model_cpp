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
  int err;
  long argp;

  char msg[] = "hello,server.I have received you message.";
  int sock_cli = socket(AF_INET, SOCK_STREAM, 0);

  SOCKADDR_IN server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("10.33.33.37");
  server_addr.sin_port = htons(8000);
  // 连接服务器
  int connect_result =
      connect(sock_cli, (SOCKADDR*)(&server_addr), sizeof(SOCKADDR));
  assert(connect_result >= 0);
  char recv_buff[BUFF_LEN];
  // 接受服务端的消息
  int recv_len;
  do
  {
    // recv有可能单次就收完了服务器发送的数据
    // 然后关闭socket,那么
    recv_len = recv(sock_cli, recv_buff, BUFF_LEN, 0);
    if (recv_len > 0)
    {
      std::cout << "来自服务器的消息长度:" << recv_len << std::endl;
      std::cout << recv_buff << std::endl;
    }
    else if (recv_len == 0)
    {
      std::cout << "对方关闭连接" << std::endl;
    }
    else
    {
      std::cout << "recv error" << std::endl;
      return 1;
    }
  } while (recv_len > 0);
  char send_buff[100];
  for (int i = 0; i < 5; ++i)
  {
    sprintf(send_buff, "NO.%d i'm the client. 1+1=2\n", i + 1);
    send(sock_cli, send_buff, strlen(send_buff) + 1, 0);
    memset(send_buff, 0, strlen(send_buff));
  }
  puts("sending data to server completed");
  close(sock_cli);
  return 0;
}