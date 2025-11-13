//
// Created by Caesar on 2025/11/13.
//

#ifndef TEACH_THREAD_THREAD_SAVE_QUEUE_H
#define TEACH_THREAD_THREAD_SAVE_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>


template <typename T>
class ThreadSaveQueue {
public:
  void push(T const& item) {
    std::unique_lock lock(mutex);
    queue.push(item);
    lock.unlock();
    condition.notify_one();
  }

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