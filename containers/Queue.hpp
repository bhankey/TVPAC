//
// Created by sergey on 28.04.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_QUEUE_HPP_
#define FT_CONTAINERS_CONTAINERS_QUEUE_HPP_

namespace ft {

#include "List.hpp"

template<typename T, typename Container = ft::List<T> >
class Queue {
 protected:
  Container container_;
 public:

  explicit Queue(const Container &cont = Container()) : container_(cont) {
  }
  Queue(const Queue &other) : container_(other.container_) {
  }
  Queue &operator=(const Queue &other) {
    if (this != &other) {
      container_ = other.container_;
    }
    return *this;
  }
  ~Queue() {
  }

  T front() {
    return container_.front();
  }

  bool empty() const {
    return container_.empty();
  }

  void push(const T &value) {
    container_.push_back(value);
  }
  void pop() {
    container_.pop_front();
  }
};
}
#endif //FT_CONTAINERS_CONTAINERS_QUEUE_HPP_
