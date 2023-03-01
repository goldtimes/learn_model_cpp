# inline namespace
```c++
namespace Parent
{
    namespace Child
    {
        void print_name() {}
    }

    inline namespace Child2
    {
        void print_name() {}
    }
}

Parent::Child::print_name();
Parent::print_name();  
```
内联命名空间的使用，对原有代码升级的时候可以用上这样的inline namespace, 由调用的方式可以看出，inline namespace 在namespace 空间中只能有一个，否则会有二义性

# 嵌套命名空间的简化
```c++
namespace A::B::C{
    int foo(){return 5;}
}
```
