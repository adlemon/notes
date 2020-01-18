// print_squares_100.cpp
// Print a table with the squares of the integers from 1 to 100.

#include <iomanip>
#include <iostream>

int square(int i);

int main() {
  const int i_min = 1;
  const int i_max = 100;

  for (int i = i_min; i <= i_max; i++) {
    std::cout << std::setw(3) << i << ' '
              << std::setw(5) << square(i) << '\n';
  }
}

int square(int i) {
  return i * i;
}
