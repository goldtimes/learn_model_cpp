#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
  Person() = default;
  Person(string name) : name_(name) { cout << "ctor" << endl; }
  Person(const Person &other) {
    name_ = other.name_;
    cout << "copyctor" << endl;
  }
  ~Person() = default;

private:
  string name_;
};

int main() {
  vector<Person> persons;
  persons.reserve(5);

  Person hang("hang");
  Person jun("jun");
  Person yuan("yuan");

  // copyctor
  // copyctor
  persons.push_back(hang);
  persons.push_back(jun); // 会调用一次copy构造函数
  //   persons.push_back("li"); 没有构造功能
  persons.emplace_back("yuan"); // 添加了构造功能

  cout << "max_size: " << persons.max_size() << endl;
  cout << "size: " << persons.size() << endl;
  cout << "capacity: " << persons.capacity() << endl;

  persons.shrink_to_fit();

  cout << "max_size: " << persons.max_size() << endl;
  cout << "size: " << persons.size() << endl;
  cout << "capacity: " << persons.capacity() << endl;

  return 0;
}