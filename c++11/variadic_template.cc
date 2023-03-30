#include <iostream>
using namespace std;
// 声明可变模板
template <long... nums> struct Multiply;
// 模板偏特化
template <long first, long... last> struct Multiply<first, last...> {
  static const long val = first * Multiply<last...>::val;
};
// 边界条件
template <> struct Multiply<> { static const long val = 1; };

int main() {
  cout << Multiply<1, 2, 3, 4>::val << endl;
  cout << Multiply<2, 3, 4, 5>::val << endl;

  return 0;
}