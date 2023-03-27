#pragma once

#include <iostream>

class Time {
public:
  Time() = default;
  ~Time() = default;
  Time(int hours, int minutes);
  void addMin(int m);
  void addHours(int h);
  void resetTime(int h = 0, int m = 0);
  // 重载+运算符
  Time operator+(const Time &other) const;
  // 重载-运算符
  Time operator-(const Time &other) const;
  // 重载*运算符 time * 3的形式
  Time operator*(double n) const;
  // 友元函数的方式重载*
  friend Time operator*(double m,
                        const Time &t); // 简单的话，可以用inline的方式 {}
  // 友元函数重载 << 运算符， 返回ostream对象，代表着可以用cout << "hour: " <<
  // time << endl 的流形式。
  friend std::ostream &operator<<(std::ostream &os, const Time &t);

private:
  int hours_;
  int minutes_;
};