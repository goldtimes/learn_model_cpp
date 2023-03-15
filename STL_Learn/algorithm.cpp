#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int main() {
  vector<int> coll = {2, 5, 4, 1, 5, 3};
  // 返回的是迭代器的位置
  auto min_it = min_element(coll.cbegin(), coll.cend());
  cout << "min: " << *min_it << endl;
  auto max_it = max_element(coll.cbegin(), coll.cend());
  cout << "max: " << *max_it << endl;

  sort(coll.begin(), coll.end());
  auto find_3_it = find(coll.begin(), coll.end(), 3);
  reverse(find_3_it, coll.end());
  for (const auto &value : coll) {
    cout << value << " ";
  }
  cout << endl;

  auto find_1_it =
      find_if(coll.begin(), coll.end(), [](int i) { return i == 1 || i == 5; });

  cout << "find_1_it:" << *find_1_it << endl;

  vector<int> coll2{1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> coll3;

  // euqal处理多区间，逐一比较容器1和容器2的元素，比较的次数由容器1的元素决定，所以要确保容器2的数量大于或者等于容器1的元素
  equal(coll.begin(), coll.end(), coll2.begin());
  // copy必须保证coll3的容量够大可以存放coll2中的元素，否则会报错
  coll3.resize(coll2.size());
  copy(coll2.begin(), coll2.end(), coll3.begin());
  for (const auto &value : coll3) {
    cout << value << " ";
  }
  cout << endl;
  return 0;
}