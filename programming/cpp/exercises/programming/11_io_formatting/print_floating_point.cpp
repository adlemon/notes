// print_floating_point.cpp
// Print floating-point numbers.

#include <iomanip>
#include <iostream>

int main() {
  double e = 2.718281828459045;
  for (int p = 1; p <= 10; ++p) {
    for (int w = 1; w <= 10; ++w) {
      std::cout << "p = " << std::setw(2) << p << ", w = " << std::setw(2) << w
                << ":\n"
                << std::setprecision(p) << "fixed:        " << std::fixed
                << std::setw(w) << e << "\n"
                << "scientific:   " << std::scientific << std::setw(w) << e
                << "\n"
                << "defaultfloat: " << std::defaultfloat << std::setw(w) << e
                << "\n\n";
    }
  }
}
