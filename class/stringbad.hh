/**
 * @file stringbad.hh
 * @author your name (you@domain.com)
 * @brief  类和动态内存分配，先展示一个设计比较糟糕的类
 * @version 0.1
 * @date 2023-03-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <iostream>

class StringBad {
private:
  char *str;
  int len;
  static int num_string; // 静态类成员，需要在类外进行初始化

private:
  int length() const { return len; }
  // 重载输出函数
  friend std::ostream &operator<<(std::ostream &os, const StringBad &str);
  // < , > == 比较符号
  friend bool operator<(const StringBad &s1, const StringBad &s2);
  friend bool operator>(const StringBad &s1, const StringBad &s2);
  friend bool operator==(const StringBad &s1, const StringBad &s2);
  friend std::istream &operator>>(std::istream &is, StringBad &s);
  // []下标访问
  char &operator[](int i);
  const char &operator[](int i) const;

public:
  StringBad();
  StringBad(const char *s);
  ~StringBad();
  // 这里没有定义复制构造函数将造成两个问题：
  // 1.
  // 赋值StringBad对象时，将调用编译器提供的拷贝构造函数，但是默认使用的是浅拷贝
  // 2. 如果对象中包含了指针，那么浅拷贝会使得两个指针都指向同一块内存区域，当
  //    前一个对象被回收时，释放了该指针，拷贝的对象被回收时，也释放了指针。相当于对同一个内存进行两次释放
  StringBad(const StringBad &other); // 执行深拷贝
  // =赋值构造函数,同样执行深拷贝
  StringBad &operator=(const StringBad &other);
  // 静态类成员函数，因为没有*this对象，所以不可以访问非静态变量len,str
  // 且在类中声明/定义，也可以在外面独立定义
  static int HowMany();
};
// 不能在类中初始化静态类成员，除非静态类成员是const int\const enum
int StringBad::num_string = 0;

int StringBad::HowMany() { return num_string; }