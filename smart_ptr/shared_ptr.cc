#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main() {
  // shared_ptr的初始化，调用单个参数的构造函数，传入指针
  // 自定义deletr,通过传入一个lambda函数，自定义析构函数
  shared_ptr<string> p_nico(new string("nico"), [](string *p) {
    cout << "delete nico" << endl;
    delete p;
  });
  // 用列表初始化的方式
  shared_ptr<string> p_jutta{new string("p_jutta")};
  // make_shared方式构造
  shared_ptr<string> p_hang = make_shared<string>("hang");
  // 声明，后通过reset赋值新的指针
  shared_ptr<string> p_str;
  p_str.reset(new string("str"));
  // 重载了->运算符，实则访问了shared_ptr中的指针对象str，并调用replace方法
  p_str->replace(0, 1, "J");
  cout << "str: " << *p_str << endl;
  vector<shared_ptr<string>> whoMadeCoffee;
  whoMadeCoffee.push_back(p_jutta);
  whoMadeCoffee.push_back(p_jutta);
  whoMadeCoffee.push_back(p_nico);
  whoMadeCoffee.push_back(p_jutta);
  whoMadeCoffee.push_back(p_nico);
  // p_jutta 开始定义的一次和push_back3次 总共4次
  cout << "use_cout: " << whoMadeCoffee[0].use_count() << endl;
  // p_nico 开始定义的一次和push_back2次 总共3次
  cout << "use_cout: " << whoMadeCoffee[2].use_count() << endl;

  whoMadeCoffee.resize(2);
  return 0;
}