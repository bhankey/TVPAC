cmake_minimum_required(VERSION 3.22)
project(TVPiS)

set(CMAKE_CXX_STANDARD 17)

add_executable(TVPiS main.cpp include.hpp Containers/List.hpp Containers/ListNode.hpp Containers/Deque.hpp Containers/Queue.hpp Containers/Stack.hpp Containers/HashTable.hpp Lexer.hpp poliz.hpp Translator.hpp RecursiveParser.hpp Reader.hpp Allocator/ClientMemoryBlock.hpp Allocator/InternalMemory.hpp Allocator/InternalMemory.cpp Allocator/Segment.cpp Allocator/Segment.hpp Allocator/Allocator.hpp VariableBlock.hpp VariableSaver.hpp)
