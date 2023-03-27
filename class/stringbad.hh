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

public:
  StringBad();
  StringBad(const char *s);
  ~StringBad();

  friend std::ostream &operator<<(std::ostream &os, const StringBad &str);
};
// 不能在类中初始化静态类成员，除非静态类成员是const int\const enum
int StringBad::num_string = 0;