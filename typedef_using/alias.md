# 类型别名
```c++
// 定义map的迭代器
typedef std::map<int, std::string>::const_iterator map_const_it;
map_const_it it;

// 函数指针 using 比 typedef定义的方式更加清晰
typedef void(*func)(int,int);
using func2 = void(*)(int, int);
```

# 别名模板c++
```c++
template<class T>
using int_map = std::map<int, T>;

int_map<std::string> person;
person[28] = "hang";

```