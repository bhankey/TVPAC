#include <iostream>
#include <exception>
#include "containers/List.hpp"
#include "containers/Queue.hpp"
#include "containers/Stack.hpp"
#include "containers/Deque.hpp"

int main() {
//  ft::List<int> l = ft::List<int>();
//
//  for (int i = 1; i < 1000; ++i) {
//    l.push_back(i);
//  }
//
//
//  std::cout << l.back() << " " << l.front();

  ft::Deque<int> q = ft::Deque<int>();
  q.push_back(5);

  std::cout << q.back();

  q.push_front(10);

  std::cout << q.front();

  q.pop_back();
  std::cout <<  q.front();


  return 0;
}
