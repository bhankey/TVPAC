//
// Created by sergey on 28.04.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_DEQUE_HPP_
#define FT_CONTAINERS_CONTAINERS_DEQUE_HPP_

#include "List.hpp"

namespace ft {
template<typename T, typename Container = ft::List<T> >
class Deque {
 protected:
  Container container_;
 public:

  explicit Deque(const Container &cont = Container()) : container_(cont) {
  }
  Deque(const Deque &other) : container_(other.container_) {
  }
  Deque &operator=(const Deque &other) {
    if (this != &other) {
      container_ = other.container_;
    }
    return *this;
  }
  ~Deque() {
  }

  T front() {
    return container_.front();
  }

  bool empty() const {
    return container_.empty();
  }

  void push_back(const T &value) {
    container_.push_back(value);
  }

  void push_front(const T &value) {
    container_.push_front(value);
  }

  void pop_back() {
    container_.pop_back();
  }

  void pop_front() {
    container_.pop_front();
  }

  T back() {
    return container_.back();
  }


};
}

#endif //FT_CONTAINERS_CONTAINERS_DEQUE_HPP_
