//
// Created by Caesar on 2025/11/17.
//
// 智能指针-->包装器
// 包装了一个指针，在智能指针超出作用域之后，析构指针指向的对象


//                   |->shared_ptr<T>   // 共享智能指针 [写清用处]
// 智能指针的类型 :  -->|->weak_ptr<T>     // 弱指针 【写清用处】
//                -->|->unique_ptr<T>   // 唯一指针【写清用处】
//

#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

class A {
public:
  A() {
    std::cout << "A()" << std::endl;
  }

  ~A() {
    std::cout << "~A()" << std::endl;
  }
};

template <typename T>
class ptr_space {
public:
  int count = 0;
  T obj;
};

template <typename T>
class i_ptr {
public:
  static i_ptr make() {
    auto a = new ptr_space<T>();
    a->count = 1;
    return i_ptr(a);
  }

  i_ptr(const i_ptr& objPtr) {
    m_ptr = objPtr.m_ptr;
    ++m_ptr->count;
  }

  ~i_ptr() {
    if (--m_ptr->count == 0 && m_ptr != nullptr) {
      delete m_ptr;
    }
  }

private:
  explicit i_ptr(ptr_space<T>* a) {
    m_ptr = a;
  }

private:
  ptr_space<T>* m_ptr;
};

std::vector<std::shared_ptr<A>> vA;
// RAII 管理的生命周期
// 作用域内有效，超出作用域自动析构
int main(int argc, char* argv[]) {
  const auto a = i_ptr<A>::make();
  i_ptr<A> b = a;
  return 0;
}