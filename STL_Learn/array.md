# array
固定大小的数组容器
```c++
#include <array>

template<class T, size_T N>
class array;

std::array<int, 4> coll {};

std::array<int, 4> coll2;

coll2 = std::move(coll);

```
