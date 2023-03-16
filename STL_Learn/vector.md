# vector
动态数组的实现，有序的集合
因为是有序的，所以在尾部和头部插入元素的效果较好
```c++
namespace std 
{   
    // allocator内存模型，可以自定义提供再哪里分配内存
    template<typename T, typename Allocator = allocator<T> >
    class vector;
}
```
## size, capacity,empty, max_size， reserve
size, empty,max_size都是vector中元素的个数有关
capacity >= size, capacity表示vector可以允许的容量，如果元素超过这个值，则重新分配内存
reserve()保留的意思，reserve(5) 如果小于capacity并不能缩小容量
std::vector<int> v; v.reserve(80); 将capacity的值设置为80，不超过这个容量，那么不会重新分配内存，因为分配内存是耗时间的
缩减容量符合当前元素个数v.shrink_to_fit();

## assign()
将新元素赋值给vector，旧元素全部移除
assign(n, elem)
assign(being, end)
assign({....})

## remove
// 删除容器中所有的val元素
coll.erase(remove(coll.being(), coll.end(), val), coll.end());

## 插入元素
insert都是插入value的拷贝，如果value为自定义类型，那么就会执行一次copy
push_back()
insert(pos, value)
insert(pos, n ,value)
insert(pos, begin, end)
insert(pos, {});
// 插入args为初值的元素，效果比insert高
emplace(pos, args...)
emplace_back(args...)
