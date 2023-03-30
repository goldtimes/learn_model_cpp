#include <iostream>

using namespace std;
// void runCode(int a) { cout << "值传递调用" << endl; }
void runCode(int &a) { cout << "左值引用传递调用" << endl; }
void runCode(int &&a) { cout << "右值引用调用" << endl; }
void runCode(const int &a) { cout << "常量左值引用调用" << endl; }
void runCode(const int &&a) { cout << "常量右值引用调用" << endl; }

template <typename T> void perfectForward(T &&t) { runCode(forward<T>(t)); }

int main() {
  int a = 0;
  int b = 0;
  const int c = 1;
  const int d = 1;
  perfectForward(a);            // 传入左值
  perfectForward(std::move(b)); // 传入右值
  perfectForward(c);            // 传入常量的左值
  perfectForward(std::move(d)); // 传入常量的右值

  return 0;
}