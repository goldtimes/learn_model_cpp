#include <chrono>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

std::mutex mutex;

class ThreadSafeCounter {
public:
  ThreadSafeCounter() = default;
  ~ThreadSafeCounter() = default;

private:
  mutable std::shared_mutex mutex_; // 这里一定要mutable
  unsigned int value_;

public:
  unsigned int getValue() const {
    // 读写锁-读锁的共享模式
    std::shared_lock<std::shared_mutex> lck(
        mutex_); // 调用mutex_.lock_shared();
    return value_;
  }

  unsigned int increment() {
    // 读写锁-写锁的独栈模式
    std::unique_lock<std::shared_mutex> un_lck(mutex_); // mutex_.lock()
    ++value_;
    return value_;
  }

  void reset() {
    std::unique_lock<std::shared_mutex> un_lock(mutex_);
    value_ = 0;
  }
};

ThreadSafeCounter counter;

void reader(int i) {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::unique_lock<std::mutex> unlock(mutex); // 这里的锁是保证cout的有序性
    std::cout << "reader #" << i << "getValue:" << counter.getValue()
              << std::endl;
  }
}

void writer(int i) {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::unique_lock<std::mutex> unlock(mutex); // 这里的锁是保证cout的有序性
    std::cout << "writer #" << i << "write value:" << counter.increment()
              << std::endl;
  }
}

int main() {
  std::thread rth[10];
  std::thread wth[10];
  for (int i = 0; i < 10; ++i) {
    rth[i] = std::thread(reader, i + 1);
  }
  for (int i = 0; i < 10; ++i) {
    wth[i] = std::thread(writer, i + 1);
  }

  for (int i = 0; i < 10; ++i) {
    rth[i].join();
  }

  for (int i = 0; i < 10; ++i) {
    wth[i].join();
  }

  return 0;
}