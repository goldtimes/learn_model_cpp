#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  pid_t pid;
  pid = fork();
  // 调用fork()之后，两个进程在执行这些代码块，所以第一次进入父进程的代码块，输出PID:9509，
  // 返回值PID:9510为子进程。
  // 然后子进程执行该代码块。pid就为0，getPid()=9510。和上面的子进程pid对上了。
  // 进程的执行是随机的，不一定
  if (pid == -1)
  {
    std::cerr << "创建子进程失败" << std::endl;
    return -1;
  }
  else if (pid == 0)
  {
    std::cout << "该代码区为子进程代码区" << std::endl;
    std::cout << "pid:" << pid << "My Pid:" << getpid() << std::endl;
  }
  else // 返回值>0，表示该部分是父进程的代码。返回值是子进程的pid
  {
    std::cout << "该代码区为父进程代码区" << std::endl;
    std::cout << "pid:" << pid << "parent pid:" << getpid() << std::endl;
  }
  return 0;
}