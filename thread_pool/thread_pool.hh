#pragma once

#include <deque>
#include <vector>
#include "nocopyable.hh"
#include <string>
#include <functional>
#include <mutex>
#include <pthread.h>

namespace lihang
{
  class ThreadPool : public nocopyable
  {
  public:
    // 函数对象，线程执行的任务
    using Task = std::function<void()>;
    explicit ThreadPool(const std::string& name = std::string("ThreadPool"));
    ~ThreadPool();

    void setMaxQueueSize(int maxSize) { max_queue_size_ = maxSize; }
    void setThreadInitCallback(const Task& cb) { thread_init_callback_ = cb; }
    void start(int numThreads);
    void stop();

    const std::string& getName() const { return name_; }
    size_t getQueueSize() const;
    void run(Task f);

  private:
    size_t max_queue_size_;
    std::string name_;
    // 使用了clang 的线程安全注解，可以编译时候检查
    // std::deque<Task> queue_  GUARDED_BY();
    std::deque<Task> queue_;
    // threads vector;
    Task thread_init_callback_;
    bool running_;
    bool isFull() const;
    void runInThread();
    // 返回任务的函数
    Task take();
  };
} // namespace lihang