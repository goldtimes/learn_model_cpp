#include <functional>
#include <iostream>

//定义一个结构体
struct Foo {
  Foo(int num) : num_(num) {}
  void print_add(int i) const {
    std::cout << "num_+i:" << num_ + i << std::endl;
  }
  int num_;
};

void print_num(int i) { std::cout << "num: " << i << std::endl; }
// 仿函数
struct PrintNum {
  void operator()(int i) { std::cout << "i: " << i << std::endl; }
};

int main() {
  // 定义function包装器，接受返回类型为void,参数为int类型的
  std::function<void(int)> f_display = print_num;
  // 通过包装器调用函数
  f_display(-9);
  // lambda可以直接捕获全局变量
  std::function<void()> f_lambda = []() -> void { print_num(-10); };
  f_lambda();

  auto f = std::bind(print_num, -11);
  f();
  // 接受bind的返回类型，function<>模板实例化中不需要和print_num函数的参数类型一致
  std::function<void()> f_display_12 = std::bind(print_num, 12);
  // f_display_12(); will get error, f_display_12 is void(int)类型
  f_display_12();
  // 实例化Foo类
  const Foo foo(12345);

  //   std::function<void(int)> f_add_display = &Foo::print_add;
  // 绑定类成员函数的时候，在模板实例化时指定类的类型
  std::function<void(const Foo &, int)> f_add_display = &Foo::print_add;
  f_add_display(foo, 1);
  f_add_display(123456, 1);
  // _1占位符表示f_1调用的时候传递过来的参数
  auto f_1 = std::bind(&Foo::print_add, foo, std::placeholders::_1);
  // 必须要传递参数，否则报错
  f_1(0);

  std::function<void(int)> f_add_display_3 =
      std::bind(&Foo::print_add, foo, std::placeholders::_1);
  f_add_display_3(3);

  return 0;
}