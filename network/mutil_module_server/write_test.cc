#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h> // unix stdlib

int main()
{
  char* p1 = "this is a c test code";
  std::cout << "p1 length:" << strlen(p1) << std::endl;
  volatile int len = 0;
  int fp = open("test.txt", O_RDWR | O_CREAT);
  for (;;)
  {
    int n;
    // 写的操作，并不会一次性写入p1的所有数据，比如这次写了10个字节，
    // write需要手动去将位置指针移动
    if ((n = write(fp, p1 + len, (strlen(p1) - len))) == 0)
    {
      std::cout << "write datas: " << n << std::endl;
      break;
    }
    len += n;
  }
  return 0;
}