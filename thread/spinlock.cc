#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>
using namespace std;

std::atomic_flag lock = ATOMIC_FLAG_INIT; // set flat is true

void f(int n)
{
    // test_and_set尝试获得锁,main函数中设置为true了，所以这个线程一直循环自旋
    while( lock.test_and_set(std::memory_order_acquire))
    {
        cout << "waiting from thread id: " << n << endl;
        cout << "thread id: " << n << "start working." << endl;
    }
}
// 当这个线程运行的时候，将lock设置为false,thread1的自旋结束，执行循环后面的代码
void g(int n)
{
    cout << "thread " << n << "is going start." << endl;
    lock.clear(); // atomic_flag set false;
    cout << "thread " << n << "start working." << endl; 
}
int main()
{
    lock.test_and_set();
    thread thread1(f, 1);
    thread thread2(g, 2);
    thread1.join();
    usleep(100);
    thread2.join();

    return 0;
}