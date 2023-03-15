#include <iostream>
#include <map>
#include <set>
using namespace std;
int main() {
  multiset<string> cities{"GuangZhou", "ShenZhen", "HangZhou", "Foshan"};
  for (const auto &city : cities) {
    cout << city << " ";
  }
  cout << endl;
  cities.insert({"ZheJiang", "JiangXi", "ShenZhen"});
  for (const auto &city : cities) {
    cout << city << " ";
  }
  cout << endl;

  multimap<int, string> coll;
  // key必须为常量
  int a = 1;
  // 首先是根据key的值排序，其次如何key为变量，如果某个地方修改了，那么整个map就变了
  // 所以建议是常量
  coll = {{a, "tagged"},  {2, "a"},  {1, "this"},    {4, "off"},
          {6, "strings"}, {1, "is"}, {3, "multimap"}};
  for (auto elem : coll) {
    cout << elem.second << " ";
  }
  a = 2;
  cout << endl;
  // 这个元素会插值this is 之后
  coll.insert({1, "ang"});
  for (auto elem : coll) {
    cout << elem.second << " ";
  }
  cout << endl;
}