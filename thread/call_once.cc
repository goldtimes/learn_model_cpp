#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

std::once_flag once;

// std::call_once 配合 once_flag使用
void callOnce() {
  std::call_once(once, [] { cout << "callonce" << endl; });
}

int main(int argc, char **argv) {

  std::thread threads[3];
  for (int i = 0; i < 3; ++i) {
    threads[i] = thread(callOnce);
  }
  for (std::thread &t : threads) {
    t.join();
  }

  return 0;
}