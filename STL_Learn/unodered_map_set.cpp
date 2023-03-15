#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;
int main() {
  unordered_multiset<string> cities{"GuangZhou", "ShenZhen", "HangZhou",
                                    "Foshan"};
  for (const auto &city : cities) {
    cout << city << " ";
  }
  cout << endl;
  cities.insert({"ZheJiang", "JiangXi", "ShenZhen"});
  for (const auto &city : cities) {
    cout << city << " ";
  }
  cout << endl;

  unordered_map<string, float> coll{{"tim", 9.9}, {"hang", 11.77}};
  for (std::pair<const string, float> &elem : coll) {
    elem.second *= elem.second;
  }

  for (const auto &elem : coll) {
    cout << elem.second << " ";
  }
  cout << endl;
  return 0;
}