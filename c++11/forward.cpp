#include <iostream>

using namespace std;

void printV(int &v) { cout << "lvalue" << endl; }
void printV(int &&v) { cout << "rvalue" << endl; }

// 完美转发，定义一个模板函数，接受任意实参
template <typename T> void Test(T &&t) {
  printV(t);
  printV(std::forward<T>(t));
}

int main() {
  Test(1); // lvalue rvalue
  int a = 1;
  Test(a);                       // l,l
  Test(std::move(a));            // l,v
  Test(std::forward<int &>(a));  // l, l
  Test(std::forward<int &&>(a)); // l, v
  return 0;
}