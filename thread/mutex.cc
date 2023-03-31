#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

std::mutex mux;

int main(int argc, char **argv) {

  auto func = [](int k) -> void {
    mux.lock();
    for (int i = 0; i < k; ++i) {
      cout << i << " ";
    }
    cout << endl;
    mux.unlock();
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