// managed_pointer_example.cpp
// Example usage for the ManagedPointer class.

#include <iostream>

#include "managed_pointer.cpp"

int main() {
  ManagedPointer<int> p1(new int(22));
  std::cout << "*p1 = " << *p1 << "\n";

  {
    ManagedPointer<int> p2(p1);
    std::cout << "*p2 = " << *p2 << "\n";
    *p2 = 23;
  }

  std::cout << "*p1 = " << *p1 << "\n";
}
