# auto 类型推断
```c++
auto i = 5;
auto str = "name"; // const char*
auto sum(int a, int b)->int // 返回类型后置，用在函数模板中
{
    return a+b;
}
// auto b;
// b = 5; 编译失败
int b = 5;
auto* p_i = &b, m = 10; // auto推断为int类型
auto i = true ? 5 : 8.0; // 实则推导为double 
// 成员变量和成员静态变量
struct sometype
{
    static const auto i = 5; // 静态成员必须为const才支持auto
    // auto b = 5; 
};

// c++20中成立
void echo(auto name)
{
    cout << name << endl
}
```

# auto 推导规则
```c++

//1.0
const int i = 5;
auto j = i; // 按值初始化/拷贝的时候,会忽略cv限定符 --> int
auto &m = i; // 引用 const int,则推导为const int 
auto *k = &i; // 指针 指向const int ,则推导为const int
const auto n = j; // const 结合auto 
//2.0 使用auto声明变量初始化时，目标对象如果是引用，则引用属性会被忽略
int i = 5;
int &j = i;
auto m = j; // 因为j是引用，推导m时会忽略引用 m->int类型
//3.0 左值和右值的引用
int i = 5;
auto&& m = i; // i为左值，m的类型为int&, auto为int&，引用折叠
auto&& j = 5; // 5为右值，j的类型为int&& ->auto为int,
//4.0 使用auto声明变量，如果目标对象是一个数组或者函数，则auto会被推导为对应的指针类型
int i[5];
auto m = i; // auto为int*

int sum(int a, int b)
{
    return a+b;
}
auto j = sum; // auto-> int(*func)(int, int); 函数指针
```

# 合理使用auto
```c++
std::map<std::string, int> str2int;

for(std::map<std::string, int>::const_iterator it = str2int.cbegin(); it!=str2int.cend(); ++it);
for(auto it = str2int.cbegin(); it!=str2int.cend(); ++it);

for(std::pair<const std::string, int>& it, str2int);
for(auto& it, str2int);
// lambda

auto l = [](int a,int b)->int {return a+b;}

int sum(int a, int b){return a+b;}
auto f = std::bind(sum, 5, std::placeholder::_1);
```

# 返回类型的推导c++14
```c++
auto sum(int a, int b){return a+b;}
```

# lambda 中使用auto
```c++
auto l = [](auto a, auto b) {return a+b;}

// lambda返回引用类型
auto l = [](int &i)->auto& {return i;}
auto x = 5;
auto& x2 = l(x);
assert(&x1 == &x2);
```