#pragma once

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
  bool empty();
  bool full();
  int size();
  bool dequeue(Item &item);      // remove item from front
  bool enqueu(const Item &item); // 队列尾部入队
};