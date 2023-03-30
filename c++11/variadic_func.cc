#include <iostream>
#include <stdexcept>
using namespace std;

// 递归的出口而已
void Printf(const char *s) {
  while (*s) {
    if (*s == '%' && *(++s) != '%') {
      throw runtime_error("extra arguments provided to Printf");
    }
    cout << "*(s++): ";
    cout << *(s++);
  }
}

template <typename T, typename... Args>
void Printf(const char *s, T value, Args... args) {
  // *s = hello value = world
  while (*s) {
    if (*s == '%' && *(++s) != '%') {
      cout << value << endl;
      return Printf(++s, args...);
    }
    cout << *(s++) << ","; // h,e,l,l,0, ,
  }
  throw runtime_error("extra arguments provided to Printf");
}

int main() {
  Printf("hello %s\n", string("world"));
  return 0;
}