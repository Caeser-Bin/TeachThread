//
// Created by Caesar on 2025/11/13.
//

#include "ThreadSaveQueue.h"
#include <iostream>

struct Item {
  explicit Item(const char id) : c(id) {}
  char c;
};

template <typename T>
struct Producer {
  void operator()() {
    for (int i = 0; i < 10; i++) {
      T item('A' + static_cast<char>(i));
      queue.push(item);
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
  }

  ThreadSaveQueue<T>& queue;
  std::chrono::milliseconds delay;

  Producer(ThreadSaveQueue<T>& queue, const int i)
    : queue(queue),
      delay(std::chrono::milliseconds(i)) {}
};

template <typename T>
struct Consumer {
  void operator()() {
    while (true) {
      if (queue.empty()) {
        break;
      }
      for (int i = 0; i < 10; i++) {
        const T item = queue.pop();
        std::cout << item.c << std::endl;
      }
    }
  }

  ThreadSaveQueue<T>& queue;
};

int main(int argc, char* argv[]) {
  ThreadSaveQueue<Item> queue;

  /// 创建生产者
  Producer producer1(queue, 1);
  Producer producer2(queue, 5);
  Producer producer3(queue, 6);

  /// 创建消费者
  Consumer consumer(queue);

  std::thread producerThread1(producer1);
  std::thread producerThread2(producer2);
  std::thread producerThread3(producer3);

  producerThread1.join();
  producerThread2.join();
  producerThread3.join();

  std::thread consumerThread1(consumer);
  consumerThread1.join();

  return 0;
}