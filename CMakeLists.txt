cmake_minimum_required(VERSION 3.22)
project(memalloc)

set(CMAKE_CXX_STANDARD 23)

add_executable(memalloc main.cpp Allocator.cpp include.hpp containers/List.hpp containers/ListNode.hpp containers/Queue.hpp containers/Stack.hpp containers/Deque.hpp)
