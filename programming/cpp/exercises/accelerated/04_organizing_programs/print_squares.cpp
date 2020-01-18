// print_squares.cpp
// Print the squares of the integers in a range specified by the user.

#include <algorithm>
#include <iomanip>
#include <iostream>

int square(int i);
int width(int i);

int main() {
  int i_min, i_max;
  std::cout << "Enter the minimum integer in the range: ";
  std::cin >> i_min;
  std::cout << "Enter the maximum integer in the range: ";
  std::cin >> i_max;

  const int i_width = std::max(width(i_min), width(i_max));
  const int square_width = std::max(width(square(i_min)), width(square(i_max)));

  for (int i = i_min; i <= i_max; i += 1) {
    std::cout << std::setw(i_width) << i << ' '
              << std::setw(square_width) << square(i) << '\n';
  }
}

int square(int i) {
  return i * i;
}

int width(int i) {
  if (i < 0) {
    return 1 + width(-i);
  }

  if (i < 10) {
    return 1;
  }

  return 1 + width(i / 10);
}
