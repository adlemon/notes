// unique_ptr.cpp
// Illustrates the use of a unique_ptr.

#include <iostream>
#include <memory>

int main() {
  std::unique_ptr<int> p(new int{10});
  std::cout << "*p = " << *p << "\n";
}
