# 迭代器的使用
```c++
// map的列表初始化
std::map<int, std::string> index_map{
    {1,"h"},{2,"j"},{3,"k"}
};

std::map<int, std::string>::iterator it = index_map.begin();
for(; it != index_map.end(); ++it)
{
    cout << "key:" <<(*it).first <<"value:"<< (*it).second << endl;
}
// for的范围循环
for(const auto& e: index_map)
{
    //
}
```

# std::for_each
标准库提供的函数，只需要提供开始和结束的迭代器，已经执行的函数或者仿函数
```c++
std::map<int, std::string> index_map{
    {1,"h"},{2,"j"},{3,"k"}
};

void print(std::map<int, std::string>::const_reference e)
{
    //
}

std::for_each(index_map.begin(), index_map.end(), print);


```