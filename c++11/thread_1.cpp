#include <iostream>
#include <thread>

int main() {
  auto func = []() {
    for (int i = 0; i < 10; ++i) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  };
  // detach相当于线程在后台运行，不阻塞主线程，所以这里就没有什么输出
  std::thread t(func);
  if (t.joinable()) {
    t.detach();
  }
  auto fun_k = [](int k) {
    for (int i = 0; i < k; ++i) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  };
  // 当主线程没有结束时，detach的线程也是可以输出的
  std::thread thread2(fun_k, 20);
  std::cout << "thread2_id: " << thread2.get_id() << std::endl;
  // join会阻塞主线程
  if (thread2.joinable()) {
    thread2.join();
  }
  return 0;
}