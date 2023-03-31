#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

std::timed_mutex time_mux;

int main(int argc, char **argv) {

  auto func = [](int k) -> void {
    time_mux.try_lock_for(std::chrono::milliseconds(10000));
    for (int i = 0; i < k; ++i) {
      cout << i << " ";
    }
    cout << endl;
    time_mux.unlock();
  };

  std::thread threads[3];
  for (int i = 0; i < 3; ++i) {
    threads[i] = std::thread(func, 20);
  }
  for (std::thread &t : threads) {
    t.join();
  }

  return 0;
}