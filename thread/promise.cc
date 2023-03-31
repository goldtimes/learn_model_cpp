#include <functional>
#include <future>
#include <iostream>
#include <thread>

void func(std::future<int> &f) {
  int result = f.get();
  std::cout << "get future: " << result << std::endl;
  result /= 2;
  std::cout << "value: " << result << std::endl;
}

int add(int n) { return n + 1; }
int main() {
  std::promise<int> prom;
  std::future<int> f = prom.get_future();
  std::thread t(func, std::ref(f));
  prom.set_value(10);
  t.join();

  std::packaged_task<int(int)> task(add);
  std::future<int> fut = task.get_future();
  //   这里会被阻塞，如果直接调用get函数
  //   std::cout << "fut.get(): " << fut.get() << std::endl;
  std::thread(std::move(task), 5).detach();
  std::cout << "result: " << fut.get() << std::endl;
  return 0;
}