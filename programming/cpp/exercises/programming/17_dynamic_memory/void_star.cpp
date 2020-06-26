// void_star.cpp
// Illustrate the use of a void* pointer.

#include <iostream>

int main() {
  int i = 12345;
  void *p = &i;
  std::cout << "int value at address p: " << *static_cast<int *>(p) << "\n";
}
