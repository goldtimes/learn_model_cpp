#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
int main() {
  // launch async 代表立刻创建线程执行
  std::future<int> f = std::async(std::launch::async, []() {
    //模拟耗时操作
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 8;
  });

  std::future<void> f2 = std::async(std::launch::async, []() {
    //模拟耗时操作
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    // return 8;
    std::cout << "waiting" << std::endl;
  });
  // 等待3秒之后输出
  std::cout << f.get() << std::endl;
  f2.wait();

  return 0;
}