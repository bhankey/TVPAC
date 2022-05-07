//
// Created by sergey on 20.04.2021.
//

#ifndef FT_CONTAINERS_CONTAINERS_LISTNODE_HPP_
#define FT_CONTAINERS_CONTAINERS_LISTNODE_HPP_

#include "../include.hpp"

namespace ft {

template<typename T>
struct List_node {
  ClientMemoryBlock<List_node> prev;
  ClientMemoryBlock<List_node> next;
  T data;
};

}

#endif //FT_CONTAINERS_CONTAINERS_LISTNODE_HPP_
