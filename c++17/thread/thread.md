# shared_mutex
读写锁c++17引入,也叫做共享-独占锁。
* 当读写锁以只读的方式加锁，这个锁是共享的
* 当以写的模式锁住时，它是独占模式的
* 通常配合 std::shared_lock 和 std::unique_lock一起实现共享和独占的使用
* 比互斥锁具有更高的并发性，想象一个场景: 有多个同学查询成绩，如果使用
  互斥锁，每次的开销0.5秒，那么20个同学查询就需要10秒。而使用读写锁，锁的开销更大，
  那么查询一次需要0.8s。那么因为只读的情况下，20个同学可以同事访问只需要1秒左右。这样的场景
  下，并发的效率高很多。