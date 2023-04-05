/**
 * 主机字节序测试
 */
#include <iostream>

int main(int argc, char** argv)
{
  int num = 0x123456789;
  char* p_addr = (char*)&num;

  if (*p_addr == 0x12)
    std::cout << "大端模式" << std::endl;
  else
    std::cout << "小端模式" << std::endl;

  return 0;
}