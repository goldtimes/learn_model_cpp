#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <string>
using namespace std;

template <class T>
void PRINT_ELEM(const T &container, const string &PROMOT = "") {
  cout << PROMOT;
  for (const auto &elem : container) {
    cout << elem << " ";
  }
  cout << endl;
}

int main() {
  array<int, 10> coll{11, 22, 33, 44};

  PRINT_ELEM(coll);
  coll.back() = 55;
  coll[coll.size() - 2] = 66;
  PRINT_ELEM(coll);

  cout << "sum: " << accumulate(coll.cbegin(), coll.cend(), 2) << endl;

  transform(coll.begin(), coll.end(), coll.begin(), negate<int>());
  PRINT_ELEM(coll);

  return 0;
}