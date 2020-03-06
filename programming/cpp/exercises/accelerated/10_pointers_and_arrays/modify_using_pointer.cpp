// modify_using_pointer.cpp
// Show how to modify a variable using a pointer to the variable.

#include <iostream>

int main() {
  int i;

  std::cout << "Enter the initial value of the integer: ";
  std::cin >> i;
  std::cout << "The initial value of the integer is: " << i << "\n";

  int *p = &i;
  std::cout << "\nEnter the new value of the integer: ";
  std::cin >> *p;
  std::cout << "The new value of the integer is: " << i << "\n";
}
