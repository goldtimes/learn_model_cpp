#include <arpa/inet.h>
#include <cstdio>
#include <iostream>

int main(int argc, char **argv) {
  struct in_addr address;
  // inet_addr("ip")->变换成二进制的ip地址
  in_addr_t dwIp = inet_addr("192.168.0.1");
  address.s_addr = dwIp;
  printf("address.s_addr=0x%x\n", address.s_addr); // 小端
  // inet_ntoa(in_addr struct)->网络ip
  printf("real_ip=%s\n", inet_ntoa(address));
  return 0;
}