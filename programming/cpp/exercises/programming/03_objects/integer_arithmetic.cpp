// integer_arithmetic.cpp
// Reads two integers from the standard input and performs various arithmetic
// operations on them.

#include <iostream>

int main() {
  int i1, i2;
  std::cout << "Enter two integers: ";
  std::cin >> i1 >> i2;

  if (i1 <= i2) {
    std::cout << "The minimum of " << i1 << " and " << i1 << " is " << i1
              << ".\n"
              << "The maximum of " << i1 << " and " << i2 << " is " << i2
              << ".\n";
  }
  if (i1 > i2) {
    std::cout << "The minimum of " << i1 << " and " << i2 << " is " << i2
              << ".\n"
              << "The maximum of " << i1 << " and " << i2 << " is " << i1
              << ".\n";
  }
  std::cout << "The sum of " << i1 << " and " << i2 << " is " << i1 + i2
            << ".\n"
            << "The difference of " << i1 << " and " << i2 << " is " << i1 - i2
            << ".\n"
            << "The product of " << i1 << " and " << i2 << " is " << i1 * i2
            << ".\n"
            << "The quotient of " << i1 << " and " << i2 << " is " << i1 / i2
            << ".\n"
            << "The remainder of " << i1 << " and " << i2 << " is " << i1 % i2
            << ".\n";
}
