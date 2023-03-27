#include "time.hh"

Time::Time(int hours, int minutes) : hours_(hours), minutes_(minutes) {}

void Time::addHours(int h) {
  hours_ += h;
  hours_ %= 24;
}

void Time::addMin(int m) {
  minutes_ += m;
  hours_ += minutes_ / 60;
  minutes_ %= 60;
}

void Time::resetTime(int h, int m) {
  hours_ = h;
  minutes_ = m;
}

Time Time::operator+(const Time &other) const {
  Time sum;
  sum.minutes_ = this->minutes_ + other.minutes_;
  sum.hours_ = this->hours_ + other.hours_ + sum.minutes_ / 60;
  sum.minutes_ %= 60;
  return sum;
}
Time Time::operator-(const Time &other) const {
  Time diff;
  int total_this = this->minutes_ + 60 * this->hours_;
  int total_other = other.minutes_ + 60 * other.hours_;
  diff.minutes_ = (total_this - total_other) % 60;
  diff.hours_ = (total_this - total_other) / 60;
  return diff;
}
Time Time::operator*(double n) const {
  Time result;
  long total_m = this->hours_ * n * 60 + this->minutes_ * n;
  result.minutes_ = total_m % 60;
  result.hours_ = total_m / 60;
  return result;
}
// 友元函数不是类成员，所以不能用Time::
Time operator*(double n, const Time &t) {
  return t * n;
  // 实际调用的是类成员的重载*方法
}

std::ostream &operator<<(std::ostream &os, const Time &t) {
  os << t.hours_ << " hours, " << t.minutes_ << " minutes.";
  return os;
}

int main() {
  using std::cout;
  using std::endl;

  Time aida(3, 35);
  Time tosca(2, 48);
  Time temp;
  cout << "Aida and Tosca: \n";
  cout << aida << "; " << tosca << endl;
  temp = aida + tosca;
  cout << "aida+tosca:" << temp << endl;
  temp = aida * 1.2;
  cout << "aida*1.2:" << temp << endl;
  cout << "10 * aida: " << 10 * aida << endl;

  return 0;
}