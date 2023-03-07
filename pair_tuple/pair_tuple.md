# 返回多个值
```c++
std::tuple<int, int> func()
{
    return std::make_tuple(11,7);
}

int main()
{
    int x, y;
    std::tie(x,y) = func();

    auto[x,y] = func(); // C++17中的结构化绑定
}
```

# 结构化绑定
```c++
struct BindTest
{
    int age = 28;
    std::string name = "lihang";
};

BindTest bt;
auto [x,y] = bt;
```