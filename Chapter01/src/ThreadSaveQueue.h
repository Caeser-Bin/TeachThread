//
// Created by Caesar on 2025/11/13.
//

#ifndef TEACH_THREAD_THREAD_SAVE_QUEUE_H
#define TEACH_THREAD_THREAD_SAVE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSaveQueue {
public:
  /// 这段代码实现了一个线程安全的入队操作：
  /// 加锁保护：使用std::unique_lock自动获取互斥锁，保护共享队列
  /// 入队操作：将传入元素添加到队列中
  /// 解锁通知：手动释放锁后，通过条件变量唤醒等待的线程
  /// 主要功能是向线程安全队列中添加元素，并通知其他等待的线程。
  void push(T const& item) {
    std::unique_lock lock(mutex);
    queue.push(item);
    lock.unlock();
    condition.notify_one();
  }

  /// 这段代码实现了一个线程安全的出队操作：
  /// 使用unique_lock自动加锁保护共享队列
  /// 当队列为空时，通过条件变量condition.wait()阻塞等待
  /// 队列非空后取出队首元素并删除
  /// 解锁并返回取出的值
  /// 功能： 从线程安全队列中取出并返回队首元素，若队列为空则等待直到有元素可用。
  T pop() {
    std::unique_lock lock(mutex);
    while (queue.empty()) {
      condition.wait(lock);
    }
    T val = queue.front();
    queue.pop();
    lock.unlock();
    return val;
  }

  bool empty() {
    std::unique_lock lock(mutex);
    return queue.empty();
  }

private:
  std::mutex mutex;
  std::condition_variable condition;
  std::queue<T> queue;
};


#endif //TEACH_THREAD_THREAD_SAVE_QUEUE_H