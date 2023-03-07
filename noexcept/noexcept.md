# noexcept 即使说明符又是运算符
## 说明符
该说明符只是作出承诺，编译器对函数优化，如果函数中发生了异常则结束
```c++
struct X{
    int f() const  noexcept
    {
        return 58
    }
    void g() noexcept
    {

    }
};

int foo() noexcept
{

}
```

## 运算符 noexcept(表达式值为true/false)
运用在大量的函数模板中
下面这个函数是完成复制的功能，当T是自定义的类型时，如果复制出现问题，我们希望的是程序抛出异常，结束程序
但是如果T是基础类型，那么我们希望是不抛出异常，noexcept(std::is_fundamental<T>::value) 就是对T的类型判断
如果为基础类型，表达式为true,否则为false.
```c++
template<class T>
T copy(const T& other) noexcept(std::is_fundamental<T>::value)
{

}
// 最右边的noexcept是运算符，判断T(o)是否可抛出异常
template<class T>
T copy(const T& other) noexcept(noexcept(T(o)))
{

}
```

## 宏定义打印的技巧
```c++
#define PRINT_NOEXCEPT(X) \ 
    std::cout << #x << "=="<<x << std::endl
```
