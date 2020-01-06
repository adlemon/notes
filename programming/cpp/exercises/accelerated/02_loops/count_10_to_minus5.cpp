// count_10_to_minus5.cpp
// Print a countdown from 10 to -5.

#include <iostream>

int main() {
  int start = 10, end = -5, delta = -1;
  for (int i = start; i != end + delta; i += delta) {
    std::cout << i << std::endl;
  }
}
