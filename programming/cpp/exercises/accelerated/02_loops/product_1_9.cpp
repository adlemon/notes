// product_1_9.cpp
// Compute and print the product of the integers in the range [1, 9).

#include <iostream>

int main() {
  int p = 1;
  for (int x = 1; x < 10; x++) {
    p *= x;
  }
  std::cout << "Product of integers in [1, 9) = " << p << std::endl;
}
