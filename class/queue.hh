#pragma once
#include <random>
class Customer {
private:
  long arrive_time_;
  int process_time_;

public:
  Customer() { arrive_time_ = process_time_ = 0; }
  // 产生了 1~3之间的随机值
  void set(long when) { process_time_ = std::rand() % 3 + 1; }
  long when() const { return arrive_time_; }
  int process_time() const { return process_time_; }
};

using Item = Customer;

// 接口
class Queue {
private:
  struct Node {
    Item item;
    struct Node *next;
  };
  enum { Q_SIZE = 10 };

private:
  Node *front;
  Node *rear;
  int items;
  const int q_size =
      Q_SIZE; // 对于const变量的初始化，也可以放在初始化列表中，引用变量需要放在初始化列表

public:
  Queue(int size = Q_SIZE);
  ~Queue();
  // 禁止拷贝构造和赋值构造函数
  Queue(const Queue &other) = delete;
  Queue &operator=(const Queue &other) = delete;
  bool empty() const;
  bool full() const;
  int size();
  bool dequeue(Item &item);      // remove item from front
  bool enqueu(const Item &item); // 队列尾部入队
};