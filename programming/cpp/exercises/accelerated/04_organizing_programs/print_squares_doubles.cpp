// print_squares_doubles.cpp
// Print the squares of the doubles in a range specified by the user.

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>

double square(double x);
int width(int i);

int main() {
  double x_min, x_max, delta;
  std::cout << "Enter the minimum value: ";
  std::cin >> x_min;
  std::cout << "Enter the maximum possible value: ";
  std::cin >> x_max;
  std::cout << "Enter the step size: ";
  std::cin >> delta;

  const int x_width = 3 + std::max(width((int) x_min), width((int) x_max));
  const int square_width = 3 + std::max(
    width((int) square(x_min)),
    width((int) square(x_max))
  );

  std::cout << std::fixed << std::setprecision(2);
  for (double x = x_min; x <= x_max; x += delta) {
    std::cout << std::setw(x_width) << x << ' '
              << std::setw(square_width) << square(x) << '\n';
  }
}

double square(double x) {
  return x * x;
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
