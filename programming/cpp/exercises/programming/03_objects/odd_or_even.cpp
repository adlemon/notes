// odd_or_even.cpp
// Reads an integer from the standard input and prints a message to the
// standard output indicating whether the integer was odd or even.

#include <iostream>

int main() {
  int i;
  std::cout << "Enter an integer: ";
  std::cin >> i;

  bool is_even = ((i % 2) == 0);
  if (is_even) {
    std::cout << "The integer " << i << " is even.\n";
  }
  if (!is_even) {
    std::cout << "The integer " << i << " is odd.\n";
  }
}
