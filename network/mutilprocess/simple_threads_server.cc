#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

void* client_process(void* arg);

int main(int argc, char** argv)
{
  int sockfd = 0, connected_sockfd = 0, err_flag = 0;
  char on = 1;
  struct sockaddr_in server_addr;
  unsigned short port = 8000;
  pthread_t thread_id;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    std::cerr << "create socket error!" << std::endl;
    exit(-1);
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(port);
  server_addr.sin_family = AF_INET;
  // 端口复用
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  // bind
  err_flag =
      bind(sockfd, (struct sockaddr*)(&server_addr), sizeof(server_addr));
  if (err_flag != 0)
  {
    std::cerr << "bind error!" << std::endl;
    close(sockfd);
    exit(-1);
  }
  // listen
  err_flag = listen(sockfd, 5);
  if (err_flag != 0)
  {
    std::cerr << "listen error" << std::endl;
    close(sockfd);
    exit(-1);
  }
  struct sockaddr_in client_addr;
  unsigned int addr_len = sizeof(client_addr);
  char client_ip[INET_ADDRSTRLEN] = "";
  while (1)
  {
    memset(&client_addr, 0, addr_len);
    int connected_sockfd =
        accept(sockfd, (struct sockaddr*)(&client_addr), &addr_len);
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    std::cout << "client ip:" << client_ip
              << ",port:" << ntohs(client_addr.sin_port) << std::endl;
    pthread_create(
        &thread_id, nullptr, client_process, (void*)connected_sockfd);
    pthread_detach(thread_id);
  }
  close(sockfd);
  return 0;
}
void* client_process(void* arg)
{
  int recv_len = 0;
  char recv_buf[1024] = "";
  // 先转换为64位的long
  long temp = (long)arg;
  int connected_sock = (int)temp;
  while (recv_len = recv(connected_sock, recv_buf, sizeof(recv_buf), 0) > 0)
  {
    std::cout << "recv data:" << recv_buf << std::endl;
    send(connected_sock, recv_buf, sizeof(recv_buf), 0);
  }
  std::cout << "client close." << std::endl;
  close(connected_sock);
  return nullptr;
}
