#include <iostream>
#include <exception>
#include "Allocator.cpp"

int main() {
  auto alloc = Allocator();

  alloc.PrintAllSegments();

  auto b1 = alloc.Allocate(20);
  auto b2 = alloc.Allocate(30);
  auto b3 = alloc.Allocate(40);
  auto b4 = alloc.Allocate(50);

  alloc.PrintAllSegments();

  std::cout << std::endl;

  alloc.Free(b2);
  alloc.Free(b4);

  alloc.PrintAllSegments();
  std::cout << std::endl;

  alloc.Free(b3);

  alloc.PrintAllSegments();
  std::cout << std::endl;

  try {
    alloc.Allocate(1025);
  } catch (std::exception& e) {
    std::cout << e.what();
  }

  std::cout << std::endl;

  alloc.Allocate(500);
  alloc.Allocate(500);
  alloc.Allocate(500);
  alloc.PrintAllSegments();
  std::cout << std::endl;


  return 0;
}
