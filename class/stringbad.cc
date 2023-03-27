#include "stringbad.hh"
#include <cstring>

using std::cout;

void pass_by_ref(StringBad &); // 引用
void pass_by_value(StringBad); // 值传递

// 构造函数，传入c风格的字符串
StringBad::StringBad(const char *s) {
  len = std::strlen(s);
  str = new char[len + 1]; // 分配内存;
  std::strcpy(str, s);     // 初始化
  // str = s 我们知道字符串变量只保存了字符串的地址
  // str=s的方式相当于直接拷贝了地址
  num_string++;
  std::cout << num_string << ": \" " << str << " \" obeject created \n ";
}

StringBad::StringBad() {
  //   len = 4;
  //   str = new char[4];
  //   std::strcpy(str, "C++");
  //   std::cout << num_string << ": \" " << str << " \" obeject created \n ";

  len = 0;
  str =
      new char[1]; // 不要str = new char, 因为delete str 和 delete [] str不一样
  str = nullptr;
}

// 对含有指针类的对象进行深拷贝，防止两个对象的指针指向同一个区域
// 在释放的时候造成二次释放
StringBad::StringBad(const StringBad &other) {
  num_string++;
  this->len = other.len;
  str = new char[len + 1];
  std::strcpy(str, other.str);
  std::cout << num_string << ": \" " << str << " \" obeject created \n ";
}

bool operator<(const StringBad &s1, const StringBad &s2) {
  if (std::strcmp(s1.str, s2.str) < 0)
    return true;
  return false;
}
// s1 > s2
bool operator>(const StringBad &s1, const StringBad &s2) { return s2 < s1; }
bool operator==(const StringBad &s1, const StringBad &s2) {
  return std::strcmp(s1.str, s2.str) == 0;
}

char &StringBad::operator[](int i) { return str[i]; }

const char &StringBad::operator[](int i) const { return str[i]; }

StringBad &StringBad::operator=(const StringBad &other) {
  if (&other == this) // 地址相同，退出。防止释放内存操作会删除对象的数据
  {
    return *this;
  }
  delete[] str;
  str = new char[other.len + 1];
  std::strcpy(str, other.str);
  return *this;
}

StringBad::~StringBad() {
  //   std::cout << "\"" << str << "\"object delete";
  //   --num_string;
  //   std::cout << num_string << "left\n";
  delete[] str;
}

std::ostream &operator<<(std::ostream &os, const StringBad &s) {
  os << s.str;
  return os;
}
// 这里有可能使用了默认的移动构造函数
void pass_by_ref(StringBad &s) {
  cout << "引用传值\n";
  cout << "\"" << s << "\"\n";
}
void pass_by_value(StringBad s) {
  cout << "拷贝传值\n";
  cout << "\"" << s << "\"\n";
}

int main() {
  using std::endl;
  {
    StringBad headline1("Celery");
    StringBad headline2("Lettuce");
    StringBad sport("Spinach");
    cout << "headline1:" << headline1 << endl;
    cout << "headline2:" << headline2 << endl;
    cout << "sport: " << sport << endl;
    pass_by_ref(headline1);
    cout << "headline1:" << headline1 << endl;
    pass_by_value(headline2);
    cout << "headline2:" << headline2 << endl;
    cout << "赋值: \n";
    StringBad sailor = sport; // 调用复制构造函数
    cout << "sailor: " << sailor << endl;
    StringBad knot;
    knot = headline1;
    int count = StringBad::HowMany();
    cout << "cout:" << count << endl;
  }
  return 0;
}