// compute_maximum.cpp
// Prompt the user for two integers, and print the maximum of the two numbers.

#include <iostream>

int main() {
  int i1, i2;
  std::cout << "Enter the first number: ";
  std::cin >> i1;
  std::cout << "Enter the second number: ";
  std::cin >> i2;

  int max;
  if (i1 >= i2) {
    max = i1;
  } else {
    max = i2;
  }
  std::cout << "The larger of the two numbers is " << max << "." << std::endl;
}
