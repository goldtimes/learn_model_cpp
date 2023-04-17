#include <sys/types.h>
#include <event2/event-config.h>
#include <stdio.h>
#include <event.h>
#include <iostream>

struct event ev;
struct timeval tv;

void time_callback(int fd, short event, void* argc)
{
  std::cout << "timer wakeup\n" << std::endl;
  event_add(&ev, &tv);
}

int main()
{
  // 初始化libevent库相当于初始化Reactor实例
  // 初始化Reactor就可以注册事件了
  struct event_base* base = event_init();
  tv.tv_usec = 0;
  tv.tv_sec = 10;
  // 初始化事件， 设置了回调函数time_callback，和关注的事件
  // evtimer_set(&ev, -1, 0, time_callback, nullptr). -1 为文件描述符,0为事件
  // 这里这是简单做一个定时的函数，所以文件描述符和事件都是不需要设置
  // 这里相当于Reactor的event handler
  evtimer_set(&ev, time_callback, nullptr);
  // 设置event从属的event_base
  event_base_set(base, &ev);
  // 添加事件  Reactor::register_handler()函数注册事件
  event_add(&ev, &tv);
  // 进入循环，等待事件就绪
  event_base_dispatch(base);
}
