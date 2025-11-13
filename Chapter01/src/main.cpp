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
      Item item('A' + static_cast<char>(i));
      queue.push(item);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  }

  ThreadSaveQueue<T>& queue;
};

template <typename T>
struct Consumer {
  void operator()() {
    while (true) {
      if (queue.empty()) {
        break;
      }
      for (int i = 0; i < 10; i++) {
        const Item item = queue.pop();
        std::cout << item.c << std::endl;
      }
    }
  }

  ThreadSaveQueue<T>& queue;
};

int main(int argc, char* argv[]) {
  ThreadSaveQueue<Item> queue;

  Producer producer1(queue);
  Producer producer2(queue);
  Producer producer3(queue);

  Consumer consumer(queue);

  std::thread producerThread1(producer1);
  std::thread producerThread2(producer2);
  std::thread producerThread3(producer3);

  producerThread1.join();
  producerThread2.join();
  producerThread3.join();

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  std::thread consumerThread1(consumer);
  consumerThread1.join();

  return 0;
}