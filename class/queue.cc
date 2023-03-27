#include "queue.hh"

Queue::Queue(int size = Q_SIZE) : items(0) { front = rear = nullptr; }

// 队列尾部插入对象
bool Queue::enqueu(const Item &item) {
  if (full()) {
    return false;
  }
  Node *node = new Node; // create 新的node
  node->item = item;
  node->next = nullptr;
  ++items;
  if (front == nullptr) // queue is empty, 那么front和rear都等于node
  {
    front = node;
  } else {
    rear->next = node;
  }
  rear = node;
  return true;
}

// const 不能对成员变量修改？
bool Queue::dequeue(Item &item) {
  if (empty()) {
    return false;
  }

  item = front->item;
  --items;
  // 记录下当前的头指针
  Node *temp = front;
  front = front->next;
  delete temp;

  if (items == 0) {
    rear = nullptr;
  }
  return true;
}

bool Queue::empty() const { return items == 0; }

// 删除链表
Queue::~Queue() {
  Node *temp = nullptr;
  while (front != rear) {
    temp = front;
    front = front->next;
    delete temp;
  }
}

bool Queue::full() const { return items == q_size; }