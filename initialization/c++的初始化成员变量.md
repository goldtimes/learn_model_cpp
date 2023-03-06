# 非静态成员的初始化
## 初始化列表
构造函数多的话，很冗余
```c++
class X 
{
    public:
        X() : a_(0), b_(0.0),c_("hello"){}
        x(int a): a_(a), b_(0.0), c_("hello"){}
    private:
        int a_;
        double b_;
        string c_;
};
```
## 对成员变量使用=,{}初始化
```c++
class X {
public:
  X() {}
  X(int a) : a_(a) {}
  X(double b) : b_(b) {}
  X(const std::string &c) : c_(c) {} // 初始化列表对成员的初始化优先于默认的声明{}初始化

private:
  int a_ = 0;
  double b_{ 0. };
  std::string c_{ "hello world" };
//   auto d = 8; error
};
```

# 位域的初始化